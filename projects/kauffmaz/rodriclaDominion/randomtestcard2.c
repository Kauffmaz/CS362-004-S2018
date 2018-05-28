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
int greathallPos(int p, struct gameState *g);
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

    printf("\n ***Great Hall TEST*** \n");

    for (i = 0; i < NUM_TESTS; i++)
    {
        printf("Test #%d\n", i+1);
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
        
        //save a copy of the state to compare
        memcpy(&endState, &startState, sizeof(struct gameState));
        
        int greatHallLoc = greathallPos(player, &startState);
        //check if great hall is in the hand
        if (greatHallLoc != -1){
            playCard(greatHallLoc,0,0,0,&endState);
        } else {
            printf("ERROR: hand does not contain great hall\n");
            failedTests += 1;
            continue;
        }
        
        
        
    {
        // Hand size should stay the same (+1 card and discard great hall)
        if (startState.handCount[player] != endState.handCount[player])
        {
            failure = true;
            printf("FAILED TEST (hand count) EXPECTED: %d ACTUAL: %d\n",startState.handCount[player], endState.handCount[player]);
        }
       // Discard deck should increase by 1 (great hall discarded)
       if(startState.discardCount[player] + 1 != endState.discardCount[player]){
           failure = true;
           printf("FAILED TEST (discard count) EXPECTED: %d ACTUAL: %d\n",startState.discardCount[player] + 1, endState.discardCount[player]);
       }
        if(startState.numActions != endState.numActions){
           failure = true;
           printf("FAILED TEST (action count) EXPECTED: %d ACTUAL: %d\n",startState.numActions, endState.numActions);
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

int greathallPos(int p, struct gameState *g) {
	int i;
	for (i = 0; i < g->handCount[p]; i++) {
		if (g->hand[p][i] == great_hall)
			return i;
	}
	return -1;
}