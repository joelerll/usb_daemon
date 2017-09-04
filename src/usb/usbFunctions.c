#include <stdlib.h>
#include "usbFunctions.h"

struct InfoUSB *crearInfoUsb(char *usbDirMount, char *usbNodo, char *idVendor, char *idProduct){
    struct InfoUSB *info = (struct InfoUSB *)malloc(sizeof(struct InfoUSB));
    info->usbDirMount=usbDirMount;
    info->usbNodo=usbNodo;
    info->idVendor=idVendor;
    info->idProduct=idProduct;
    info->nombre="";
    info->estado=1;

    return info;
}
