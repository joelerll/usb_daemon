#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define POSTBUFFERSIZE  800000
#define MAXNAMESIZE     2000
#define MAXANSWERSIZE   80000

#define GET             0
#define POST            1

struct connection_info_struct
{
  int connectiontype;
  char *answerstring;
  struct MHD_PostProcessor *postprocessor;
};

char *url_tmp;

struct solicitud_uno {
  char * solicitud;
  char * nodo;
  char * nombre;
};

const char *greetingpage =
  "%s";

char *page = "";


char *listar_dispositivos_respo = "%s";

const char *errorpage =
  "{\"error\": \"metodo no valido\"}";

static int
send_page (struct MHD_Connection *connection, const char *page)
{
  int ret;
  struct MHD_Response *response;


  response =
    MHD_create_response_from_buffer (strlen (page), (void *) page,
				     MHD_RESPMEM_PERSISTENT);
  if (!response)
    return MHD_NO;

  ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
  MHD_destroy_response (response);

  return ret;
}


static int iterate_post (void *coninfo_cls, enum MHD_ValueKind kind, const char *key, const char *filename, const char *content_type,const char *transfer_encoding, const char *data, uint64_t off,size_t size)
{
  // printf("%s\n", url_tmp);
  struct connection_info_struct *con_info = coninfo_cls;
  if (0 == strcmp (key, "nombrar_dispositivo"))
  {
    printf("nombrar dispotivos\n");
    if ((size > 0)) // && (size <= MAXNAMESIZE)
    {
      char *answerstring;
      answerstring = malloc (MAXANSWERSIZE);
      if (!answerstring)
        return MHD_NO;
      // CAMBIAR POR FUNCION
      // char *nombre = "asds";
      char *x  = nombrar_dispositivo(data);
      // printf("%s\n", data);
      snprintf (answerstring, MAXANSWERSIZE, greetingpage, x);
      con_info->answerstring = answerstring;
    }
    else
      con_info->answerstring = NULL;

    return MHD_NO;
  }

  if (0 == strcmp (key, "escribir_archivo"))
  {
    printf("escribir archivo\n");

    if ((size > 0)) // && (size <= MAXNAMESIZE)
    {
      char *answerstring;
      answerstring = malloc (MAXANSWERSIZE);
      if (!answerstring)
        return MHD_NO;
      // printf("%s\n", data);
      // CAMBIAR POR FUNCION
      char *estado = escribir_archivo(data);
      snprintf (answerstring, MAXANSWERSIZE, greetingpage, estado);
      con_info->answerstring = answerstring;
    }
    else
      con_info->answerstring = NULL;

    return MHD_NO;
  }
  if (0 == strcmp (key, "leer_archivo"))
  {
    printf("leer archivo\n");
    if ((size > 0)) // && (size <= MAXNAMESIZE)
    {
      char *answerstring;
      answerstring = malloc (MAXANSWERSIZE);
      if (!answerstring)
        return MHD_NO;
      // CAMBIAR POR FUNCION
      char *resp = leer_archivo(data);
      // printf("%s\n", resp);
      snprintf (answerstring, MAXANSWERSIZE, greetingpage, resp);
      con_info->answerstring = answerstring;
    }
    else
      con_info->answerstring = NULL;

    return MHD_NO;
  }
  return MHD_YES;
}

static void request_completed (void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe)
{
  struct connection_info_struct *con_info = *con_cls;

  if (NULL == con_info)
    return;

  if (con_info->connectiontype == POST)
  {
    MHD_destroy_post_processor (con_info->postprocessor);
    if (con_info->answerstring)
      free (con_info->answerstring);
  }

  free (con_info);
  *con_cls = NULL;
}


static int answer_to_connection (void *cls, struct MHD_Connection *connection, const char *url, const char *method,const char *version, const char *upload_data,size_t *upload_data_size, void **con_cls)
{
  url_tmp = malloc(sizeof(char *));
  if (NULL == *con_cls)
  {
    struct connection_info_struct *con_info;
    con_info = malloc (sizeof (struct connection_info_struct));
    if (NULL == con_info)
      return MHD_NO;
    con_info->answerstring = NULL;
    if (0 == strcmp (method, "POST"))
    {
      con_info->postprocessor = MHD_create_post_processor (connection, POSTBUFFERSIZE,iterate_post, (void *) con_info);

      if (NULL == con_info->postprocessor)
      {
        free (con_info);
        return MHD_NO;
      }
      con_info->connectiontype = POST;
    }
    else
      con_info->connectiontype = GET;

    *con_cls = (void *) con_info;
    return MHD_YES;
  }
  if (strcmp(method,"GET") == 0 && strcmp("/listar_dispositivos",url) == 0) {
    printf("listar dispositivos\n");
    char *dispositivos = solicitudes_daemon();
    char *page_tmp = malloc(MAXANSWERSIZE);
    snprintf (page_tmp, MAXANSWERSIZE, listar_dispositivos_respo, dispositivos);
    // printf("%s\n", page_tmp);
    page = "{\"solicitud\": \"listar_dispositivos\", \"dispositivos\": [{\"nombre\": \"mi_dispotivito\", \"montaje\": \"/home/joel\",\"nodo\": \"/dev/ddd\",\"id\": \"vendor:device\"},{\"nombre\": \"mi_dispotivito2\", \"montaje\": \"/home/joel/dos\",\"nodo\": \"/dev/bbb\",\"id\": \"vendor:device:2\"}],\"status\": 1,\"str_error\": \"mensaje de arror\"}";
    return send_page (connection, page_tmp);
  }

  if (0 == strcmp (method, "POST") && (strcmp("/escribir_archivo",url) == 0 || strcmp("/nombrar_dispositivo",url) == 0 || strcmp("/leer_archivo",url) == 0))
  {
    struct connection_info_struct *con_info = *con_cls;
    if (*upload_data_size != 0)
    {
      MHD_post_process (con_info->postprocessor, upload_data,*upload_data_size);
      *upload_data_size = 0;
      return MHD_YES;
    }
    else if (NULL != con_info->answerstring)

    return send_page (connection, con_info->answerstring);
  }
  return send_page (connection, errorpage);
}

int main (int argc, char **argv)
{
  if (argc !=2) {
    printf("\n**Error, argumentos invalidos, por favor ingrese el puerto**\n\n");
    return 0;
  }
  int puerto = atoi(argv[1]);
  printf("Servidor inicializado en el puerto: %d\n", puerto);
  struct MHD_Daemon *daemon;

  daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, puerto, NULL, NULL, &answer_to_connection, NULL,MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL, MHD_OPTION_END);
  if (NULL == daemon)
    return 1;

  getchar ();

  MHD_stop_daemon (daemon);

  return 0;
}
