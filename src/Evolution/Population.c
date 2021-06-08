/*
 * Population.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */
#include "Population.h"

struct Population* Population(int size) {
    struct Population* population = malloc(sizeof(struct Population));
    population->size = size;
    population->ranking = malloc(sizeof(int) * size);
    population->ranking[0] = 0;
    population->individuals = malloc(sizeof(struct Individual*) * size);
    population->biggestSoftViolation = 0;
    return population;
}

void Population_destruct(struct Population* population) {
	for (int i = 0; i < population->size; i++) {
		Individual_destruct(population->individuals[i]);
	}

	free(population->individuals);
    free(population->ranking);
    free(population);
}

void Population_reassign(struct Population* population, struct Population* newPopulation) {
	for (int i = 0; i < population->size; i++) {
		Individual_destruct(population->individuals[i]);
	}

	free(population->ranking);
	free(population->individuals);

	population->size = newPopulation->size;
	population->ranking = newPopulation->ranking;
	population->individuals = newPopulation->individuals;
	free(newPopulation);
}

void Population_calculateRanking(struct Population* population) {
	free(population->ranking);
	population->ranking = malloc(sizeof(int) * population->size);
	population->ranking[0] = 0;
	for (int i = 1; i < population->size; i++) {
		for (int j = i; j >= 0 ; j--) {
			if (
				j > 0
				&& Individual_compare(
					population->individuals[i],
					population->individuals[population->ranking[j - 1]]
				) > 0
			) {
				population->ranking[j] = population->ranking[j - 1];
			} else {
				population->ranking[j] = i;
				break;
			}
		}
	}
}

struct Individual* Population_getNthBestIndividual(struct Population* population, int n) {
	return population->individuals[population->ranking[n]];
}

void Population_replaceNthWorstIndividual(struct Population* population, int n, struct Individual* newIndividual) {
	int nthWorstIndividualIndex = population->ranking[population->size -1 - n];
	Individual_destruct(population->individuals[nthWorstIndividualIndex]);
	population->individuals[nthWorstIndividualIndex] = newIndividual;
}

struct Population* Population_create(int populationCardinality, struct Data* data) {
	struct Population* population = Population(populationCardinality);
    for (int i = 0; i < populationCardinality; i++) {
       population->individuals[i] = Individual_create(data);
    }
    return population;
}
