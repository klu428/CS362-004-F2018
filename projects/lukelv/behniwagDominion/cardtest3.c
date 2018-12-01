#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
	int seed = 1000;
	int numPlayer = 4;
	int r;
	int k[10] = {adventurer, council_room, great_hall, gardens, mine, remodel, smithy, village, baron, treasure_map};
	struct gameState G, testG;
	int rc = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int i;

	printf("TESTING great_hall\n");
	initializeGame(numPlayer, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (testG.handCount[0] != G.handCount[0] ) {
		printf("TEST FAILED: Incorrect number of cards in current player's hand\n");
		rc = 1;
	}

	if (testG.deckCount[0] != G.deckCount[0] - 1 ) {
		printf("TEST FAILED: Incorrect number of cards in current player's deck\n");
		rc = 1;
	}

	if (testG.numBuys != G.numBuys) {
		printf("TEST FAILED: Incorrect number of buys for current player\n");
		rc = 1;
	}

	if (testG.numActions != G.numActions + 1) {
		printf("TEST FAILED: Incorrect number of actions for current player\n");
		rc = 1;
	}

	for (i = 1; i < numPlayer; i++) {

		if (testG.handCount[1] != G.handCount[1]) {
			printf("TEST FAILED: Incorrect number of cards in other players' hands\n");
			rc = 1;
		}

		if (testG.deckCount[1] != G.deckCount[1]) {
			printf("TEST FAILED: Incorrect number of cards in other players' deck\n");
			rc = 1;
		}

		if (testG.discardCount[1] != G.discardCount[1]) {
			printf("TEST FAILED: Incorrect number of cards in other players' discard pile\n");
			rc = 1;
		}
	}

	if (rc)
	{
		printf("TESTS FAILED\n");
	}

	printf("ALL TESTS PASSED\n");
	return 0;
}
