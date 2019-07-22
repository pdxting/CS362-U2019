/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: cardtest2.c
 * Description: Unit test for dominion game.
 * Test function: shuffle
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "shuffle"

// assert helper function
void assertCheck(int A, int B, int testNum);

int main() {
	
	int seed = rand() % 1000 + 1;
	int numPlayers = 3;
	int thisPlayer = 0;
	int returnValue = 0;
	struct gameState beforeState, afterState;
	int k[10] = { baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };
	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----- Test 1 -----
	printf("TEST 1: Check if shuffle is needed\n");
	
	afterState.deckCount[thisPlayer] = 0;

	returnValue = shuffle(thisPlayer, &afterState);
	printf("Set deckCount zero\n");
	printf("Expecting return value of -1\n");
	assertCheck(returnValue, -1, 1);
	
	// ----- Test 2 -----
	printf("TEST 2: Check if deck is shuffled\n");
	initializeGame(numPlayers, k, seed, &beforeState);
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	shuffle(thisPlayer, &afterState);
	int shuffledCards = afterState.deckCount[thisPlayer];
	for (int i = 0; i < afterState.deckCount[thisPlayer]; i++)
	{
		if (beforeState.deck[thisPlayer][i] == afterState.deck[thisPlayer][i]) {
			shuffledCards--;
		}
	}
	if (shuffledCards == 0)
	{
		printf("Cards not shuffled. All cards are still in order.\n");
		assertCheck(shuffledCards, -1, 2);
	}
	else
	{
		printf("Card shuffled. Cards are now in different order.\n");
		assertCheck(1, 1, 2);
	}

	return 0;
}

void assertCheck(int A, int B, int testNum)
{
	if (A == B)
		printf("Test %d passed\n", testNum);
	else
		printf("Test %d failed\n", testNum);
}


