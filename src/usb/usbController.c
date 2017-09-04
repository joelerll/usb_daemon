#include <libudev.h>
#include <stdio.h>
#include <string.h>
#include "usbController.h"
#include "usbLista.h"
#include "usbFunctions.h"
#include <stdlib.h>
#include <mntent.h>
#include "usbJson.h"

#define SUBSYSTEM "usb"

void print_device()
{
    //Imprime lista como prueba
    printf("\n----------------------------------------------------------%i\n",listaUsb.numeroElementos);
    ElementoLista *elem = NULL;
    for (elem = Lista_Primero(&listaUsb); elem != NULL; elem = Lista_Siguiente(&listaUsb, elem)){
        struct InfoUSB *info4 = (struct InfoUSB *)elem->objeto;
        printf("[%s %s %s %s]\n",info4->usbDirMount,
                        info4->usbNodo,
                        info4->idProduct,
                        info4->idVendor);
    } 
}

struct udev_device* obtener_hijo(struct udev* udev , struct udev_device* padre, const char* subsistema){
	struct udev_device* hijo = NULL;
	struct udev_enumerate *enumerar = udev_enumerate_new(udev);

	udev_enumerate_add_match_parent(enumerar, padre);
	udev_enumerate_add_match_subsystem(enumerar, subsistema);
	udev_enumerate_scan_devices(enumerar);

	struct udev_list_entry *dispositivos = udev_enumerate_get_list_entry(enumerar);
	struct udev_list_entry *entrada;

	udev_list_entry_foreach(entrada, dispositivos){
		const char *ruta = udev_list_entry_get_name(entrada);
		hijo = udev_device_new_from_syspath(udev, ruta);
		break;
	}

	udev_enumerate_unref(enumerar);
	return hijo;
}

void enumerate_devices(struct udev* udev)
{
    struct udev_enumerate* enumerate = udev_enumerate_new(udev);

    udev_enumerate_add_match_subsystem(enumerate, "scsi");
    udev_enumerate_add_match_property(enumerate, "DEVTYPE", "scsi_device");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry* devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry* entry;

    udev_list_entry_foreach(entry, devices) {
        const char* path = udev_list_entry_get_name(entry);
        struct udev_device* dev = udev_device_new_from_syspath(udev, path);

    	//Obtenemos la informacion pertinente del dispositivo
		struct udev_device* block = obtener_hijo(udev, dev, "block");
		struct udev_device* scsi_disk = obtener_hijo(udev, dev, "scsi_disk");
		struct udev_device* usb = udev_device_get_parent_with_subsystem_devtype(dev, "usb", "usb_device");
        
		if (block && scsi_disk && usb){
            char *nodo = malloc(sizeof(char));
            strcpy(nodo,(char *)udev_device_get_devnode(block));
            actLista(nodo,usb);
        }

    }
    eliminarRetirado();
    print_device();
    encerarEstado();
    //Cada vez que se actualiza la lista, se actualiza el json 
    toJson();
    udev_enumerate_unref(enumerate);
}

void actLista(char *nodo, struct udev_device* dev){
    char *product = malloc(sizeof(char));
    strcpy(product,(char *)udev_device_get_sysattr_value(dev, "idProduct"));
    ElementoLista *elem = NULL;
    elem = Lista_BuscarXNodo(&listaUsb,product);
    if(elem==NULL){
        anadirLista(nodo,dev);
    }else{
        struct InfoUSB *info4 = (struct InfoUSB *)elem->objeto;
        //Se actualiza mount por si se encuentra vacío.
        char *mount = getMount(nodo);
        info4->usbDirMount = mount;
        //
        info4->estado = 1;
    }
}

void encerarEstado(){
    ElementoLista *elem = NULL;
    for (elem = Lista_Primero(&listaUsb); elem != NULL; elem = Lista_Siguiente(&listaUsb, elem)){
        struct InfoUSB *info4 = (struct InfoUSB *)elem->objeto;
        info4->estado = 0;    
    } 
}

void eliminarRetirado(){
    ElementoLista *elem = NULL;
    for (elem = Lista_Primero(&listaUsb); elem != NULL; elem = Lista_Siguiente(&listaUsb, elem)){
        struct InfoUSB *info4 = (struct InfoUSB *)elem->objeto;
        if(info4->estado == 0){
            Lista_Sacar(&listaUsb,elem);
        }    
    } 
}

void anadirLista(char* nodo, struct udev_device* dev){    
    char *vendor = malloc(sizeof(char));
    char *product = malloc(sizeof(char));
    char *mount = getMount(nodo);
    strcpy(vendor,(char *)udev_device_get_sysattr_value(dev, "idVendor"));
    strcpy(product,(char *)udev_device_get_sysattr_value(dev, "idProduct"));
    struct InfoUSB *info = crearInfoUsb(mount,nodo,vendor,product);
    Lista_InsertarFin(&listaUsb,(void *)info);
}


char *getMount(char *usbNodo){

    //Dirección donde se almacena mtab: /etc/mtab
    FILE *fp = setmntent( "/etc/mtab", "r" );
    for ( ;; ){
        struct mntent *me = getmntent( fp );
        if ( NULL == me )
        {
            break;
        }
        /*
            Corregir
        */
        int var = 0;
        //printf("[CMP: %s - %s]\n",me->mnt_fsname,usbNodo);
        for(int i=0 ; *(usbNodo+i)!='\0' ; i++ ){
            //  /dev/sdb
            char a = *(usbNodo+i);
            //  /dev/sdb1
            char b = *((me->mnt_fsname)+i);
            if( a!= b){
                var = 1;
                break;
            }  
        }
        if(var == 0){
            char *retorno = (char *)malloc(strlen(me->mnt_dir)*sizeof(char));
            strcpy(retorno,me->mnt_dir);
            endmntent( fp );
            return retorno;
        }
    }
    endmntent( fp );
    return "";
}