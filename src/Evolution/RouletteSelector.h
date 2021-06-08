/*
 * RouletteSelector.h
 *
 *  Created on: 7 cze 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_ROULETTESELECTOR_H_
#define EVOLUTION_ROULETTESELECTOR_H_
#include <stdlib.h>
#include "Population.h"
#include "Violation.h"

struct RouletteSelector {
	float* sections;
	float limit;
	int size;
};

struct RouletteSelector* RouletteSelector(struct Population* population);
int RouletteSelector_drawIndividualIndex();
void RouletteSelector_destruct(struct RouletteSelector* rouletteSelector);

#endif /* EVOLUTION_ROULETTESELECTOR_H_ */
