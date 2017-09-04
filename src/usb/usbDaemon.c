#include <libudev.h>
#include <stdio.h>
#include "usbController.h"
#include "usbFunctions.h"
#include "usbLista.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdlib.h>

//Principal

int main(void){

    pid_t process_id = 0;
    pid_t sid = 0;
    
    process_id = fork();
    if (process_id < 0){
        printf("fork failed!\n");
        exit(1);
    }
    if (process_id > 0){
        printf("process_id of child process %d \n", process_id);
        exit(0);
    }
    umask(0);
    sid = setsid();
    if(sid < 0){
        exit(1);
    }
    close(STDERR_FILENO);

    Lista_Inicializar(&listaUsb);

    struct udev* udev = udev_new();
    if (!udev) {
        fprintf(stderr, "udev_new() failed\n");
        return 1;
    }

    while(1){
        enumerate_devices(udev);
        sleep(1);
    }

    udev_unref(udev);
    return 0;

}
