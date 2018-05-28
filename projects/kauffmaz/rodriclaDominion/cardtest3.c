#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testAssert(int, int);
void analyzeResults(int);
typedef enum {false = 0, true = 1} boolean;
int passed = true;
int result;
int main(){
	struct gameState game;
    int result, i;
    int player = 0;
    int player2 = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    initializeGame(2, k, 2, &game);
    //set arbirtrary hand/discard/deck sizes
    game.handCount[player] = 5;
    game.discardCount[player] = 5;
    game.deckCount[player] = 5;
    game.handCount[player2] = 5;
    game.discardCount[player2] = 5;
    game.deckCount[player2] = 5;
    
    //set hand to 4 coins and 1 cutpurse for each player
    for(i = 0; i < game.handCount[player]; i++){
        game.hand[player][i] = silver;
    }
    for(i = 0; i < game.handCount[player2]; i++){
        game.hand[player2][i] = copper;
    }
    game.hand[player][0] = cutpurse;
    game.hand[player2][0] = cutpurse;

    //check original game state NOTE: player 1 should have 8 coins, player 2 should have 4 coins
    updateCoins(player, &game, 0);
    result = testAssert(8, game.coins);
    if(result == false){
        printf("TEST FAILED: expected coins = 8, actual coins = %d\n", game.coins);
        passed = false;
    }
    updateCoins(player2, &game, 0);
    result = testAssert(4, game.coins);
    if(result == false){
        printf("TEST FAILED: expected coins = 4, actual coins = %d\n", game.coins);
        passed = false;
    }

    //player 1 plays cutpurse
    playCard(0,0,0,0,&game);

    //player1 should have 10 coins
    result = testAssert(10, game.coins);
    if(result == false){
        printf("TEST FAILED: expected coins = 10, actual coins = %d\n", game.coins);
        passed = false;
    }
    //player 2 should have 3 coins (1 discarded)
    updateCoins(player2, &game, 0);
    result = testAssert(3, game.coins);
    if(result == false){
        printf("TEST FAILED: expected coins = 3, actual coins = %d\n", game.coins);
        passed = false;
    }

    //update player 2 to have no copper to discard
    for(i = 0; i < game.handCount[player2]; i++){
        game.hand[player2][i] = smithy;
    }
    
    updateCoins(player2, &game, 0);
    result = testAssert(0, game.coins);
    if(result == false){
        printf("TEST FAILED: expected coins = 0, actual coins = %d\n", game.coins);
        passed = false;
    }


	if(passed == true){
        printf("ALL TESTS PASSED\n");
    }
    else{
        printf("TEST FAILED\n");
    }
	return 0;
}

int testAssert(int expected, int actual){
    return expected == actual;
}

