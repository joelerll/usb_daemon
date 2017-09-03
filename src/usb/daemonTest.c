#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "usbFunctions.h"
#include <pthread.h>

int main(int argc, char* argv[])
{
    pid_t process_id = 0;
    pid_t sid = 0;
    // Create child process
    process_id = fork();
    // Indication of fork() failure
    if (process_id < 0)
    {
        printf("fork failed!\n");
        // Return failure in exit status
        exit(1);
    }
    // PARENT PROCESS. Need to kill it.
    if (process_id > 0)
        {
        printf("process_id of child process %d \n", process_id);
        // return success in exit status
        exit(0);
    }
    //unmask the file mode
    umask(0);
    //set new session
    sid = setsid();
    if(sid < 0)
    {
        // Return failure
        exit(1);
    }
    // Change the current working directory to root.
    //chdir("/");
    // Close stdin. stdout and stderr
    //close(STDIN_FILENO);
    //close(STDOUT_FILENO);
    close(STDERR_FILENO);
    struct udev* udev = udev_new();
    memset(GLOBALJSON,0,sizeof(GLOBALJSON));

    pthread_t *hilo2;
    int status = 0;
    status = pthread_create(hilo2, NULL, server, NULL);
    if (status < 0) {
        fprintf(stderr, "Error al crear el hilo\n");
        exit(-1);
    }

    while (1)
    {
        //Hacer hilo para la lista
        listaDispConectados *listaDisp = (getListaDispConectados(udev));
        parseToJson(listaDisp);
        udev_unref(udev);
        //Hilo para servidor
        sleep(1);
    }
    return (0);
}