/*********************************************************
 * Name: Ting Sheppy 
 * Course: CS 362 Software Engineering II
 * File: unittest1.c
 * Description: Unit test for dominion game. 
 * Test function: baronAction
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Baron"

// assert helper function 
void assertCheck(int A, int B, int testNum);

int main() {

    int choice1 = 0;
	int seed = rand() % 1000 + 1;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState beforeState, afterState;
	int k[10] = {baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village};

	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTCARD);

	// ----- Test 1 -----
	printf("TEST 1: No estate found, check if player gets an estate card and supply count is correct\n");

	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	choice1 = 0;
	playBaron(&afterState, thisPlayer, choice1);

	printf("Estate card supply before count: ");
	printf("%d\n", beforeState.supplyCount[estate]);
	printf("Estate card supply after count: ");
	printf("%d\n", afterState.supplyCount[estate]); 
	printf("Expecting one less card after estate card passed out to player\n");

	assertCheck(afterState.supplyCount[estate], beforeState.supplyCount[estate] - 1, 1);

	// ----- Test 2 -----
	printf("TEST 2: There's an estate card, check to see if player gets coins\n");

	beforeState.hand[thisPlayer][0] = baron;
	beforeState.hand[thisPlayer][1] = copper;
	beforeState.hand[thisPlayer][2] = remodel;
	beforeState.hand[thisPlayer][3] = estate;
	beforeState.hand[thisPlayer][4] = copper;

	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	choice1 = 1;

	playBaron(&afterState, thisPlayer, choice1);

	printf("Coin count = %d, Expected = %d\n", afterState.coins, beforeState.coins + 4);
	assertCheck(afterState.coins, beforeState.coins + 4, 2);


	return 0;
}

void assertCheck(int A, int B, int testNum)
{
	if (A == B)
		printf("Test %d passed\n\n", testNum);
	else
		printf("Test %d failed\n\n", testNum);
}


