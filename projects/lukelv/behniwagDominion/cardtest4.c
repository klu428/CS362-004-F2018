#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define DECKCOUNT 10

int main() {
	int seed = 1000;
	int numPlayer = 4;
	int r;
	int k[10] = {adventurer, council_room, great_hall, gardens, mine, remodel, smithy, village, baron, treasure_map};
	struct gameState G, testG;
	int rc = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int deckCount = 10;
	int deck[DECKCOUNT];
	int i, j;
	for (i = 0; i < DECKCOUNT; i++) {
		deck[i] = k[rand() % 10];
	}

	deck[0] = copper;
	deck[5] = silver;
	deck[DECKCOUNT - 1] = gold;

	printf("TESTING adventurer\n");

	memset(&G, 23, sizeof(struct gameState));
	initializeGame(numPlayer, k, seed, &G);
	G.deckCount[0] = DECKCOUNT;
	memcpy(G.deck[0], deck, sizeof(int) * DECKCOUNT);
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Player 1's hand: ");
	for(j = 0; j < testG.handCount[0]; j++) {
		printf("%d | ", testG.hand[0][j]);
	}
	
	printf("\n");	

	if (testG.handCount[0] != G.handCount[0] + 1) {
		printf("TEST FAILED: Incorrect number of cards in current player's hand\n");
		rc = 1;
	}

	if (testG.discardCount[0] != G.deckCount[0] + 3) {
		printf("TEST FAILED: Incorrect number of cards in current player's discard pile\n");
		rc = 1;
	}

	if (testG.hand[0][testG.handCount[0] - 1] != silver) {
		printf("TEST FAILED: Last card in hand is not silver\n");
		rc = 1;
	}

	if (testG.hand[0][testG.handCount[0] - 2] != gold) {
		printf("TEST FAILED: Second to last card in hand is not gold\n");
		rc = 1;
	}

	if (rc)
	{
		printf("TESTS FAILED\n");
	}

	printf("ALL TESTS PASSED\n");
	return 0;
}
