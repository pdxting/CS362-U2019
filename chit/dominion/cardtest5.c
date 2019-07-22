/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: cardtest3.c
 * Description: Unit test for dominion game.
 * Test function: drawCard
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "drawCard"

// assert helper function
void assertCheck(int A, int B, int testNum);

int main() {
	
	int seed = rand() % 1000 + 1;
	int numPlayers = 4;
	int thisPlayer = 0;
	struct gameState beforeState, afterState;
	int k[10] = { baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };
	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----- Test 1 -----
	printf("TEST 1: When there are still cards in deck, \n");
	printf("check if player card counts are still accuate after draw cards\n");
	beforeState.deckCount[thisPlayer] = 12;
	beforeState.handCount[thisPlayer] = 5;
	beforeState.discardCount[thisPlayer] = 0;

	memcpy(&afterState, &beforeState, sizeof(struct gameState));

	drawCard(thisPlayer, &afterState);

	printf("deckCount before drawCard: %d. DeckCount after drawCard: %d.\n", beforeState.deckCount[thisPlayer], afterState.deckCount[thisPlayer]);
	printf("deckCount expecting one less\n");
	assertCheck(beforeState.deckCount[thisPlayer] - 1, afterState.deckCount[thisPlayer], 1);
	printf("handCount before drawCard: %d. handCount after drawCard: %d.\n", beforeState.handCount[thisPlayer], afterState.handCount[thisPlayer]);
	printf("handCount expecting one more\n");
	assertCheck(beforeState.handCount[thisPlayer], afterState.handCount[thisPlayer] - 1, 1);
	printf("discardCount before drawCard: %d. discardCount after drawCard: %d.\n", beforeState.discardCount[thisPlayer], afterState.discardCount[thisPlayer]);
	printf("discardCount remain the same\n");
	assertCheck(beforeState.discardCount[thisPlayer], afterState.discardCount[thisPlayer], 1);

	// ----- Test 2 -----
	printf("TEST 2: When there no cards in deck, \n");
	printf("check if player card counts are still accuate after draw cards\n");
	beforeState.deckCount[thisPlayer] = 0;
	beforeState.handCount[thisPlayer] = 5;
	beforeState.discardCount[thisPlayer] = 12;

	memcpy(&afterState, &beforeState, sizeof(struct gameState));

	drawCard(thisPlayer, &afterState);

	printf("deckCount before drawCard: %d. DeckCount after drawCard: %d.\n", beforeState.deckCount[thisPlayer], afterState.deckCount[thisPlayer]);
	printf("deckCount expecting to be one less than the same as discard count before draw card\n");
	assertCheck(beforeState.discardCount[thisPlayer] - 1, afterState.deckCount[thisPlayer], 2);
	printf("handCount before drawCard: %d. handCount after drawCard: %d.\n", beforeState.handCount[thisPlayer], afterState.handCount[thisPlayer]);
	printf("handCount expecting one more\n");
	assertCheck(beforeState.handCount[thisPlayer], afterState.handCount[thisPlayer] - 1, 2);
	printf("discardCount before drawCard: %d. discardCount after drawCard: %d.\n", beforeState.discardCount[thisPlayer], afterState.discardCount[thisPlayer]);
	printf("discardCount should be zero\n");
	assertCheck(0, afterState.discardCount[thisPlayer], 2);
	return 0;
}

void assertCheck(int A, int B, int testNum)
{
	if (A == B)
		printf("Test %d passed\n", testNum);
	else
		printf("Test %d failed\n", testNum);
}


