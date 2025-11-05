#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

enum
{
    NUM_OF_PLAYERS = 8,
};

typedef struct player_t
{
    uint32_t id;
    uint16_t server_id;
    uint16_t table_id;
} player_t;

#endif    // PLAYER_H
