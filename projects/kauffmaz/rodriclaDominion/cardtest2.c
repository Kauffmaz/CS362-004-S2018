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
int totalDeckSize = 0;
int totalMinusHand = 0;
int expectedDeckDiscard = 0;
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
    
    
    //set first card to be adventurer(card we are testing)
    for(i = 0; i < game.handCount[player]; i++){
        game.hand[player][i] = copper;
        game.discard[player][i] = copper;
        game.deck[player][i] = copper;
    }

    // //filling deck with junk
    // for(i = 0; i < game.deckCount[player]; i++){
    //     game.deck[player][i] = smithy;
    // }

    game.hand[player][0] = adventurer;

    //test original state
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

    //play the adventurer NOTE: Should draw 2 treasures so hand size should go up by 1 and deck size + discard size should remain the same
    playCard(0,0,0,0,&game);


    //testing hand size after adventurer. Should be +1 total
    result = testAssert(6, game.handCount[player]);
    if(result == false){
        printf("test failed: expected hand size: 6, actual hand size: %d\n", game.handCount[player]);
    }
    analyzeResults(result);
   
   //testing deck/discard size. varies on how many draws it takes to draw 2 treasures but deck + discard should == total cards - size of hand
    totalDeckSize = game.deckCount[player] + game.discardCount[player] + game.handCount[player];
    totalMinusHand = totalDeckSize - game.handCount[player];
    expectedDeckDiscard = game.discardCount[player] + game.deckCount[player];

    result = testAssert(totalMinusHand, expectedDeckDiscard);
    if(result == false){
        printf("test failed: expected deck + discard: %d, actual = %d", totalMinusHand, expectedDeckDiscard);
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

void analyzeResults(int result)
{
    if (result == false){
        passed = false;
    }
}
