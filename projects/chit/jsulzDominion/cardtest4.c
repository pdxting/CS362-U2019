/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: cardtest4.c
 * Description: Unit test for dominion game.
 * Test function: getWinners
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "getWinners"

// assert helper function
void assertCheck(int A, int B, int testNum);

int main() {
	
	int seed = rand() % 1000 + 1;
	int numPlayers = 4;
	int players[MAX_PLAYERS];
	int winnerNum;
	struct gameState beforeState, afterState;
	int k[10] = { baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };
	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----- Test 1 -----
	printf("TEST 1: Check if correct winner is found\n");
	
	memcpy(&afterState, &beforeState, sizeof(struct gameState));

	// Let last player gets all province cards to get heighest scores
	afterState.discardCount[numPlayers-1] = 12;
	for (int i = 0; i < 12; i++)
	{
		afterState.discard[numPlayers-1][i] = province;
	}

	// Print scores for all players
	for (int i = 0; i < numPlayers; i++)
	{
		printf("Score for player %d: %d\n", i, scoreFor(i, &afterState));
	}

	getWinners(players, &afterState);

	for (winnerNum = 0; winnerNum < numPlayers; winnerNum++) {
		if (players[winnerNum] == 1)
			printf("Player %d has the highest points\n", winnerNum);
	}

	assertCheck(numPlayers, winnerNum, 1);

	return 0;
}

void assertCheck(int A, int B, int testNum)
{
	if (A == B)
		printf("Test %d passed\n", testNum);
	else
		printf("Test %d failed\n", testNum);
}


