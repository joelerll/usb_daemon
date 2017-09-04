
struct InfoUSB{
    char *usbDirMount;
    char *usbNodo;
    char *idVendor;
    char *idProduct;
    char *nombre;
    int estado;
}InfoUSB;

//Variables globales
//char JSON[50000];

struct InfoUSB *crearInfoUsb(char *usbDirMount, char *usbNodo, char *idVendor, char *idProduct);
