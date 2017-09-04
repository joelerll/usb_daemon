#include <libudev.h>

void print_device();
void process_device(struct udev_device* dev);
struct udev_device *obtener_hijo(struct udev* udev , struct udev_device* padre, const char* subsistema);
void enumerate_devices(struct udev* udev);  
void anadirLista(char* nodo, struct udev_device* dev);
void eliminarRetirado();
void encerarEstado();
void actLista(char *nodo, struct udev_device* dev);
char *getMount(char *usbNodo);