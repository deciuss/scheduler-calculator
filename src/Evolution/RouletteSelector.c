/*
 * RouletteSelector.c
 *
 *  Created on: 7 cze 2021
 *      Author: deciuss
 */
#include "RouletteSelector.h"

float _RouletteSelector_getRandomFloatFromRangeZeroToA(float a) {
	return (float)rand()/(float)(RAND_MAX/a);
}

struct RouletteSelector* RouletteSelector(struct Population* population) {

	struct RouletteSelector* rouletteSelector = malloc(sizeof(struct RouletteSelector));
	rouletteSelector->size = population->size;
	rouletteSelector->sections = malloc(population->size * sizeof(int));

	for (int i = 0; i < population->size; i++) {
		rouletteSelector->sections[i] = (i > 0) ? rouletteSelector->sections[i - 1] : 0;
		rouletteSelector->sections[i] += Violation_getInversed(population->individuals[i]->violation, population->biggestSoftViolation);
		rouletteSelector->limit = rouletteSelector->sections[i];
	}

	return rouletteSelector;

}

void RouletteSelector_destruct(struct RouletteSelector* rouletteSelector) {
	free(rouletteSelector->sections);
	free(rouletteSelector);
}

int RouletteSelector_drawIndividualIndex(struct RouletteSelector* rouletteSelector) {
	float rouletteRollingResult = _RouletteSelector_getRandomFloatFromRangeZeroToA(rouletteSelector->limit);
	for (int i = 0; i < rouletteSelector->size; i++) {
		if (rouletteRollingResult <= rouletteSelector->sections[i]) {
			return i;
		}
	}

	return rouletteSelector->size - 1;
}
