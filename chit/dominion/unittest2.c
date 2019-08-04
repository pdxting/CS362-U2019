/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: unittest2.c
 * Description: Unit test for dominion game.
 * Test function: minionAction
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Minion"

// assert helper function
void assertCheck(int A, int B, int testNum);

int main() {

    int choice1 = 0;
	int choice2 = 0;
	int handPos = 0;
	int seed = rand() % 1000 + 1;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState beforeState, afterState;
	int k[10] = {baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village};

	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTCARD);

	// ----- Test 1 -----
	printf("TEST 1: Player chooses to get two coins, check if correct coins are added\n");

	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	choice1 = 1;
	minionAction(&afterState, thisPlayer, choice1, choice2, handPos);

	printf("Coin count = %d, Expected = %d\n", afterState.coins, beforeState.coins + 2);
	assertCheck(afterState.coins, beforeState.coins + 2, 1);

	// ----- Test 2 -----
	printf("TEST 2: Player chooese to redraw. Check to see all other players have four cards\n");

	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 1;

	for (int i = 0; i < afterState.numPlayers; i++)
	{
		afterState.handCount[i] = 5;
	}

	minionAction(&afterState, thisPlayer, choice1, choice2, handPos);

	for (int i = 0; i < beforeState.numPlayers; i++)
	{
		if (i != thisPlayer)
		{
			printf("Player %d card count = %d, Expected = 4\n", i, afterState.handCount[i]);
			assertCheck(afterState.handCount[i], 4, 2);
		}
	}

	return 0;
}

void assertCheck(int A, int B, int testNum)
{
	if (A == B)
		printf("Test %d passed\n\n", testNum);
	else
		printf("Test %d failed\n\n", testNum);
}


