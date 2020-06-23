#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("%s : %i \n", argv[0], getpid());

    for(int i = 0; i < argc; i++){
        printf("Argumento %d, %s \n", i, argv[i]);
    }
    return 0;
}
