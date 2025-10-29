#ifndef TABLE_H
#define TABLE_H

#include <../include/player.h>
#include <stdint.h>
#include <unistd.h>


enum
{
    NUM_OF_SEATS = 4,
    EMPTY = 0x0F
};

// a table has 4 seats, could support up to 8 seats
typedef struct table_t
{
    // 1111 is default, 1 is free, 0 is taken.
    uint8_t freeMap;
    uint8_t seats[NUM_OF_SEATS];
} table_t;

typedef struct request_t
{
    table_t *table;
    uint8_t index;
    player_t *player;
} request_t;

ssize_t sit(void *args);

ssize_t un_sit(void *args);

ssize_t get_u_seat(void *args);

#endif    // TABLE_H
