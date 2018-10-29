#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
		
#define NOISY_TEST 0

int main() {
	int seed = 1000;
	int numPlayer = 2;
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int rc = 0;

	printf("TESTING supplyCount():\n");
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);

	if (supplyCount(curse, &G) != 10) {
		printf("TEST FAILED: Incorrect supply count of curse");
		rc = 1;
	}

	if (supplyCount(estate, &G) != 8) {
		printf("TEST FAILED: Incorrect supply count of estates");
		rc = 1;
	}

	if (supplyCount(gold, &G) != 30) {
		printf("TEST FAILED: Incorrect supply count of gold");
		rc = 1;
	}

	if (supplyCount(great_hall, &G) != 8) {
		printf("TEST FAILED: Incorrect supply count of great halls");
		rc = 1;
	}

	if (supplyCount(adventurer, &G) != 10) {
		printf("TEST FAILED: Incorrect supply count of adventurers");
		rc = 1;
	}

	if (supplyCount(tribute, &G) != -1) {
		printf("TEST FAILED: Tribute not in the game but does not return -1");
		rc = 1;
	}

	G.supplyCount[gold] = 0;
	if (supplyCount(gold, &G) != 0) {
		printf("TEST FAILED: Incorrect supply count of gold after changing the value");
		rc = 1;
	}

	if (rc)
	{
		printf("TESTS FAILED\n");
	}

	printf("ALL TESTS PASSED\n");
	return 0;
}
