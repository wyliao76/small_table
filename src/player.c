#include "../include/player.h"
#include "stdio.h"

void player_init(player_t *players)
{
    for(int i = 0; i < NUM_OF_PLAYERS; ++i)
    {
        players[i].id = (uint32_t)i;

        printf("player %d : %u\n", i, players[i].id);
    }
}
