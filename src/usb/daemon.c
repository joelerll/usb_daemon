#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include "usbFunctions.h"

// ps -efj - comando para verificar procesos, de acá se obtiene el pid
// sudo kill PID - matar proceso 

int main() { 
  pid_t pid, sid;
  int apachePIDfile,apachePIDread, apachePID, daemonLogFileDesc;
  char buf[5], filename[255];        
          
  /* Forkeamos el proceso padre */
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  /* Cuando tenemos un PID correcto podemos cerrar
   * el proceso padre.
   * Atención al control de errores, es una buena
   * técnica de programación comprobar todas las
   * situaciones donde se pueden dar errores. */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  /* Cambiamos el modo de la mascara de ficheros */
  /* Hacemos esto para que los fichero generados por el
   * demonio sean accesibles por todo el mundo */
  umask(0);      
  /* Abrimos los ficheros de logs del demonio */        
  /* Esto es opcional pero como vamos a cerrar los descriptores 
   * hacemos esto para que exista algo de comunicación con el demonio */
  daemonLogFileDesc = open ("log", O_WRONLY | O_CREAT, 0600); 
  if (daemonLogFileDesc == -1) {
    perror ("Error en la apertura del log");
    exit (EXIT_FAILURE); 
  }

  /* Creamos un nuevo SID */
  /* Esto se hace porque al haber matado al padre el hijo puede quedarse 
   * en el sistema como un proceso zombie, generando un nuevo SID hacemos
   * que el sistema se haga cargo del proceso huérfano otorgándole un nuevo SID */
  sid = setsid();
  if (sid < 0) {  
    perror("new SID failed");
    exit(EXIT_FAILURE);
  }
    
  /* Por seguridad, cambiamos el directorio de trabajo */
  if ((chdir("/")) < 0) {
    perror("Change the current work directory failed");
    exit(EXIT_FAILURE);
  }
    
  /* Cerramos los descriptores standard */
  /* El demonio no puede usar la terminal, por lo que estos
   * descriptores son inútiles y un posible riesgo de seguridad.*/
  //close(STDIN_FILENO);
  //close(STDOUT_FILENO);
  close(STDERR_FILENO);
  /* El código del demonio */
  /* Obtenemos el PID con el que está corriendo el proceso apache */



  ///////////////////////////      AQUI      /////////////////////////
  //// Debes cambiarle la ruta var/run/(nombre del proceso que siempre estara)

  apachePIDfile = open("/var/run/acpid.pid", O_RDONLY, 0600);
  if (apachePIDfile == -1) {
    perror("Error en la apertura del fichero");
    exit(EXIT_FAILURE);
  }
  apachePIDread = read (apachePIDfile, buf, sizeof(buf));
  ///////////////////////////      ------      /////////////////////////

    
  /* El gran bucle! */
  /* El demonio ejecutara este bucle toda su vida,
   * abrirá un archivo del pseudo sistema de ficheros /proc
   * y comprobará que existe, si existe Apache está corriendo y lo escribe
   * en el log, en caso contrario sale. */


  //////Con esto compruebas en el archivo LOG q se crea al hacerle ./a.out que diga "Tal proceso running"///
  while (1) {
    apachePID = atoi (buf);
    snprintf(filename, sizeof(filename), "/proc/%d/cmdline", apachePID);
  
    if ((open (filename, O_RDONLY, 0600)) == -1) {
      perror ("No puedo abrir el fichero en proc");
      exit(EXIT_FAILURE);
    } else {
      struct udev* udev = udev_new();
      char *lista = imprimirListaDispositivos(getListaDispConectados(udev));
      write (daemonLogFileDesc, lista, 15);
      sleep(10); /* espera 30 segundos */
    }
  }
  exit(EXIT_SUCCESS);
}