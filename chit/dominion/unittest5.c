/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: unittest5.c
 * Description: Unit test for dominion game.
 * Test function: mineAction
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Mine"

// assert helper function
void assertCheck(int A, int B, int testNum);

int main() {

	int seed = rand() % 1000 + 1;
    int numPlayers = 2;
    int thisPlayer = 0;
	int choice1 = 0;
	int choice2 = 0;
	int handPos = 0;
	int returnValue = 0;
	struct gameState beforeState, afterState;
	int k[10] = {baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village};

	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTCARD);

	// ----- Test 1 -----
	printf("TEST 1: Check if choice1 is less than copper or greater than gold\n");
	
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	
	choice1 = 3;
	returnValue = mineAction(&afterState, thisPlayer, choice1, choice2, handPos);
	printf("Choice1 is less than copper\n");
	printf("Expecting return value of -1\n");
	assertCheck(returnValue, -1, 1);
	
	choice1 = 7;
	returnValue = mineAction(&afterState, thisPlayer, choice1, choice2, handPos);
	printf("Choice1 is greater than gold\n");
	printf("Expecting return value of -1\n");
	assertCheck(returnValue, -1, 1);

	// ----- Test 2 -----
	printf("TEST 2: Check if choice2 is less than treasure_map or greater than curse\n");

	memcpy(&afterState, &beforeState, sizeof(struct gameState));

	choice1 = 0;
	choice2 = -1;
	returnValue = mineAction(&afterState, thisPlayer, choice1, choice2, handPos);
	printf("Choice2 is less than curse\n");
	printf("Expecting return value of -1\n");
	assertCheck(returnValue, -1, 2);

	choice2 = 27;
	returnValue = mineAction(&afterState, thisPlayer, choice1, choice2, handPos);
	printf("Choice1 is greater than treasure_map\n");
	printf("Expecting return value of -1\n");
	assertCheck(returnValue, -1, 2);

	// ----- Test 3 -----
	printf("TEST 3: Check if choice1 card plus 3 copper is worth more than choice2 card\n");

	memcpy(&afterState, &beforeState, sizeof(struct gameState));

	choice1 = 6;
	choice2 = 0;
	returnValue = mineAction(&afterState, thisPlayer, choice1, choice2, handPos);
	printf("Choice1 plus 3 copper is worth more than choice2\n");
	printf("Expecting return value of -1\n");
	assertCheck(returnValue, -1, 3);

	// ----- Test 4 -----
	printf("TEST 4: Check if one card is discarded\n");

	memcpy(&afterState, &beforeState, sizeof(struct gameState));

	choice1 = 6;
	choice2 = 7;
	returnValue = mineAction(&afterState, thisPlayer, choice1, choice2, handPos);
	
	printf("Player %d card number before discarding trashed card: %d\n", thisPlayer, beforeState.discardCount[thisPlayer]);
	printf("Player %d card number after discarding trashed card: %d\n", thisPlayer, afterState.discardCount[thisPlayer]);
	printf("Expecting one card less\n");
	assertCheck(afterState.discardCount[thisPlayer], beforeState.discardCount[thisPlayer] -1, 4);


	return 0;
}

void assertCheck(int A, int B, int testNum)
{
	if (A == B)
		printf("Test %d passed\n\n", testNum);
	else
		printf("Test %d failed\n\n", testNum);
}


