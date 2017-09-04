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
#include "usbServer.h"
#include "usbJson.h"

//Principal
void *runDaemon();
void doHiloDaemon();

int main(void){
    //Proceso daemon
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

    doHilo();
    doHiloDaemon();
    
    return 0;
}

void doHiloDaemon(){
    pthread_t hiloDaemon = 0;
    int status = 0;
    fseek(stdin,0,SEEK_END);
    status = pthread_create(&hiloDaemon, NULL, runDaemon, NULL);
    if (status < 0) {
        printf("Error al crear el hilo\n");
    }    
    pthread_join(hiloDaemon,NULL);
}

void *runDaemon(){
    struct udev* udev = udev_new();
    if (!udev) {
        fprintf(stderr, "udev_new() failed\n");
    }
    while(1){
        enumerate_devices(udev);
        sleep(3);
    }
    udev_unref(udev);
}