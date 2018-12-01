#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
	int seed = 1000;
	int numPlayer = 2;
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, treasure_map};
	struct gameState G, testG;
	int rc = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

	printf("TESTING smithy\n");
	initializeGame(numPlayer, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (testG.handCount[0] != G.handCount[0] + 2 ) {
		printf("TEST FAILED: Incorrect number of cards in hand\n");
		rc = 1;
	}

	if (testG.deckCount[0] != G.deckCount[0] - 3 ) {
		printf("TEST FAILED: Incorrect number of cards in deck\n");
		rc = 1;
	}

	if (testG.handCount[1] != G.handCount[1]) {
		printf("TEST FAILED: Other players do not have the same number of cards in hand\n");
		rc = 1;
	}

	if (rc)
	{
		printf("TESTS FAILED\n");
	} else {
		printf("ALL TESTS PASSED\n");
	}

	return 0;
}
