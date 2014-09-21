#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ONE_K 1024
int main()
{
    char *some_memory = NULL;

    int exit_code = EXIT_FAILURE;

    some_memory = (char *)malloc(ONE_K);

    if (NULL != some_memory)
    {
        free(some_memory);
        printf("Memory allocated and freed again\n");
        exit_code = EXIT_SUCCESS;
    }

    exit(exit_code);
}
