#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

int baronAction(struct gameState * state, int currentPlayer, int choice1);

int minionAction(struct gameState * state, int currentPlayer, int choice1, int choice2, int handPos);

int ambassadorAction(struct gameState * state, int currentPlayer, int choice1, int choice2, int handPos);

int tributeAction(struct gameState * state, int currentPlayer, int nextPlayer);
int setCard(struct gameState * state, int nextPlayer, int card);
void giveCardToPlayer(struct gameState * state, int currentPlayer, int card);

int mineAction(struct gameState * state, int currentPlayer, int choice1, int choice2, int handPos);

#endif
