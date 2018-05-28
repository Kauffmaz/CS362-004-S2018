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
    int result;
    int player = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    initializeGame(2, k, 2, &game);
    //set arbirtrary hand/discard/deck sizes
    game.handCount[player] = 5;
    game.discardCount[player] = 5;
    game.deckCount[player] = 5;

    //set first card to be smithy(card we are testing)
    game.hand[player][0] = smithy;

    //test original state
    //test hand size
    result = testAssert(5, game.handCount[player]);
    if(result == false){
        printf("test failed: expected hand size: 5, actual hand size: %d\n", game.handCount[player]);
    }
    analyzeResults(result);
    //test discard size
    result = testAssert(5, game.discardCount[player]);
    if(result == false){
        printf("test failed: expected discard size: 5, actual discard size: %d\n", game.discardCount[player]);
    }
    analyzeResults(result);
    //test deck size
    result = testAssert(5, game.deckCount[player]);
    if(result == false){
        printf("test failed: expected deck size: 5, actual deck size: %d\n", game.deckCount[player]);
    }
    analyzeResults(result);

    //play the smithy
    playCard(0,0,0,0,&game);


    //test game state after smithy NOTE: Smithy should draw 3 cards, and put the smithy into the discard pile
    //resulting in hand size +2, discard size +1, deck size -3
 
    result = testAssert(7, game.handCount[player]);
    if(result == false){
        printf("test failed: expected hand size: 7, actual hand size: %d\n", game.handCount[player]);
    }
    analyzeResults(result);
    //test discard size
    result = testAssert(6, game.discardCount[player]);
    if(result == false){
        printf("test failed: expected discard size: 6, actual discard size: %d\n", game.discardCount[player]);
    }
    analyzeResults(result);
    //test deck size
    result = testAssert(2, game.deckCount[player]);
    if(result == false){
        printf("test failed: expected deck size: 2, actual deck size: %d\n", game.deckCount[player]);
    }
    analyzeResults(result);


	if(passed == true){
        printf("ALL TESTS PASSED\n");
    }
    else{
        printf("TESTS FAILED\n");
    }
	return 0;
}

int testAssert(int expected, int actual){
    return expected == actual;
}

void analyzeResults(int result)
{
    if (result == false){
        passed = false;
    }
}

// for (i = 0; i < 3; i++)
//     {
//       drawCard(currentPlayer, state);
//     }

//     //discard card from hand
//     discardCard(handPos, currentPlayer, state, 0);
//     return 0;
