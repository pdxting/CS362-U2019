/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: randomtestcard1.c
 * Description: Random test for dominion game.
 * Test function: baronAction
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "baronAction"

// assert helper function
void assertCheck(int A, int B);

int main() {

	int choice1 = 0;
	int seed = rand() % 1000 + 1;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState beforeState, afterState;
	int k[10] = { baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };

	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	for (int i = 0; i < 2000; i++) {
		seed = rand() % 1000 + 1;
		initializeGame(numPlayers, k, seed, &beforeState);
		choice1 = rand() % 2;

		beforeState.supplyCount[estate] = rand() % 3;
		
		for (int i = 0; i < 5; i++) {
			beforeState.hand[thisPlayer][i] = rand() % 27 + 1;
		}
		
		memcpy(&afterState, &beforeState, sizeof(struct gameState));

		baronAction(&afterState, thisPlayer, choice1);

		if (choice1 > 0) {
			int currentCard = 0;
			int estateNotFound = 1;
			while (estateNotFound) {
				if (afterState.hand[thisPlayer][currentCard] == estate) {
					printf("Coin count should be 4 more. ");
					assertCheck(beforeState.coins + 4, afterState.coins);
					printf("Discard count should increase by 1. ");
					assertCheck(beforeState.discardCount[thisPlayer] + 1, afterState.discardCount[thisPlayer]);
					estateNotFound = 0;
				}
				else if (currentCard > afterState.handCount[thisPlayer]) {
					printf("choice1 is 1: Supply count should decrease by 1. ");
					assertCheck(beforeState.supplyCount[estate] - 1, afterState.supplyCount[estate]);
					estateNotFound = 0;
				}
				else {
					currentCard++;
				}
			}
		}
		else {
			printf("choice 1 is 0: Supply count should decrease by 1. ");
			assertCheck(beforeState.supplyCount[estate] - 1, afterState.supplyCount[estate]);
		}
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


