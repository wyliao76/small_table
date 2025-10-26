#include "../include/table.h"
#include <stdio.h>
#include <strings.h>

// return -2, -1, 0 to NUM_OF_SEATS - 1
ssize_t sit(void *args)
{
    request_t *request = (request_t *)args;

    // validate input
    if(request->index >= NUM_OF_SEATS)
    {
        printf("invalid input %d\n", request->index);
        return -2;
    }

    // check if full
    if(request->table->freeMap == 0)
    {
        printf("no more seats\n");
        return -1;
    }

    // if free
    if(request->table->freeMap & (1 << request->index))
    {
        printf("the seat is free\n");
    }
    else
    {
        // not free find a slot
        request->index = (uint8_t)(ffs(request->table->freeMap) - 1);
        printf("the seat is not free, found %d.\n", request->index);
    }
    // flip bit
    request->table->freeMap &= (uint8_t)~(1 << request->index);
    // update seats
    request->table->seats[request->index] = request->session_id;

    return request->index;
}

ssize_t un_sit(void *args)
{
    request_t *request = (request_t *)args;

    printf("%d, %d\n", request->table->freeMap, request->index);
    return 0;
}
