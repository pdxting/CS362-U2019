/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: unittest4.c
 * Description: Unit test for dominion game.
 * Test function: tributeAction
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Tribute"

// assert helper function
void assertCheck(int A, int B, int testNum);

int main() {

	int seed = rand() % 1000 + 1;
    int numPlayers = 2;
    int thisPlayer = 0;
	int nextPlayer = 1;
	int tributeRevealedCards[2] = {-1, -1};
	struct gameState beforeState, afterState;
	int k[10] = {baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village};

	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTCARD);

	// ----- Test 1 -----
	printf("TEST 1: Check if next player deck count decreased\n");
	
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	
	int beforeDeckSize = 1;
	afterState.deckCount[nextPlayer] = beforeDeckSize;
	afterState.discardCount[nextPlayer] = 0;
	playTribute(&afterState, thisPlayer, nextPlayer, tributeRevealedCards);
	
	printf("Player %d deck count before: %d\n", nextPlayer, beforeDeckSize);
	printf("Player %d deck count after: %d\n", nextPlayer, afterState.deckCount[nextPlayer]);
	printf("Expecting one card decrease\n");
	assertCheck(afterState.deckCount[nextPlayer], beforeDeckSize - 1, 1);

	// ----- Test 2 -----
	printf("TEST 2: check if next player discard count decreased\n");
	
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	
	int beforeDiscarding = 1;
	afterState.deckCount[nextPlayer] = 0;
	afterState.discardCount[nextPlayer] = beforeDiscarding;
	playTribute(&afterState, thisPlayer, nextPlayer, tributeRevealedCards);
	
	printf("Player %d discard count before: %d\n", nextPlayer, beforeDiscarding);
	printf("Player %d discard count after: %d\n", nextPlayer, afterState.discardCount[nextPlayer]);
	printf("Expecting one card decrease\n");
	assertCheck(afterState.discardCount[nextPlayer], beforeDiscarding - 1, 2);

	// ----- Test 3 -----
	printf("TEST 3: check if no card to reveal\n");
	
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	
	afterState.deckCount[nextPlayer] = 0;
	afterState.discardCount[nextPlayer] = 0;
	playTribute(&afterState, thisPlayer, nextPlayer, tributeRevealedCards);
	
	printf("Player %d deck count: %d\n", nextPlayer, afterState.deckCount[nextPlayer]);
	printf("Player %d discard count: %d\n", nextPlayer, afterState.discardCount[nextPlayer]);
	printf("Expecting no card to reveal\n");
	assertCheck(afterState.deckCount[nextPlayer], afterState.discardCount[nextPlayer], 3);

	// ----- Test 4 -----
	printf("TEST 4: there are two cards to reveal\n");
	printf("Check if both cards are discarded\n");
	
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	
	afterState.deckCount[nextPlayer] = 0;
	afterState.discardCount[nextPlayer] = 2;
	
	playTribute(&afterState, thisPlayer, nextPlayer, tributeRevealedCards);
	
	printf("Player %d discard count before: %d\n", nextPlayer, beforeState.discardCount[nextPlayer]);
	printf("Player %d discard count after: %d\n", nextPlayer, afterState.discardCount[nextPlayer]);
	printf("Expecting two less cards\n");
	assertCheck(afterState.discardCount[nextPlayer], beforeState.discardCount[nextPlayer] - 2, 4);

	return 0;
}

void assertCheck(int A, int B, int testNum)
{
	if (A == B)
		printf("Test %d passed\n\n", testNum);
	else
		printf("Test %d failed\n\n", testNum);
}


