#include "../include/table.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

void table_init(table_t *table)
{
    BIT_ALL_SET(table->freeMap, NUM_OF_SEATS);
    memset(table->seats, 0, NUM_OF_SEATS * sizeof(table->seats[0]));
}

// return -3, -2, -1, 0 to NUM_OF_SEATS - 1
ssize_t sit(void *args)
{
    request_t *request = (request_t *)args;
    size_t     nbytes;

    nbytes = (NUM_OF_SEATS + EIGHT - 1) / EIGHT;

    // validate input
    if(request->index >= NUM_OF_SEATS)
    {
        printf("Invalid index %d\n", request->index);
        return -2;
    }

    // check if full
    if(*request->table->freeMap == 0)
    {
        printf("Table is full.\n");
        return -1;
    }

    // check duplicate
    for(size_t i = 0; i < nbytes; ++i)
    {
        // seat is taken
        if(BIT_IS_CLEAR(request->table->freeMap[i], (uint8_t)i))
        {
            printf("The seat %zu was taken. Checking the duplicate user...\n", i);
            // check the user
            if(request->table->seats[i] == request->player->id)
            {
                printf("User %u already sit at the table.\n", request->player->id);
                return -3;
            }
        }
    }

    // if free
    if(BIT_IS_SET(request->table->freeMap[request->index / EIGHT], request->index % EIGHT))
    {
        printf("The seat %d is free.\n", request->index);
    }
    else
    {
        // not free find a slot
        printf("The seat %d was taken", request->index);
        for(size_t i = 0; i < nbytes; ++i)
        {
            size_t bit = (size_t)ffs(request->table->freeMap[i]);
            if(bit)
            {
                request->index = (uint8_t)((i * EIGHT) + (bit - 1));    // absolute seat index
                break;
            }
        }
        printf(", allocate to seat %d.\n", request->index);
    }

    // clear the bit. [0 and 0 = 0], [1 and 0 = 0].
    BIT_CLEAR(&request->table->freeMap[request->index / EIGHT], request->index % EIGHT);
    // update seats
    request->table->seats[request->index] = request->player->id;

    return request->index;
}

ssize_t un_sit(void *args)
{
    request_t *request = (request_t *)args;
    size_t     nbytes;

    nbytes = request->index / EIGHT;

    // validate input
    if(request->index >= NUM_OF_SEATS)
    {
        printf("Invalid index %d.\n", request->index);
        return -2;
    }

    // if seat was free
    if(BIT_IS_SET(request->table->freeMap[nbytes], request->index % EIGHT))
    {
        printf("Seat %d is empty.\n", request->index);
        return -1;
    }

    // validate user
    if(request->table->seats[request->index] != request->player->id)
    {
        printf("User id mismatch was %u.\n", request->table->seats[request->index]);
        return -3;
    }
    // set the bit. [0 or 1 = 1], [1 or 1 = 1].
    BIT_SET(&request->table->freeMap[nbytes], request->index % EIGHT);
    // update seats
    request->table->seats[request->index] = 0;
    printf("Remove user %u from seat %d.\n", request->player->id, request->index);
    return 0;
}

// get user from seat
ssize_t get_player(void *args)
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
