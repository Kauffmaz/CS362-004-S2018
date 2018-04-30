#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testAssert(int, int);
void analyzeResults(int);
typedef enum { false = 0,
               true = 1 } boolean;
int MIN_HAND;
int passed = true;

int main()
{
    struct gameState game;
    int player = 0;
    
    int result, i;
    int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int pointCards[6] = {curse, estate, duchy, province, great_hall, gardens};
    initializeGame(2, k, 2, &game);

    
    //testing score from hand - setting hand size to 5, setting hand to "value" cards - discard and deck to "no-value" cards
    game.handCount[player] = 6;
    game.discardCount[player] = 6;
    game.deckCount[player] = 6;
    for(i = 0; i < game.handCount[player]; i++)
    {
      game.hand[player][i] = estate;
      game.discard[player][i] = smithy;
      game.deck[player][i] = smithy;
    }

    int score = scoreFor(player,&game);
    result = testAssert(6, score);
    analyzeResults(result);

    //testing score from discard - discard filled with "value" cards - deck and hand set to "no-value" cards
    for(i = 0; i < game.discardCount[player]; i++)
    {
      game.hand[player][i] = smithy;
      game.discard[player][i] = estate;
      game.deck[player][i] = smithy;
    }
    score = scoreFor(player,&game);
    result = testAssert(6, score);
    analyzeResults(result);

    //testing score from deck - deck filled with "value" cards - hand and discard filled with "no-value" cards
    for(i = 0; i < game.deckCount[player]; i++)
    {
      game.hand[player][i] = smithy;
      game.discard[player][i] = smithy;
      game.deck[player][i] = estate;
    }
    score = scoreFor(player,&game);
    result = testAssert(6, score);
    analyzeResults(result);

    //testing values of all "score cards"

    for(i = 0; i < game.deckCount[player]; i++)
    {
        game.hand[player][i] = pointCards[i];
        game.discard[player][i] = pointCards[i];
        game.deck[player][i] = pointCards[i];
        
        
        
    }

    score = scoreFor(player,&game);
    result = testAssert(31, score);
    analyzeResults(result);


    //testing my own curiosity
    game.handCount[player] = 100;
    game.discardCount[player] = 100;
    game.deckCount[player] = 100;
    for(i = 0; i < game.deckCount[player]; i++)
    {
      game.hand[player][i] = gardens;
      game.discard[player][i] = gardens;
      game.deck[player][i] = gardens;
    }
    score = scoreFor(player,&game);
    result = testAssert(100, score);
    analyzeResults(result);

    if (passed == true)
    {
        printf("Tests passed\n");
    }
    else
    {
        printf("Tests failed\n");
    }
    

    return 0;
}

int testAssert(int expected, int actual)
{
    if(expected != actual){
        printf("Assertion failed: expected: %d != calculated: %d\n", expected, actual);
    }
    return expected == actual;
}

void analyzeResults(int result)
{
    if (result == false){
        passed = false;
    }
}