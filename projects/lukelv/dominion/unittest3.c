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
	int p, deckCount, handCount, discardCount;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxDeckCount = 20;
	int maxHandCount = 5;
	int maxDiscardCount = 20;
	int cards[MAX_HAND];
	int init[MAX_HAND];
	int rc = 0;
	int i;
	for (i = 0; i < MAX_DECK; i++) {
		init[i] = k[rand() % 10];
		cards[i] = copper;
	}

	printf("TESTING fullDeckCount():\n");
	for (p = 0; p < numPlayer; p++)
	{
		for (deckCount = 0; deckCount <= maxDeckCount; deckCount++)
		{
			for (handCount = 0; handCount <= maxHandCount; handCount++)
			{
				for (discardCount = 0; discardCount <= maxDiscardCount; discardCount++)
				{
#if (NOISY_TEST == 1)
					printf("Player: %d | Deck Count: %d | Hand Count: %d | Discard Count: %d\n", p, deckCount, handCount, discardCount);
#endif
					memset(&G, 23, sizeof(struct gameState));
					r = initializeGame(numPlayer, k, seed, &G);
					G.deckCount[p] = maxDeckCount;
					memcpy(G.deck[p], init, sizeof(int) * maxDeckCount);
					memcpy(G.deck[p], cards, sizeof(int) * deckCount);
					G.handCount[p] = maxHandCount;
					memcpy(G.hand[p], init, sizeof(int) * maxHandCount);
					memcpy(G.hand[p], cards, sizeof(int) * handCount);
					G.discardCount[p] = maxDiscardCount;
					memcpy(G.discard[p], init, sizeof(int) * maxDiscardCount);
					memcpy(G.discard[p], cards, sizeof(int) * discardCount);

					if (fullDeckCount(p, copper, &G ) != deckCount + handCount + discardCount ) {
						printf("TEST FAILED: Copper in full deck not counted correctly\n");
						rc |= 1;
					}
				}
			}
		}
	}
	if (rc)
	{
		printf("TESTS FAILED\n");
	}

	printf("ALL TESTS PASSED\n");
	return 0;
}
