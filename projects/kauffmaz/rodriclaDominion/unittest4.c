#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testAssert(int, int);
typedef enum {false = 0, true = 1} boolean;
int passed = true;

int main(){
	
    int result, i, cost;
    
    int expectedValues[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};

    //testing cards cost against their expected cost
    for(i = 0; i < 27; i ++){
        cost = getCost(i);
        result = testAssert(expectedValues[i], cost);
        if(result == false){
            passed = false;
        }
    }
   //testing card costs against an "impossible" cost
   for(i = 0; i < 27; i++){
       cost = getCost(i);
       result = testAssert(-1, cost);
       if(result == true){
           passed = false;
       }
    }

    //testing getCost against a card that doesn't exist
    cost = getCost(999);
    result = testAssert(-1, cost);
    if(result == false){
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

void analyzeResults(int result)
{
    if (result == false){
        passed = false;
    }
}



// int getCost(int cardNumber)
// {
//   switch (cardNumber)
//   {
//   case curse:
//     return 0;
//   case estate:
//     return 2;
//   case duchy:
//     return 5;
//   case province:
//     return 8;
//   case copper:
//     return 0;
//   case silver:
//     return 3;
//   case gold:
//     return 6;
//   case adventurer:
//     return 6;
//   case council_room:
//     return 5;
//   case feast:
//     return 4;
//   case gardens:
//     return 4;
//   case mine:
//     return 5;
//   case remodel:
//     return 4;
//   case smithy:
//     return 4;
//   case village:
//     return 3;
//   case baron:
//     return 4;
//   case great_hall:
//     return 3;
//   case minion:
//     return 5;
//   case steward:
//     return 3;
//   case tribute:
//     return 5;
//   case ambassador:
//     return 3;
//   case cutpurse:
//     return 4;
//   case embargo:
//     return 2;
//   case outpost:
//     return 5;
//   case salvager:
//     return 4;
//   case sea_hag:
//     return 4;
//   case treasure_map:
//     return 4;
//   }

//   return -1;
// }