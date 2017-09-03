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

InfoUSB *crearPlantillaInformacion(char *usbDirMount, char *usbNodo, char *idVendor, char *idProduct);
char *getUSBDirMount(char *usbNodo);
struct udev_device* obtener_hijo(struct udev* udev , struct udev_device* padre, const char* subsistema);
listaDispConectados *getListaDispConectados(struct udev* udev);
void imprimirListaDispositivos(listaDispConectados *lista);

char *parseToJson(listaDispConectados *listaDisp);