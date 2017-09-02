#include <libudev.h>
#include <stdio.h>
#include <mntent.h>
#include <stdlib.h>
#include "usbFunctions.h"
#include <string.h>

//gcc -Wall -Iinclude/ src/usb/usb.c -o bin/usb -ludev

InfoUSB *crearPlantillaInformacion(char *usbDirMount, char *usbNodo, char *idVendor, char *idProduct){
    InfoUSB *info = (InfoUSB *)malloc(sizeof(InfoUSB));
    info->usbDirMount=usbDirMount;
    info->usbNodo=usbNodo;
    info->idVendor=idVendor;
    info->idProduct=idProduct;
    return info;
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

listaDispConectados *getListaDispConectados(struct udev* udev){

    struct listaDispConectados *listaDisp = (listaDispConectados *)malloc(sizeof(listaDispConectados));
    listaDisp->lista =(InfoUSB**)malloc(sizeof(InfoUSB *));

	struct udev_enumerate* enumerar = udev_enumerate_new(udev);

	//Buscamos los dispositivos USB del tipo SCSI (MASS STORAGE)
	udev_enumerate_add_match_subsystem(enumerar, "scsi");
	udev_enumerate_add_match_property(enumerar, "DEVTYPE", "scsi_device");
	udev_enumerate_scan_devices(enumerar);

	//Obtenemos los dispositivos con dichas caracteristicas
	struct udev_list_entry *dispositivos = udev_enumerate_get_list_entry(enumerar);
	struct udev_list_entry *entrada;

    int iterator = 0;

	//Recorremos la lista obtenida
	udev_list_entry_foreach(entrada, dispositivos){
		const char* ruta = udev_list_entry_get_name(entrada);
		struct udev_device* scsi = udev_device_new_from_syspath(udev, ruta);

		//Obtenemos la informacion pertinente del dispositivo
		struct udev_device* block = obtener_hijo(udev, scsi, "block");
		struct udev_device* scsi_disk = obtener_hijo(udev, scsi, "scsi_disk");
		struct udev_device* usb = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");

		if (block && scsi_disk && usb){   
            //Se crea la estructura que contiene la información del usb
            char *usbNodo = (char *)malloc(sizeof(char));
            char *usbDirMount = (char *)malloc(sizeof(char));
            char *idVendor = (char *)malloc(sizeof(char));
            char *idProduct = (char *)malloc(sizeof(char));

            strcpy(usbNodo,(char *) udev_device_get_devnode(block));
            strcpy(usbDirMount,getUSBDirMount(usbNodo));
            strcpy(idVendor,(char *)udev_device_get_sysattr_value(usb, "idVendor"));
            strcpy(idProduct,(char *)udev_device_get_sysattr_value(usb, "idProduct"));

            struct InfoUSB *info = crearPlantillaInformacion(usbDirMount,usbNodo,idVendor,idProduct);                
            //Se guarda la plantilla de cada usb en la lista
            *((listaDisp->lista)+iterator) = info;
            iterator++;
		}
		if (block) udev_device_unref(block);
		if (scsi_disk) udev_device_unref(scsi_disk);
		udev_device_unref(scsi);
	}
    listaDisp->n_Dispositivos = iterator;
	udev_enumerate_unref(enumerar);
    return listaDisp;
}

char *getUSBDirMount(char *usbNodo){
    /*
    Dirección donde se almacena mtab: /etc/mtab
    */
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
        for(int i=0 ; *(usbNodo+i)!='\0' ; i++ ){
            //  /dev/sdb
            char a = *(usbNodo+i);
            //  /dev/sdb1
            char b = *(me->mnt_fsname+i);
            if( a!= b){
                var = 1;
                break;
            }  
        }
        if(var == 0) return me->mnt_dir;
    }
    endmntent( fp );
    return NULL;
}

//Función que imprime los dispositivos conectados con su respectiva información.
char *imprimirListaDispositivos(listaDispConectados *listaDisp){

    printf("----------------------------------------------------------------------\n\n");
    printf("\tLISTA DE DISPOSITIVOS CONECTADOS\n\n");

    char *retorno  = malloc(sizeof(char));

    for(int i=0 ; i<listaDisp->n_Dispositivos; i++){
        struct InfoUSB *prueba = *((listaDisp->lista)+i);
        printf("\t\t%i) Nodo     : %s\n",i+1,prueba->usbNodo);
        strcat(retorno,"Nodo     : ");
        printf("\t\t   Montaje  : %s\n",prueba->usbDirMount);
        printf("\t\t   idVendor : %s\n",prueba->idVendor);
        printf("\t\t   idProduct: %s",prueba->idProduct);
        printf("\n\n");
    }

    printf("----------------------------------------------------------------------\n\n");
    
    return retorno;

}

/*int main(){
    struct udev* udev = udev_new();
    imprimirListaDispositivos(getListaDispConectados(udev));
    udev_unref(udev);
    return 0;
}*/