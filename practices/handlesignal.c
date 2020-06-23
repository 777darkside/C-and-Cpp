#include <stdio.h>
#include <unistd.h>
#include <signal.h>


//COMANDOS kill, ps u
void MySignalHandle(int sig){
    printf("Signal number is %d \n", sig);
}

int main(void) {


    while(1){

        signal(SIGIO, &MySignalHandle);

        printf(".... waiting for a signal \n");

        sleep(2);
    }
    return 0;
}