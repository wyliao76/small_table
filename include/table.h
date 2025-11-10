#ifndef TABLE_H
#define TABLE_H

#include <../include/player.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define BITMAP_BYTES ((NUM_OF_SEATS + EIGHT - 1) / EIGHT)
// #define BIT_ALL_CLEAR(map)  ((map) = 0)


enum
{
    NUM_OF_TABLES  = 2,
    NUM_OF_SEATS = 10,
    EIGHT = 8,
    EMPTY = 0xFF,
};

// static const uint8_t FREE_MAP_ZERO[BITMAP_BYTES]  = {0x00};
// static uint8_t *FREEMAP_EMPTY = NULL;

static inline uint64_t BIT(uint8_t n)
{
    return (n < EIGHT) ? (1U << n) : 0U;
}

static inline uint8_t BIT_IS_SET(const uint8_t map, uint8_t n)
{
    return map & (uint8_t)BIT(n);
}

static inline uint8_t BIT_IS_CLEAR(const uint8_t map, uint8_t n)
{
    return !(map & (uint8_t)BIT(n));
}

static inline void BIT_SET(uint8_t *map, uint8_t n)
{
    *map |= (uint8_t)BIT(n);
}

static inline void BIT_CLEAR(uint8_t *map, uint8_t n)
{
    *map &= (uint8_t)~BIT(n);
}

static inline void BIT_ALL_SET(uint8_t *map, uint8_t nbits)
{
    // set full bytes
    size_t nbytes;
    size_t rem;

    nbytes = nbits / EIGHT;
    rem    = nbits % EIGHT;
    memset(map, EMPTY, nbytes);

    // set rest bits
    if (rem)
    {
        map[nbytes] = (uint8_t) ((1U << rem) - 1);
    }
}

// a table has 4 seats, could support up to EIGHT seats
typedef struct table_t
{
    // 1 is free, 0 is taken.
    uint8_t freeMap[BITMAP_BYTES];
    uint32_t seats[NUM_OF_SEATS];
    // player_t *seats[NUM_OF_SEATS]; // or pointers
} table_t;

typedef struct request_t
{
    table_t *table;
    uint8_t index;
    player_t *player;
} request_t;

void table_init(table_t *tables);

ssize_t sit(void *args);

ssize_t un_sit(void *args);

ssize_t get_player(void *args);

#endif    // TABLE_H
