#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

enum
{
    NUM_OF_PLAYERS = 8,
};

typedef struct player_t
{
    uint8_t id;
} player_t;

#endif    // PLAYER_H
