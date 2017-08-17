// METODOS
char POST [] = "POST";
char GET [] = "GET";

// routes
char listar_dispositivos [] = "/listar_dispositivos";
char nombrar_dispositivo [] = "/nombrar_dispositivo";
char leer_archivo [] = "/leer_archivo";
char escribir_archivo [] = "/escribir_archivo";
// printf("%s\n", upload_data);
if (strcmp(method,GET) == 0 && strcmp(listar_dispositivos,url) == 0) {
  page = "{dispositivo: \"listar_dispositivos\"}";
} else if (strcmp(method,POST) == 0 && strcmp(nombrar_dispositivo,url) == 0) {
  page = "nombrar_dispositivo";
  MHD_create_post_processor (connection, POSTBUFFERSIZE, iterate_post, (void *)con_info);
} else if (strcmp(method,GET) == 0 && strcmp(leer_archivo,url) == 0) {
  page = "leer_archivo";
} else if (strcmp(method,POST) == 0 && strcmp(escribir_archivo,url) == 0) {
  page = "escribir_archivo";
} else {
  page = "accion no valida";
}
