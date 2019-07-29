/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: randomtestcard3.c
 * Description: Random test for dominion game.
 * Test function: tributeAction
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "tributeAction"

// assert helper function
void assertCheck(int A, int B);

int main() {

	int seed = rand() % 1000 + 1;
	int numPlayers = 2;
	int thisPlayer = 0;
	int nextPlayer = 0;
	int card1 = -1;
	int card2 = -1;
	struct gameState beforeState, afterState;
	int k[10] = { baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };

	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);


	for (int i = 0; i < 1000; i++) {
		seed = rand() % 1000 + 1;
		initializeGame(numPlayers, k, seed, &beforeState);
		
		// Randomize current player and next player
		thisPlayer = rand() % numPlayers;
		nextPlayer = thisPlayer + 1;
		if (nextPlayer == numPlayers) {
			nextPlayer = 0;
		}

		// Randomize next player's deck count and discard count
		for (int i = 0; i < numPlayers; i++) {
			beforeState.deckCount[i] = rand() % 10;
			beforeState.discardCount[i] = rand() % 10;
		}

		memcpy(&afterState, &beforeState, sizeof(struct gameState));

		// Card 1 and 2 stored for comparison later
		card1 = beforeState.deck[nextPlayer][beforeState.deckCount[nextPlayer] - 1];
		card2 = beforeState.deck[nextPlayer][beforeState.deckCount[nextPlayer] - 2];

		tributeAction(&afterState, thisPlayer, nextPlayer);
		
		if (beforeState.discardCount[nextPlayer] + beforeState.deckCount[nextPlayer] <= 1) {
			if (beforeState.deckCount[nextPlayer] > 0) {
				printf("Next player deck count should decrease by 1. ");
				assertCheck(beforeState.deckCount[nextPlayer] - 1, afterState.deckCount[nextPlayer]);
			}
			else if (beforeState.discardCount[nextPlayer] > 0) {
				printf("Next player discard count should decrease by 1. ");
				assertCheck(beforeState.discardCount[nextPlayer] - 1, afterState.discardCount[nextPlayer]);
			}
		}
		else {
			if (beforeState.deckCount[nextPlayer] == 0) {
				printf("Next player deck count should increase by 1. ");
				assertCheck(beforeState.deckCount[nextPlayer] + 1, afterState.deckCount[nextPlayer]);
			}
			printf("card1 before and after function call. ");
			assertCheck(afterState.deck[nextPlayer][afterState.deckCount[nextPlayer] - 1], card1);
			printf("card2 before and after function call. ");
			assertCheck(afterState.deck[nextPlayer][afterState.deckCount[nextPlayer] - 2], card2);
		}
		printf("Current player should gain 2 cards. ");
		assertCheck(beforeState.handCount[thisPlayer] + 2, afterState.handCount[thisPlayer]);
	}

	return 0;
}

void assertCheck(int A, int B)
{
	if (A == B)
		printf("Test passed\n");
	else
		printf("Test failed\n");
}


