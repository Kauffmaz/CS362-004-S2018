#include "dominion.h"
#include "interface.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define NUM_TESTS 5000
int smithyPos(int p, struct gameState *g);
typedef enum {false = 0, true = 1} boolean;
typedef struct gameState gameState;

int main()
{
    int passedTests, failedTests;
    int cards[10] = {minion, mine, cutpurse, sea_hag, tribute, smithy, adventurer, gardens, embargo, village};
    int i, player, players, randomSeed, count;
    

    srand(time(NULL));

    gameState startState;
    gameState endState;
    passedTests = 0;
    failedTests = 0;
    count = 0;

    printf("\n ***Smithy TEST*** \n");

    for (i = 0; i < NUM_TESTS; i++)
    {
        printf("Test #%d\n", i);
        count++;
        randomSeed = rand() % 50 + 1;
        players = rand() % 4 + 1;
        int failure = false;
        player = 1;
        
        initializeGame(players, cards, randomSeed, &startState); 
            
        //randomize the hand/deck/discard piles
        startState.handCount[1] = rand() % MAX_HAND;
        startState.deckCount[1] = rand() % MAX_DECK;
        startState.discardCount[1] = rand() % MAX_DECK;
        int k;
        for (k = 0; k <startState.deckCount[1]; k++) {
            startState.deck[1][k] = rand() % 25;
        }
        for (k = 0; k <startState.discardCount[1]; k++) {
            startState.discard[1][k] = rand() % 25;
        }
        for (k = 0; k <startState.handCount[1]; k++) {
            startState.hand[1][k] = rand() % 25;
        }

        startState.whoseTurn = player; 
        // get the original hand count

        memcpy(&endState, &startState, sizeof(struct gameState));
        
        int smithyLoc = smithyPos(player, &startState);
        //check if smithy is in the hand and if it is - play it
        if (smithyLoc != -1){
            playCard(smithyLoc,0,0,0,&endState);
        } else {
            printf("ERROR: hand does not contain smithy\n");
            failedTests += 1;
            continue;
        }
        
        
        
    {
        // Smithy should draw a net of 2 cards (draw 3 discard smithy)
        if (startState.handCount[player] + 2 != endState.handCount[player])
        {
            failure = true;
            printf("FAILED TEST (hand count) EXPECTED: %d ACTUAL: %d\n",startState.handCount[player] + 2, endState.handCount[player]);
        }
       // Discard deck should increase by 1 (smithy discarded)
       if(startState.discardCount[player] + 1 != endState.discardCount[player]){
           failure = true;
           printf("FAILED TEST (discard count) EXPECTED: %d ACTUAL: %d\n",startState.discardCount[player] + 1, endState.discardCount[player]);
       }

        if (failure == true)
        {
            failedTests += 1;
        }
        else
        {
            passedTests += 1;
        }
    }
        }

    printf("\n *** TEST RESULTS *** \n");
    printf("Tests passed: %d\n", passedTests);
    printf("Tests failed: %d\n", failedTests);
    return 0;
}

int smithyPos(int p, struct gameState *g) {
	int i;
	for (i = 0; i < g->handCount[p]; i++) {
		if (g->hand[p][i] == smithy)
			return i;
	}
	return -1;
}