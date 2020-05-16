#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int     main()
{
    fork();
    fork();
    fork();
    fork();
    fork();
    printf("I am %d\n", (int)getpid());
    exit(0);
    return (0);
}