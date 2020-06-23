#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
 

static int count = 10;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


 void *thread1_routine(void *unused)
 {
    for (int i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&mutex);
        count++; //zona critica acceden a un recurso compartido
        pthread_mutex_unlock(&mutex);
    }
    
 }     //Los count NO son operaciones atomicas, si se pueden interrumpir se mira con la flag -S en el gcc que pasa a ensamblador

  void *thread2_routine(void *unused)
 {
    for (int i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&mutex);
        count--; //zona critica acceden a un recurso compartido
        pthread_mutex_unlock(&mutex);
    }
    
 }

 void errorEXit(char *strerr)
 {
     perror(strerr);    
     exit(1);
 }

 int main(int argc, char const *argv[])
 {
     pthread_t thread1, thread2;

     if(0 != pthread_create(&thread1, NULL, thread1_routine, NULL)){
         errorEXit(" El hilo 1 no pudo ser creado ");
     }

     if(0 != pthread_create(&thread2, NULL, thread2_routine, NULL)){
         errorEXit(" El hilo 2 no pudo ser creado ");
     }

     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL);

     printf("El valor de count es: %d \n", count);
     return 0;
 }

