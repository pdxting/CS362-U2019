/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: randomtestcard2.c
 * Description: Random test for dominion game.
 * Test function: minionAction
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "minionAction"

// assert helper function
void assertCheck(int A, int B);

int main() {

	int choice1;
	int choice2;
	int seed = rand() % 1000 + 1;
	int numPlayers = 2;
	int thisPlayer = 0;
	int handPos = 0;
	struct gameState beforeState, afterState;
	int k[10] = { baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };

	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	for (int i = 0; i < 1000; i++) {
		seed = rand() % 1000 + 1;
		choice1 = rand() % 2;
		choice2 = 1 - choice1;
		initializeGame(numPlayers, k, seed, &beforeState);
		
		for (int i = 0; i < numPlayers; i++) {
			beforeState.handCount[i] = rand() % 6;
		}
		
		memcpy(&afterState, &beforeState, sizeof(struct gameState));
		playMinion(&afterState, thisPlayer, handPos, choice1, choice2);
		
		if (choice1) {
			printf("Coin should increase by 2. ");
			assertCheck(beforeState.coins + 2, afterState.coins);
		}
		else if (choice2) {
			printf("Current player should have 4 cards in hand. ");
			assertCheck(afterState.handCount[thisPlayer], 4);
			for (int i = 0; i < numPlayers; i++) {
				if (i != thisPlayer) {
					if (beforeState.handCount[i] > 4) {
						printf("Other players 5 or more cards now have 4. ");
						assertCheck(afterState.handCount[i], 4);
					}
				}
			}
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


