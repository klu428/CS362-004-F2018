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
int checkAdventurer(int p, struct gameState * post) {
	int rc = 0;

	int i;
	int numTreasures = 0;
	int bonus = 0;

	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));

	//Find if the number of treasures in the discard/deck pile is > 2 in the pre-game state
	for (i = 0; i < pre.deckCount[p]; i++) {
		if (numTreasures >= 2) {
			break;
		}

		if (pre.deck[p][i] == gold || pre.deck[p][i] == silver || pre.deck[p][i] == copper) {
			numTreasures++;
		}
	}

	for (i = 0; i < pre.discardCount[p]; i++) {
		if (numTreasures >= 2) {
			break;
		}

		if (pre.discard[p][i] == gold || pre.discard[p][i] == silver || pre.discard[p][i] == copper) {
			numTreasures++;
		}
	}

	printf ("Adventurer PRE: p %d HC %d DeC %d DiC %d numT %d\n",
		     p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], numTreasures);

	//Play card
	int r = cardEffect(adventurer, 0, 0, 0, post, 0, &bonus);

	printf ("Adventurer POST: p %d HC %d DeC %d DiC %d\n",
             p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

	//Ensure treasure cards equal to numTreasures is added to the hand
	//Ensure hand count is correct (numTreasures added, adventurer card discarded)
	rc |= check(post->handCount[p] == pre.handCount[p] + numTreasures - 1);
	//Ensure the last numTreasure cards in hand are treasure cards
	for (i = 0; i < numTreasures; i++) {
		rc |= check(post->hand[p][post->handCount[p] - 1 - numTreasures] == gold || 
			   post->hand[p][post->handCount[p] - 1 - numTreasures] == silver ||
			   post->hand[p][post->handCount[p] - 1 - numTreasures] == copper);
	} 

	//Ensure correct discard + deck count
	rc |= check(post->deckCount[p] + post->discardCount[p] == pre.deckCount[p] + pre.discardCount[p] - numTreasures + 1);

	//Ensure correct return value
	rc |= check (r == 0);

	return rc;
}

int main() {
	int rc = 0;

	int i, n, p;

	int cards[10] = { adventurer, council_room, great_hall, gardens,
			      smithy, remodel, baron, village, mine, feast };

	//33% chance of treasure
	int k[9] = {copper, silver, gold, estate, duchy, province, adventurer, council_room, feast};

	struct gameState G;

	printf("Testing Adventurer.\n");

	srand(time(0));

	for (n = 0; n < 2000; n++) {
	  	p = rand() % MAX_PLAYERS;

	  	initializeGame(MAX_PLAYERS, cards, 1000, &G);

	  	G.whoseTurn = p;

    	G.deckCount[p] = rand() % MAX_DECK;
    	for (i = 0; i < G.deckCount[p]; i++) {
    		G.deck[p][i] = k[(int)rand() % 9];
    	}

    	G.discardCount[p] = rand() % MAX_DECK;
    	for (i = 0; i < G.discardCount[p]; i++) {
    		G.discard[p][i] = k[(int)rand() % 9];
    	}

    	G.handCount[p] = rand() % MAX_HAND;
    	for (i = 0; i < G.handCount[p]; i++) {
    		G.hand[p][i] = k[(int)rand() % 9];
    	}

    	rc |= checkAdventurer(p, &G);
	  }

	if (rc) {
		printf("TESTS FAILED\n");
	} else {
		printf("ALL TESTS PASSED!\n");
	}
}