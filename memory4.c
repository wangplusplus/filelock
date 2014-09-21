#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ONE_K (1024)

int main()
{
    char *some_memory = NULL;
    char *scan_ptr = NULL;

    some_memory = (char *)malloc(ONE_K);

    if (NULL == some_memory)
    {
        exit(EXIT_FAILURE);
    }

    scan_ptr = some_memory;
    for (int i = 0; i < (ONE_K * 2); ++i)
    {
        *scan_ptr = 0;
        scan_ptr++;
    }

    exit(EXIT_SUCCESS);
}
