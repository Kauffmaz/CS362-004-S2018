#include "dominion.h"
#include "interface.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_TESTS 1500
typedef enum {false = 0, true = 1} boolean;
typedef struct gameState gameState;

int main()
{
    int passedTests, failedTests;
    int cards[10] = {minion, mine, cutpurse, sea_hag, tribute, smithy, adventurer, gardens, embargo, village};
    int i, j, player, players, handCount, randomSeed, treasureCount, count;
    

    srand(time(NULL));

    gameState state;

    passedTests = 0;
    failedTests = 0;
    count = 0;

    printf("\n ***ADVENTURER TEST*** \n");

    for (i = 0; i < NUM_TESTS; i++)
    {
        printf("Test #%d\n", i);
        count++;
        randomSeed = rand() % 50 + 1;
        players = rand() % 4 + 1;
        int actualTreasure = 0;
        int currentPlayer = state.whoseTurn;
        int failure = 0;

        
            initializeGame(players, cards, randomSeed, &state); // init the game
            for (j = 0; j < players; j++)
            {
                // loop through each player and give them random values
                state.handCount[j] = rand() % MAX_HAND;
                state.deckCount[j] = rand() % MAX_DECK;
                state.discardCount[j] = rand() % MAX_DECK;
            }
            state.whoseTurn = player; 
            // deckCountPre = state.deckCount[player];
            // discardCountPre = state.discardCount[player]; // preserve discarded card value
            treasureCount = countHandCoins(player, &state);
            // get the original hand count
            handCount = numHandCards(&state);
            // play the adventurer
            testAdventurer(player, &state);
            
            
    {
        // check if player drew 2 cards
        if (handCount + 2 != state.handCount[currentPlayer])
        {
            failure = true;
            printf("FAILED TEST (hand count) EXPECTED: %d ACTUAL: %d\n",handCount + 2, state.handCount[currentPlayer]);
        }
        // do some math check if the discard count is correct
        actualTreasure = countHandCoins(state.whoseTurn, &state);
        if (treasureCount != actualTreasure)
        {
            failure = true;
            printf("FAILED TEST (treasure count) EXPECTED: %d ACTUAL: %d\n",treasureCount, actualTreasure);
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