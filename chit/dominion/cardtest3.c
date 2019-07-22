/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: cardtest3.c
 * Description: Unit test for dominion game.
 * Test function: endTurn
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "endTurn"

// assert helper function
void assertCheck(int A, int B, int testNum);

int main() {
	
	int seed = rand() % 1000 + 1;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState beforeState;
	int k[10] = { baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };
	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----- Test 1 -----
	printf("TEST 1: Check if current player is changed after endTurn is called\n");
	printf("Check current player after calling endTurn\n");
	printf("current player before calling endTurn: %d\n", thisPlayer);
	endTurn(&beforeState);
	printf("current player after calling endTurn: %d\n", whoseTurn(&beforeState));
	assertCheck(thisPlayer, whoseTurn(&beforeState) -1, 1);

	return 0;
}

void assertCheck(int A, int B, int testNum)
{
	if (A == B)
		printf("Test %d passed\n", testNum);
	else
		printf("Test %d failed\n", testNum);
}


