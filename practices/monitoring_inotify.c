#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>


int main(void) {
    int fd; // File Descriptor  
    int wd; // Watch descriptor
    char buf[200]; // Leera la estructura de inotify, por eso el tamaño grande (200)
    fd = inotify_init();   
    inotify_add_watch(fd, "/home/anibal/Documents" , IN_CLOSE_WRITE);

for (;;)
{
    read(fd, buf, 200);
    printf("El archivo escrito y cerrado es: %s \n" , ((struct inotify_event*)buf) -> name);  //Estructura sacada del manual
}

    return 0;
}