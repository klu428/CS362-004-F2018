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
	int discardedCard;
	int r;
	int p, handCount, handPos, trashFlag;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHandCount = 5;
	int hand[MAX_HAND];
	int rc = 0;
	int i;
	for (i = 0; i < MAX_HAND; i++) {
		hand[i] = k[rand() % 10];
	}

	printf("TESTING discardCard():\n");
	for (p = 0; p < numPlayer; p++)
	{
		for (handCount = 1; handCount <= maxHandCount; handCount++)
		{
			for (handPos = 0; handPos < handCount; handPos++)
			{
				for (trashFlag = 0; trashFlag < 2; trashFlag++)
				{
					discardedCard = hand[handPos];
#if (NOISY_TEST == 1)
					printf("Player: %d | Hand Count: %d | Hand Pos: %d | Discarded Card: %d | Trash Flag: %d\n", p, handCount, handPos, discardedCard, trashFlag);
#endif
					memset(&G, 23, sizeof(struct gameState));
					r = initializeGame(numPlayer, k, seed, &G);
					G.handCount[p] = handCount;
					memcpy(G.hand[p], hand, sizeof(int) * handCount);
					discardCard(handPos, p, &G, trashFlag);
					if (trashFlag < 1) {
						if (G.playedCards[G.playedCardCount - 1] != discardedCard) {
							printf("TEST FAILED: Card not played\n");
							rc |= 1;
						}
					}
					if (G.handCount[p] != handCount - 1) {
						printf("TEST FAILED: Wrong hand count\n");
						rc |= 1;
					}
					else {
						for (i = 0; i < handCount - 1; i++) {
							if (i == handPos) {
								if (G.hand[p][i] != hand[handCount -1]) {
									printf("TEST FAILED: Card not replaced correctly\n");
									rc |= 1;
									break;
								}
							}
							else if (G.hand[p][i] != hand[i]) {
								printf("TEST FAILED: Wrong cards in hand\ni = %d\nG.hand[p][i] = %d\nHand[i] = %d", i, G.hand[p][i], hand[i]);
								rc |= 1;
								break;
							}
						}
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

							
