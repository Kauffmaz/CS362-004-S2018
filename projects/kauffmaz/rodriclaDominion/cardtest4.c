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
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    initializeGame(2, k, 2, &game);
    //set arbirtrary hand/discard/deck sizes
    game.handCount[player] = 5;
    game.discardCount[player] = 5;
    game.deckCount[player] = 5;
    
    //fill hand with arbitrary cards + 1 great_hall
    for(i = 0; i < game.handCount[player]; i++){
       if(i == 0){
            game.hand[player][i] = great_hall;
       }
       else{
            game.hand[player][i] = copper;
       }   
    }
    
    //test original hand size (should be 5)
    result = testAssert(5, game.handCount[player]);
    if (result == false){
        printf("TEST FAILED: expected hand size = 5, actual hand size = %d\n", game.handCount[player]);
        passed = false;
    }
    //test original action count (should be 1)
    result = testAssert(1, game.numActions);
    if (result == false){
        printf("TEST FAILED: expected actions = 1, actual actions = %d", game.numActions);
        passed = false;
    }

    //play the great_hall NOTE: great hall basically replaces itself - you spend your action and card to get another action and another card
    //so hand and actions should still be 5/1
    playCard(0,0,0,0,&game);

    //test handsize after great hall played (should be 5)
    result = testAssert(5, game.handCount[player]);
    if (result == false){
        printf("TEST FAILED: expected hand size = 5, actual hand size = %d\n", game.handCount[player]);
        passed = false;
    }
    //test action count after great hall played (should be 1)
    result = testAssert(1, game.numActions);
    if (result == false){
        printf("TEST FAILED: expected actions = 1, actual actions = %d\n", game.numActions);
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