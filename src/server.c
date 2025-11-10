#include "../include/player.h"
#include "../include/table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Use stack for simplicity
    // 12 players
    // 2 tables 10 seats
    player_t  players[NUM_OF_PLAYERS];
    table_t   tables[NUM_OF_TABLES];
    request_t request;

    player_init(players);
    table_init(tables);
    // table 0
    assert(tables[0].freeMap[0] == 0xFF);
    assert(tables[0].freeMap[1] == 0x03);

    // table 1
    assert(tables[1].freeMap[0] == 0xFF);
    assert(tables[1].freeMap[1] == 0x03);

    request.table  = &tables[0];
    request.index  = 1;
    request.player = &players[0];
    printf("player 0 takes seat 1, should return 1. FreeMap is 1101(13).\n");
    assert(sit(&request) == 1);
    assert(tables[0].freeMap[0] == 0xFD);
    assert(tables[0].freeMap[1] == 0x03);

    request.index  = 0;
    request.player = &players[1];
    printf("player 1 takes seat 0, should return 0, FreeMap is 1100(12).\n");
    assert(sit(&request) == 0);
    assert(tables[0].freeMap[0] == 0xFC);
    assert(tables[0].freeMap[1] == 0x03);

    request.index  = 1;
    request.player = &players[1];
    printf("player 1 takes seat 0, should return -3 (duplicate player).\n");
    assert(sit(&request) == -3);
    assert(tables[0].freeMap[0] == 0xFC);
    assert(tables[0].freeMap[1] == 0x03);

    // 12 - 2, sit 10 players to table 0
    for(ssize_t i = 2; i < (NUM_OF_PLAYERS - 2); ++i)
    {
        request.index  = (uint8_t)i;
        request.player = &players[i];
        assert(sit(&request) == i);
    }

    assert(tables[0].freeMap[0] == 0);
    assert(tables[0].freeMap[1] == 0);

    // table should be full
    request.index  = 1;
    request.player = &players[NUM_OF_PLAYERS - 1];    // 11
    assert(sit(&request) == -1);

    // invalid index
    request.index  = NUM_OF_SEATS;                    // 10
    request.player = &players[NUM_OF_PLAYERS - 1];    // 11
    assert(sit(&request) == -2);

    request.index  = 0;
    request.player = &players[0];
    printf("remove player 0 from seat 0, should return -3 (mismatch).\n");
    assert(un_sit(&request) == -3);

    request.index  = NUM_OF_SEATS;
    request.player = &players[2];
    printf("remove player 2 from seat 10, should return -2 (invalid index).\n");
    assert(un_sit(&request) == -2);

    request.index  = 2;
    request.player = &players[2];
    printf("remove player 2 from seat 2, should return 0, FreeMap is 0100(4).\n");
    assert(un_sit(&request) == 0);
    assert(tables[0].freeMap[0] == 0x04);
    assert(tables[0].freeMap[1] == 0);

    request.index  = 2;
    request.player = &players[2];
    printf("remove player 2 from seat 2, should return -1 (seat is empty).\n");
    assert(un_sit(&request) == -1);

    request.index  = 0;
    request.player = &players[NUM_OF_PLAYERS - 1];    // 11
    printf("player 11 takes seat 0, should return 2, FreeMap is 0.\n");
    assert(sit(&request) == 2);
    assert(tables[0].freeMap[0] == 0);
    assert(tables[0].freeMap[1] == 0);

    request.index = NUM_OF_SEATS;    // 10
    printf("check who seats at seat 10, should return -1 (invalid index).\n");
    assert(get_player(&request) == -1);

    request.index = 2;
    printf("check who seats at seat 2, should return 11.\n");
    assert(get_player(&request) == 11);

    request.table  = &tables[1];
    request.index  = 2;
    request.player = &players[NUM_OF_PLAYERS - 2];    // 10
    printf("player 10 takes seat 2, should return 2. FreeMap is 1011(11).\n");
    assert(sit(&request) == 2);
    assert(tables[1].freeMap[0] == 0xFB);
    assert(tables[1].freeMap[1] == 0x03);

    request.index = 2;
    printf("check who seats at seat 2, should return 10.\n");
    assert(get_player(&request) == 10);

    // todo
    // request.index  = 0;
    // request.player = &players[NUM_OF_PLAYERS - 1];    // 11
    // printf("player 11 takes seat 0 at table 1, should return -4 (player already sit at different table).\n");
    // assert(sit(&request) == -4);

    return EXIT_SUCCESS;
}
