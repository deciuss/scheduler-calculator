/*
 * Population.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_POPULATION_H_
#define EVOLUTION_POPULATION_H_
#include <stdlib.h>
#include "Individual.h"

struct Population {
    struct Individual** individuals;
    int size;
    int* ranking;
};

struct Population* Population(int size);
struct Individual* Population_getNthBestIndividual(struct Population* population, int n);
void Population_replaceNthWorstIndividual(struct Population* population, int n, struct Individual* newIndividual);
void Population_calculateRanking(struct Population* population);

#endif /* EVOLUTION_POPULATION_H_ */
