#ifndef TABLE_H
#define TABLE_H

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
    uint8_t freeMap;
    uint8_t seats[NUM_OF_SEATS];
} table_t;

typedef struct request_t
{
    table_t *table;
    uint8_t index;
    uint8_t session_id;
} request_t;

ssize_t sit(void *args);

ssize_t un_sit(void *args);

#endif    // TABLE_H
