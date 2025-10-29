#include "../include/table.h"
#include <stdio.h>
#include <strings.h>

// return -3, -2, -1, 0 to NUM_OF_SEATS - 1
ssize_t sit(void *args)
{
    request_t *request = (request_t *)args;

    // validate input
    if(request->index >= NUM_OF_SEATS)
    {
        printf("Invalid index %d\n", request->index);
        return -2;
    }

    // check if full
    if(request->table->freeMap == 0)
    {
        printf("Table is full.\n");
        return -1;
    }

    // check duplicate
    for(size_t i = 0; i < NUM_OF_SEATS; ++i)
    {
        // if the seat was taken [0 and 1 = 0].
        if(!(request->table->freeMap & (1 << i)))
        {
            printf("The seat %zu was taken. Checking the duplicate user...\n", i);
            // check the user
            if(request->table->seats[i] == request->player->id)
            {
                printf("User %d already sit at the table.\n", request->player->id);
                return -3;
            }
        }
    }

    // if free
    if(request->table->freeMap & (1 << request->index))
    {
        printf("The seat %d is free.\n", request->index);
    }
    else
    {
        // not free find a slot
        printf("The seat %d was taken", request->index);
        request->index = (uint8_t)(ffs(request->table->freeMap) - 1);
        printf(", allocate to seat %d.\n", request->index);
    }
    // clear the bit. [0 and 0 = 0], [1 and 0 = 0].
    request->table->freeMap &= (uint8_t)~(1 << request->index);
    // update seats
    request->table->seats[request->index] = request->player->id;

    return request->index;
}

ssize_t un_sit(void *args)
{
    request_t *request = (request_t *)args;

    // validate input
    if(request->index >= NUM_OF_SEATS)
    {
        printf("Invalid index %d.\n", request->index);
        return -2;
    }

    // if seat was free
    if(request->table->freeMap & (1 << request->index))
    {
        printf("Seat %d is empty.\n", request->index);
        return -1;
    }

    // validate user
    if(request->table->seats[request->index] != request->player->id)
    {
        printf("User id mismatch was %d.\n", request->table->seats[request->index]);
        return -3;
    }
    // set the bit. [0 or 1 = 1], [1 or 1 = 1].
    request->table->freeMap |= (uint8_t)(1 << request->index);
    // update seats
    request->table->seats[request->index] = 0;
    printf("Remove user %d from seat %d.\n", request->player->id, request->index);
    return 0;
}

// get user from seat
ssize_t get_u_seat(void *args)
{
    request_t *request = (request_t *)args;

    // validate input
    if(request->index >= NUM_OF_SEATS)
    {
        printf("Invalid index %d.\n", request->index);
        return -1;
    }

    return request->table->seats[request->index];
}
