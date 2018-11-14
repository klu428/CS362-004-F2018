#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <time.h>

int check(int condition) {
	if (!condition) {
		printf("TEST FAILED!\n");
		return 1;
	}
	return 0;
}

//Reference: testBuyCard in example code
int checkCouncilRoom(int p, struct gameState * post) {
	int rc = 0;

	int i, cardsDrawn;
	int bonus = 0;

	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));

	printf ("Adventurer PRE: p %d HC %d DeC %d DiC %d numB %d\n",
		     p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numBuys);

	int r = cardEffect(council_room, 0, 0, 0, post, 0, &bonus);

	printf ("Adventurer POST: p %d HC %d DeC %d DiC %d numB %d\n",
             p, post->handCount[p], post->deckCount[p], post->discardCount[p], post->numBuys);

	//Get cards drawn for current player
	if (pre.deckCount[p] + pre.discardCount[p] < 4) {
		cardsDrawn = pre.deckCount[p] + pre.discardCount[p];
	} else {
		cardsDrawn = 4;
	}

	//Ensure correct return code
	rc |= check(r == 0);

	//Ensure correct amount of cards drawn
	rc |= check(post->handCount[p] == pre.handCount[p] + cardsDrawn - 1 );

	//Ensure correct discard + deck count
	rc |= check(post->deckCount[p] + post->discardCount[p] == pre.deckCount[p] + pre.discardCount[p] - cardsDrawn);

	//Ensure correct amount of buys
	rc |= check(post->numBuys == pre.numBuys + 1);

	//Ensure each other player draws a card
	for (i = 0; i < pre.numPlayers; i++) {
		if (i != p) {
			//Get cards drawn for current player
			if (pre.deckCount[p] + pre.discardCount[p] == 0) {
				cardsDrawn = 0;
			} else {
				cardsDrawn = 1;
			}

			//Ensure correct amount of cards drawn
			rc |= check(post->handCount[i] == pre.handCount[i] + cardsDrawn );

			//Ensure correct discard + deck count
			rc |= check(post->deckCount[i] + post->discardCount[i] == pre.deckCount[i] + pre.discardCount[i] - cardsDrawn);
		}
	}

	return rc;
}

int main() {
	int rc;

	int i, n, p;

	int k[10] = { adventurer, council_room, great_hall, gardens,
			      smithy, remodel, baron, village, mine, feast };

	struct gameState G;

	printf("Testing Council Room.\n");

	srand(time(0));

	//Reference: testBuyCard in example code
	for (n = 0; n < 2000; n++) {
	  	//Randomize number of players. Must have at least 2 players to MAX_PLAYERS
	  	G.numPlayers = rand() % 3 + 2;
	  	//Randomize current player
	  	p = rand() % G.numPlayers;

	  	initializeGame(G.numPlayers, k, 1000, &G);

	  	G.whoseTurn = p;

	  	//Randomize each player's deck/discard/hand count
	  	for (i = 0; i < G.numPlayers; i++) {
	  		G.deckCount[i] = rand() % MAX_DECK;
    		G.discardCount[i] = rand() % MAX_DECK;
    		G.handCount[i] = rand() % MAX_HAND;
	  	}

    	rc |= checkCouncilRoom(p, &G);
	}

	if (rc) {
		printf("TESTS FAILED\n");
	} else {
		printf("ALL TESTS PASSED!\n");
	}
}