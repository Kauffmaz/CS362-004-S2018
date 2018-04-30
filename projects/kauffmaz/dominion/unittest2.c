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
int MIN_HAND, totalTests, passedTests, failedTests = 0;
int passed = true;

int main()
{
    struct gameState game;
    
    int result, i;
    int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    initializeGame(2, k, 2, &game);

    //testing isGameOver for number of province > 0
    //expecting isGameOver to return 0
    for (i = 1; i < MAX_DECK; i++)
    {
        game.supplyCount[province] = i;
        result = testAssert(0, isGameOver(&game));
        analyzeResults(result);
    }

    //testing province == 0
    //expecting isGameOver to return 1
    game.supplyCount[province] = 0;
    result = testAssert(1, isGameOver(&game));
    analyzeResults(result);

    //testing supply piles full
    //expecting isGameOver to return 0
    for (i = 0; i < 12; i++)
    {
        game.supplyCount[i] = 5;
    }
    game.supplyCount[province] = 5;
    result = testAssert(0, isGameOver(&game));
    analyzeResults(result);

    //testing 1, 2 supply piles empty
    //expecting isGameOver to return 0
    for (i = 0; i < 2; i++)
    {
        game.supplyCount[i] = 0;
        result = testAssert(0, isGameOver(&game));
        analyzeResults(result);
    }
    
    //testing 3 supply piles empty
    //expecting isGameOver to return 1
    for (i = 0; i < 12; i++)
    {   
        if(i < 3){
            game.supplyCount[i] = 0;
        }
        else{
            game.supplyCount[i] = 5;
        }
    }
    result = testAssert(1, isGameOver(&game));
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
    return expected == actual;
}

void analyzeResults(int result)
{
    if (result == false){
        passed = false;
    }
}
// int isGameOver(struct gameState *state) {
//   int i;
//   int j;

//   //if stack of Province cards is empty, the game ends
//   if (state->supplyCount[province] == 0)
//     {
//       return 1;
//     }

//   //if three supply pile are at 0, the game ends
//   j = 0;
//   for (i = 0; i < 25; i++)
//     {
//       if (state->supplyCount[i] == 0)
// 	{
// 	  j++;
// 	}
//     }
//   if ( j >= 3)
//     {
//       return 1;
//     }

//   return 0;
// }