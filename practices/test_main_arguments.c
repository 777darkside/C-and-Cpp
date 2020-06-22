#include <stdio.h>


int main(int argc, char *argv[]) {

    for (int i = 0; i < argc; i++)
    {
        printf("Argumento %d, %s \n", i, argv[i]);
        
    }
    
    printf("argc = %d \n", argc);
    printf("argv[argc] = %s \n", argv[argc]);

    int pause = getchar();
    return 0;
}