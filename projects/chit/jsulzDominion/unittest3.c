/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: unittest3.c
 * Description: Unit test for dominion game.
 * Test function: ambassadorAction
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Ambassador"

// assert helper function
void assertCheck(int A, int B, int testNum);

int main() {

    int choice1 = 0;
	int choice2 = 0;
	int handPos = 0;
	int returnValue = 0;
	int seed = rand() % 1000 + 1;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState beforeState, afterState;
	int k[10] = {baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village};

	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTCARD);

	// ----- Test 1 -----
	printf("TEST 1: Player choose more than allowed supply number. Expected to return -1\n");
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	choice2 = 2;
	returnValue = playAmbassador(&afterState, thisPlayer, choice1, choice2, handPos);
	printf("Choice2 is greater than 2\n");
	assertCheck(returnValue, -1, 1);

	// ----- Test 2 -----
	printf("TEST 2: Player choose less than allowed supply number. Expected to return -1\n");
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	choice2 = -1;
	returnValue = playAmbassador(&afterState, thisPlayer, choice1, choice2, handPos);
	printf("Choice2 is less than 0\n");
	assertCheck(returnValue, -1, 2);

	// ----- Test 3 -----
	printf("TEST 3: Player choice1 and handPos are equal. Expected to return -1\n");
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 1;
	handPos = 1;
	returnValue = playAmbassador(&afterState, thisPlayer, choice1, choice2, handPos);
	printf("Choice1 and handPos should not be equal\n");
	assertCheck(returnValue, -1, 3);

	// ----- Test 4 -----
	printf("TEST 4: Check if each other player gained a supply card\n");
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 2;
	playAmbassador(&afterState, thisPlayer, choice1, choice2, handPos);
	for (int i = 0; i < afterState.numPlayers; i++)
	{
		if (i != thisPlayer)
		{
			printf("Player %d: ", i);
			printf("Before gaining a card count: %d\n", beforeState.handCount[i]);
			printf("After gaining a card count: %d\n", afterState.handCount[i]);
			printf("Player %d should now have one more card\n", i);
			assertCheck(afterState.handCount[i], beforeState.handCount[i] + 1, 4);
		}
	}

	// ----- Test 5 -----
	printf("TEST 5: Check if trashed cards returned to supply\n");
	memcpy(&afterState, &beforeState, sizeof(struct gameState));
	playAmbassador(&afterState, thisPlayer, choice1, choice2, handPos);
	for (int cardCount = 0; cardCount < choice2; cardCount++)
	{
		for (int i = 0; i < afterState.handCount[thisPlayer]; i++)
		{
			if (afterState.hand[thisPlayer][i] == afterState.hand[thisPlayer][choice1])
			{
				printf("Returning card for player %d\n", i);
				assertCheck(afterState.hand[thisPlayer][i], afterState.hand[thisPlayer][choice1], 5);
			}
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


