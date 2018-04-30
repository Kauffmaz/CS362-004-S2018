#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testAssert(int, int);
typedef enum {false = 0, true = 1} boolean;

int main(){
	struct gameState game;
	int passed = true;
    int totalTests, passedTests, failedTests = 0;	
    int result, i;


    //testing all expected hand sizes
    for(i = 0; i < MAX_HAND; i++){
        game.handCount[0] = i;
        result = testAssert(i, numHandCards(&game));
        if(result == false){
            passed = false;
            failedTests++;
        }
        else{
            passedTests++;
        }
        totalTests++;
    }
    //testing negative hand sizes
    for(i = -500; i < 0; i++){
        game.handCount[0] = i;
        result = testAssert(i, numHandCards(&game));
        if(result == false){
            passed = false;
            failedTests++;
        }
        else{
            passedTests++;
        }
        totalTests++;
    }
    //testing cases that should fail
    for(i = 0; i < MAX_HAND; i++){
        game.handCount[0] = i + 1;
        result = testAssert(i, numHandCards(&game));
        if(result == false){
            passed = true;
        }
        
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

