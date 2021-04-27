/*
 * Individual.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */
#include "Individual.h"
#include "Gene.h"

struct Individual* Individual(int numberOfGenes) {
    struct Individual* individual = malloc(sizeof(struct Individual));
    individual->numberOfGenes = numberOfGenes;
    individual->genes = malloc(sizeof(struct Gene*) * numberOfGenes);
    return individual;
}

void Individual_updateGene(struct Individual* individual, unsigned int position, struct Gene * gene) {
    Gene_destruct(individual->genes[position]);
    individual->genes[position] = gene;
}

void Individual_destruct(struct Individual * individual) {
    for (int i = 0; i < individual->numberOfGenes; i++) {
        Gene_destruct(individual->genes[i]);
    }
    free(individual);
}
