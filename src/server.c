#include "../include/table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    table_t   table;
    request_t request;
    ssize_t   result;

    table.freeMap = EMPTY;
    memset(&table.seats, 0, NUM_OF_SEATS);

    printf("%d\n", table.freeMap);

    request.table      = &table;
    request.index      = 0;
    request.session_id = 0;

    result = sit(&request);
    printf("%zd, %d\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 1;

    result = sit(&request);
    printf("%zd, %d\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 2;

    result = sit(&request);
    printf("%zd, %d\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 3;

    result = sit(&request);
    printf("%zd, %d\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 4;

    result = sit(&request);
    printf("%zd, %d\n", result, request.table->freeMap);

    request.index      = 4;
    request.session_id = 4;

    result = sit(&request);
    printf("%zd, %d\n", result, request.table->freeMap);

    return EXIT_SUCCESS;
}
