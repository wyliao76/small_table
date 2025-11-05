#include "../include/player.h"
#include "../include/table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void assert_freemap(const uint8_t *freeMap, size_t nbits)
{
    size_t nbytes;
    size_t rem;

    nbytes = nbits / EIGHT;
    rem    = nbits % EIGHT;

    for(size_t i = 0; i < nbytes; ++i)
    {
        assert(freeMap[i] == 0xFF);
    }
    if(rem)
    {
        assert(freeMap[nbytes] == (uint8_t)((1U << rem) - 1));
    }
}

int main(void)
{
    // Use stack for simplicity
    player_t  players[NUM_OF_PLAYERS];
    table_t   table;
    request_t request;
    ssize_t   result;

    for(int i = 0; i < NUM_OF_PLAYERS; ++i)
    {
        player_t player;
        player.id  = (uint32_t)i;
        players[i] = player;

        printf("player %d : %u\n", i, players[i].id);
    }

    table_init(&table);
    assert_freemap(table.freeMap, NUM_OF_SEATS);

    request.table = &table;

    request.index  = 2;
    request.player = &players[0];
    printf("player 0 takes seat 2, should return 2. FreeMap is 1011(11).\n");
    result = sit(&request);
    assert(result == 2);
    assert(*table.freeMap == 0xB);

    request.index  = 0;
    request.player = &players[1];
    printf("player 1 takes seat 0, should return 0, FreeMap is 1010(10).\n");
    result = sit(&request);
    assert(result == 0);
    assert(*table.freeMap == 0xA);

    request.index  = 1;
    request.player = &players[1];
    printf("duplicate player 1 takes seat 1, should return -3, FreeMap is 1010(10).\n");
    result = sit(&request);
    assert(result == -3);
    assert(*table.freeMap == 0xA);

    request.index  = 3;
    request.player = &players[2];
    printf("player 2 takes seat 3, should return 3, FreeMap is 0010(2).\n");
    result = sit(&request);
    assert(result == 3);
    assert(*table.freeMap == 0x2);

    request.index  = 0;
    request.player = &players[3];
    printf("player 3 takes seat 0, should return remaining seat 1, FreeMap is 0000.\n");
    result = sit(&request);
    assert(result == 1);
    assert(*table.freeMap == 0x0);

    request.index  = 0;
    request.player = &players[4];
    printf("player 4 takes seat 0, should return -1, FreeMap is 0000.\n");
    result = sit(&request);
    assert(result == -1);
    assert(*table.freeMap == 0x0);

    request.index  = 4;
    request.player = &players[4];
    printf("player 4 takes seat 4, should return -2, FreeMap is 0000.\n");
    result = sit(&request);
    assert(result == -2);
    assert(*table.freeMap == 0x0);

    request.index  = 2;
    request.player = &players[2];
    printf("remove player 2 from seat 2, should return -3.\n");
    result = un_sit(&request);
    assert(result == -3);

    request.index  = 4;
    request.player = &players[2];
    printf("remove player 2 from seat 4, should return -2.\n");
    result = un_sit(&request);
    assert(result == -2);

    request.index  = 2;
    request.player = &players[0];
    printf("remove player 0 from seat 2, should return 0, FreeMap is 0100(4).\n");
    result = un_sit(&request);
    assert(result == 0);
    assert(*table.freeMap == 0x4);

    request.index  = 2;
    request.player = &players[0];
    printf("remove player 0 from seat 2, should return -1.\n");
    result = un_sit(&request);
    assert(result == -1);

    request.index  = 0;
    request.player = &players[4];
    printf("player 4 takes seat 0, should return 2, FreeMap is 0.\n");
    result = sit(&request);
    assert(result == 2);
    assert(*table.freeMap == 0x0);

    request.index = 4;
    printf("check who seats at seat 4, should return -1.\n");
    result = get_player(&request);
    assert(result == -1);

    request.index = 2;
    printf("check who seats at seat 2, should return 4.\n");
    result = get_player(&request);
    assert(result == 4);

    return EXIT_SUCCESS;
}
