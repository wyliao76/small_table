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
    printf("user 0 takes seat 2, should return 2. FreeMap is 1011(11).\n");
    result = sit(&request);
    printf("Actual: %zd, %d.\n\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 1;
    printf("user 1 takes seat 0, should return 0, FreeMap is 1010(10).\n");
    result = sit(&request);
    printf("Actual: %zd, %d.\n\n", result, request.table->freeMap);

    request.index      = 1;
    request.session_id = 1;
    printf("duplicate user 1 takes seat 1, should return -3, FreeMap is 1010(10).\n");
    result = sit(&request);
    printf("Actual: %zd, %d.\n\n", result, request.table->freeMap);

    request.index      = 3;
    request.session_id = 2;
    printf("user 2 takes seat 3, should return 3, FreeMap is 0010(2).\n");
    result = sit(&request);
    printf("Actual: %zd, %d.\n\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 3;
    printf("user 3 takes seat 0, should return remaining seat 1, FreeMap is 0000.\n");
    result = sit(&request);
    printf("Actual: %zd, %d.\n\n", result, request.table->freeMap);

    request.index      = 0;
    request.session_id = 4;
    printf("user 4 takes seat 0, should return -1, FreeMap is 0000.\n");
    result = sit(&request);
    printf("Actual: %zd, %d.\n\n", result, request.table->freeMap);

    request.index      = 4;
    request.session_id = 4;
    printf("user 4 takes seat 4, should return -2, FreeMap is 0000.\n");
    result = sit(&request);
    printf("Actual: %zd, %d.\n\n", result, request.table->freeMap);

    request.index      = 2;
    request.session_id = 2;
    printf("remove user 2 from seat 2, should return -3.\n");
    result = un_sit(&request);
    printf("Actual: %zd\n\n", result);

    request.index      = 4;
    request.session_id = 2;
    printf("remove user 2 from seat 4, should return -2.\n");
    result = un_sit(&request);
    printf("Actual: %zd\n\n", result);

    request.index      = 2;
    request.session_id = 0;
    printf("remove user 0 from seat 2, should return 0, FreeMap is 0100(4).\n");
    result = un_sit(&request);
    printf("Actual: %zd, %d.\n\n", result, request.table->freeMap);

    request.index      = 2;
    request.session_id = 0;
    printf("remove user 2 from seat 2, should return -1.\n");
    result = un_sit(&request);
    printf("Actual: %zd\n\n", result);

    request.index      = 0;
    request.session_id = 4;
    printf("user 4 takes seat 0, should return 2, FreeMap is 0.\n");
    result = sit(&request);
    printf("Actual: %zd, %d.\n\n", result, request.table->freeMap);

    request.index = 4;
    printf("check who seats at seat 4, should return -1.\n");
    result = get_u_seat(&request);
    printf("Actual: %zd\n\n", result);

    request.index = 2;
    printf("check who seats at seat 0, should return 4.\n");
    result = get_u_seat(&request);
    printf("Actual: %zd\n\n", result);

    return EXIT_SUCCESS;
}
