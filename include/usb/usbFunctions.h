
struct InfoUSB{
    char *usbDirMount;
    char *usbNodo;
    char *idVendor;
    char *idProduct;
    char *nombre;
    int estado;
}InfoUSB;

struct InfoUSB *crearInfoUsb(char *usbDirMount, char *usbNodo, char *idVendor, char *idProduct);
