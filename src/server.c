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
    printf("Should be 15. Actual: %d\n", table.freeMap);

    request.table = &table;

    request.index      = 2;
    request.session_id = 0;
    result             = sit(&request);
    printf("user 0 takes seat 2, should return 2. FreeMap is 1011(11) Actual: %zd, %d\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 1;
    result             = sit(&request);
    printf("user 1 takes seat 0, should return 0, FreeMap is 1010(10), Actual: %zd, %d\n", result, request.table->freeMap);

    request.index      = 1;
    request.session_id = 1;
    result             = sit(&request);
    printf("duplicate user 1 takes seat 1, should return -3, FreeMap is 1010(10), Actual: %zd, %d\n", result, request.table->freeMap);

    request.index      = 3;
    request.session_id = 2;
    result             = sit(&request);
    printf("user 2 takes seat 3, should return 3, FreeMap is 0010(2), Actual: %zd, %d\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 3;
    result             = sit(&request);
    printf("user 3 takes seat 0, should return remaining seat 1, FreeMap is 0000, Actual: %zd, %d\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 4;
    result             = sit(&request);
    printf("user 4 takes seat 0, should return -1, FreeMap is 0000, Actual: %zd, %d\n", result, request.table->freeMap);

    request.index      = 4;
    request.session_id = 4;
    result             = sit(&request);
    printf("user 4 takes seat 4, should return -2, FreeMap is 0000, Actual: %zd, %d\n", result, request.table->freeMap);

    request.index      = 2;
    request.session_id = 2;
    result             = un_sit(&request);
    printf("remove user 2 from seat 2, should return -3, Actual: %zd\n", result);

    request.index      = 4;
    request.session_id = 2;
    result             = un_sit(&request);
    printf("remove user 2 from seat 4, should return -2, Actual: %zd\n", result);

    request.index      = 2;
    request.session_id = 0;
    result             = un_sit(&request);
    printf("remove user 0 from seat 2, should return 0, FreeMap is 0100(4), Actual: %zd, %d\n", result, request.table->freeMap);

    request.index      = 2;
    request.session_id = 0;
    result             = un_sit(&request);
    printf("remove user 2 from seat 2, should return -1, Actual: %zd\n", result);

    request.index      = 0;
    request.session_id = 4;
    result             = sit(&request);
    printf("user 4 takes seat 0, should return 2, FreeMap is 0, Actual: %zd, %d\n", result, request.table->freeMap);

    request.index = 4;
    result        = get_u_seat(&request);
    printf("check who seats at seat 4, should return -1. Actual: %zd\n", result);

    request.index = 2;
    result        = get_u_seat(&request);
    printf("check who seats at seat 0, should return 4. Actual: %zd\n", result);

    return EXIT_SUCCESS;
}
