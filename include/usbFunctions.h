typedef struct InfoUSB{
    char *usbDirMount;
    char *usbNodo;
    char *idVendor;
    char *idProduct;
    char *nombre;
}InfoUSB;

InfoUSB *crearPlantillaInformacion(char *usbDirMount, char *usbNodo, char *idVendor, char *idProduct);
char *getUSBDirMount(char *usbNodo);
struct udev_device* obtener_hijo(struct udev* udev , struct udev_device* padre, const char* subsistema);
static void enumerar_disp_alm_masivo(struct udev* udev);
