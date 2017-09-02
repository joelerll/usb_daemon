#include <libudev.h>
#include <stdio.h>
#include <mntent.h>
#include <stdlib.h>
#include "usbFunctions.h"

//gcc -Wall -Iinclude/ src/usb.c -o bin/usb -ludev

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


static void enumerar_disp_alm_masivo(struct udev* udev){
	struct udev_enumerate* enumerar = udev_enumerate_new(udev);

	//Buscamos los dispositivos USB del tipo SCSI (MASS STORAGE)
	udev_enumerate_add_match_subsystem(enumerar, "scsi");
	udev_enumerate_add_match_property(enumerar, "DEVTYPE", "scsi_device");
	udev_enumerate_scan_devices(enumerar);

	//Obtenemos los dispositivos con dichas caracteristicas
	struct udev_list_entry *dispositivos = udev_enumerate_get_list_entry(enumerar);
	struct udev_list_entry *entrada;

	//Recorremos la lista obtenida
	udev_list_entry_foreach(entrada, dispositivos){
		const char* ruta = udev_list_entry_get_name(entrada);
		struct udev_device* scsi = udev_device_new_from_syspath(udev, ruta);

		//Obtenemos la informacion pertinente del dispositivo
		struct udev_device* block = obtener_hijo(udev, scsi, "block");
		struct udev_device* scsi_disk = obtener_hijo(udev, scsi, "scsi_disk");

		struct udev_device* usb = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");

		if (block && scsi_disk && usb){
            
            char *usbNodo = (char *) udev_device_get_devnode(block);
            char *usbDirMount = getUSBDirMount(usbNodo);
            char *idVendor = (char *)udev_device_get_sysattr_value(usb, "idVendor");
            char *idProduct = (char *)udev_device_get_sysattr_value(usb, "idProduct");
            
            //Se crea la estructura que contiene la información del usb
            struct InfoUSB *info = crearPlantillaInformacion(usbDirMount,usbNodo,idVendor,idProduct);
                            
            printf("Nodo: %s, Montado en: %s, id's: %s:%s\n",info->usbNodo,
                                                            info->usbDirMount,
                                                            info->idVendor,
                                                            info->idProduct);
		}

		if (block){
			udev_device_unref(block);
		}

		if (scsi_disk){
			udev_device_unref(scsi_disk);
		}

		udev_device_unref(scsi);
	}

	udev_enumerate_unref(enumerar);
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


int main(){

    struct udev* udev = udev_new();
    enumerar_disp_alm_masivo(udev);
    udev_unref(udev);
    return 0;
}