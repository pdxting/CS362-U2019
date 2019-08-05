/*********************************************************
 * Name: Ting Sheppy
 * Course: CS 362 Software Engineering II
 * File: cardtest1.c
 * Description: Unit test for dominion game.
 * Test function: initializeGame
 *********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "initializeGame"

// assert helper function
void assertCheck(int A, int B, int testNum);

int main() {

	int seed = rand() % 1000 + 1;
    int numPlayers = 0;
	int returnValue = 0;
	struct gameState beforeState;
	int k[10] = {baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----- Test 1 -----
	printf("TEST 1: Check if we can start the game with one player\n");
	
	returnValue = initializeGame(numPlayers, k, seed, &beforeState);
	printf("Starting the game with one player\n");
	printf("Expecting return value of -1\n");
	assertCheck(returnValue, -1, 1);
	
	// ----- Test 2 -----
	printf("TEST 2: Check all kingdom cards are different\n");

	int k2[10] = { baron, baron, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };
	returnValue = initializeGame(numPlayers, k2, seed, &beforeState);
	printf("Two of the 10 cards are the same\n");
	printf("Expecting return value of -1\n");
	assertCheck(returnValue, -1, 2);

	// ----- Test 3 -----
	printf("TEST 3: Check proper number of curse cards are passed out with 2, 3 or 4 players\n");

	numPlayers = 2;
	returnValue = initializeGame(numPlayers, k, seed, &beforeState);
	printf("Two player game: %d curse cards\n", beforeState.supplyCount[curse]);
	assertCheck(beforeState.supplyCount[curse], 10, 3);

	numPlayers = 3;
	returnValue = initializeGame(numPlayers, k, seed, &beforeState);
	printf("Three player game: %d curse cards\n", beforeState.supplyCount[curse]);
	assertCheck(beforeState.supplyCount[curse], 20, 3);

	numPlayers = 4;
	returnValue = initializeGame(numPlayers, k, seed, &beforeState);
	printf("Three player game: %d curse cards\n", beforeState.supplyCount[curse]);
	assertCheck(beforeState.supplyCount[curse], 30, 3);

	// ----- Test 4 -----
	printf("TEST 4: Check proper number of victory cards are passed out with 2 or more than 3 players\n");

	numPlayers = 2;
	returnValue = initializeGame(numPlayers, k, seed, &beforeState);
	printf("Two player game: \n");
	printf("%d estate cards. Expecting 8\n", beforeState.supplyCount[estate]);
	assertCheck(beforeState.supplyCount[estate], 8, 4);
	printf("%d duchy cards. Expecting 8\n", beforeState.supplyCount[duchy]);
	assertCheck(beforeState.supplyCount[duchy], 8, 4);
	printf("%d province cards. Expecting 8\n", beforeState.supplyCount[province]);
	assertCheck(beforeState.supplyCount[province], 8, 4);

	numPlayers = 3;
	returnValue = initializeGame(numPlayers, k, seed, &beforeState);
	printf("Three player game: \n");
	printf("%d estate cards. Expecting 12\n", beforeState.supplyCount[estate]);
	assertCheck(beforeState.supplyCount[estate], 12, 4);
	printf("%d duchy cards. Expecting 12\n", beforeState.supplyCount[duchy]);
	assertCheck(beforeState.supplyCount[duchy], 12, 4);
	printf("%d province cards. Expecting 12\n", beforeState.supplyCount[province]);
	assertCheck(beforeState.supplyCount[province], 12, 4);

	return 0;
}

void assertCheck(int A, int B, int testNum)
{
	if (A == B)
		printf("Test %d passed\n", testNum);
	else
		printf("Test %d failed\n", testNum);
}


