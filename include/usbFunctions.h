#include <libudev.h>

typedef struct InfoUSB{
    char *usbDirMount;
    char *usbNodo;
    char *idVendor;
    char *idProduct;
    char *nombre;
}InfoUSB;

typedef struct listaDispConectados{
    InfoUSB **lista;
    int n_Dispositivos;
}listaDispConectados;

char GLOBALJSON[50000];

<<<<<<< HEAD
//static pthread_mutex_t candado;
//static pthread_cond_t producido;
//static pthread_cond_t consumido;

//pthread_mutex_init(&candado, NULL);
=======
// static pthread_mutex_t candado;
//static pthread_cond_t producido;
//static pthread_cond_t consumido;

// pthread_mutex_init(&candado, NULL);
>>>>>>> 1803d5b8b121d2a2554064725511694849f71380
//pthread_cond_init(&producido, NULL);
//pthread_cond_init(&consumido, NULL);

InfoUSB *crearPlantillaInformacion(char *usbDirMount, char *usbNodo, char *idVendor, char *idProduct);
char *getUSBDirMount(char *usbNodo);
struct udev_device* obtener_hijo(struct udev* udev , struct udev_device* padre, const char* subsistema);
listaDispConectados *getListaDispConectados(struct udev* udev);
void imprimirListaDispositivos(listaDispConectados *lista);

void parseToJson(listaDispConectados *listaDisp);

void *server();