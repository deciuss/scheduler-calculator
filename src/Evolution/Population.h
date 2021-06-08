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
    float biggestSoftViolation;
};

struct Population* Population(int size);
struct Individual* Population_getNthBestIndividual(struct Population* population, int n);
void Population_replaceNthWorstIndividual(struct Population* population, int n, struct Individual* newIndividual);
void Population_calculateRanking(struct Population* population);
struct Population* Population_create(int populationCardinality, struct Data* data);
void Population_destruct(struct Population* population);
void Population_reassign(struct Population* population, struct Population* newPopulation);

#endif /* EVOLUTION_POPULATION_H_ */
