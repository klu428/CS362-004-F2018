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
int checkSmithy(int p, struct gameState * post) {
	int rc = 0;

	int cardsDrawn;
    int bonus = 0;

	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));

	printf ("Smithy PRE: p %d HC %d DeC %d DiC %d\n",
		     p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);

	int r = cardEffect(smithy, 0, 0, 0, post, 0, &bonus);

	printf ("Smithy POST: p %d HC %d DeC %d DiC %d\n",
		     p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

	if (pre.deckCount[p] + pre.discardCount[p] < 3) {
		cardsDrawn = pre.deckCount[p] + pre.discardCount[p];
	} else {
		cardsDrawn = 3;
	}

	//Ensure correct return code
	rc |= check(r == 0);

	//Ensure correct amount of cards drawn
	rc |= check(post->handCount[p] == pre.handCount[p] + cardsDrawn - 1 );

	//Ensure correct discard + deck count
	rc |= check(post->deckCount[p] + post->discardCount[p] == pre.deckCount[p] + pre.discardCount[p] - cardsDrawn);

	return rc;
}

int main() {
	int rc;

	int i, n, p;

	int k[10] = { adventurer, council_room, great_hall, gardens,
			      smithy, remodel, baron, village, mine, feast };

	struct gameState G;

	printf("Testing Smithy.\n");

	srand(time(0));

	//Reference: testBuyCard in example code
	for (n = 0; n < 2000; n++) {
		p = rand() % MAX_PLAYERS;

	  	initializeGame(MAX_PLAYERS, k, 1000, &G);

	  	G.whoseTurn = p;

	  	for (i = 0; i < G.numPlayers; i++) {
    		G.deckCount[i] = rand() % MAX_DECK;
    		G.discardCount[i] = rand() % MAX_DECK;
    		G.handCount[i] = rand() % MAX_HAND;
    	}
    	rc |= checkSmithy(p, &G);
	}

	if (rc) {
		printf("TESTS FAILED\n");
	} else {
		printf("ALL TESTS PASSED!\n");
	}
}
