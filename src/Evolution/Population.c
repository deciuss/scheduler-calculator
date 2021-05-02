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
    population->individuals = malloc(sizeof(struct Individual*) * size);
    return population;
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
