#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{

     char *const argv2[] = {"execv2", "abcdef", "ghij", NULL};

    printf("%s : %i \n", argv[0], getpid());
    execv("/home/anibal/Dev/C/execv2", argv2);
    
    printf("ERROR");

    return -1;
}
