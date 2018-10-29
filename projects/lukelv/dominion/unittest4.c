#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
		
#define NOISY_TEST 1

int main() {
	int seed = 1000;
	int numPlayer = 2;
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, treasure_map};
	struct gameState G;
	int rc = 0;

	printf("TESTING isGameOver():\n");
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);

	if (isGameOver(&G) == 1) {
		printf("TEST FAILED: Game should not have ended because no conditions were met");
		rc = 1;
	}

	G.supplyCount[province] = 0;
	if (isGameOver(&G) == 0) {
		printf("TEST FAILED: Game should have ended after province supply pile was exhausted");
		rc = 1;
	}

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);

	G.supplyCount[adventurer] = 0;

	if (isGameOver(&G) == 1) {
		printf("TEST FAILED: Game should not have ended after one supply pile was exhausted");
		rc = 1;
	}

	G.supplyCount[copper] = 0;

	if (isGameOver(&G) == 1) {
		printf("TEST FAILED: Game should not have ended after two supply piles were exhausted");
		rc = 1;
	}

	G.supplyCount[treasure_map] = 0;

	if (isGameOver(&G) == 0) {
		printf("TEST FAILED: Game should have ended after three supply piles were exhausted\n");
		rc = 1;
	}

	G.supplyCount[estate] = 0;

	if (isGameOver(&G) == 0) {
		printf("TEST FAILED: Game should have ended after four supply piles were exhausted\n");
		rc = 1;
	}
	
	if (rc)
	{
		printf("TESTS FAILED\n");
	}

	printf("ALL TESTS PASSED\n");
	return 0;
}
