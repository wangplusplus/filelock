#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define A_MEGABYTE (1024 * 1024)

int main()
{
    char *some_memory = NULL;
    int megabyte = A_MEGABYTE;

    int exit_code = EXIT_FAILURE;

    some_memory = (char *)malloc(megabyte);
    if (NULL != some_memory)
    {
        sprintf(some_memory, "Hello, world\n");
        printf("%s", some_memory);
        exit_code = EXIT_SUCCESS;
    }

    free(some_memory);
    exit(exit_code);
}
