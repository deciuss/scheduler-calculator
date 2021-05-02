/*
 * Individual.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */
#include "Individual.h"

struct Individual* Individual(int numberOfGenes) {
    struct Individual* individual = malloc(sizeof(struct Individual));
    individual->numberOfGenes = numberOfGenes;
    individual->genes = malloc(sizeof(struct Gene*) * numberOfGenes);
    individual->hardViolationFactor = -1;
    individual->softViolationFactor = -1;
    return individual;
}

void Individual_updateGene(struct Individual* individual, int position, struct Gene * gene) {
    Gene_destruct(individual->genes[position]);
    individual->genes[position] = gene;
}

void Individual_destruct(struct Individual* individual) {
    for (int i = 0; i < individual->numberOfGenes; i++) {
        Gene_destruct(individual->genes[i]);
    }
    free(individual->genes);
    free(individual);
}

/**
 * Returns -1 if individualA violation > individualB violation <=> individualB is healthier
 * Returns  1 if individualA violation < individualB violation <=> individualA is healthier
 * Returns  0 if individualA violation == individualB violation
 */
int Individual_compare(struct Individual* individualA, struct Individual* individualB) {
	if (individualA->hardViolationFactor < 0) exit(23);
	if (individualB->hardViolationFactor < 0) exit(24);
	if (individualA->softViolationFactor < 0) exit(23);
	if (individualB->softViolationFactor < 0) exit(24);

	if (individualA->hardViolationFactor == individualB->hardViolationFactor) {
		if (individualA->softViolationFactor == individualB->softViolationFactor) {
			return 0;
		} else if(individualA->softViolationFactor > individualB->softViolationFactor) {
			return -1;
		} else {
			return 1;
		}
	} else if(individualA->hardViolationFactor > individualB->hardViolationFactor) {
		return -1;
	} else {
		return 1;
	}
}

struct Individual* Individual_clone(struct Individual* original) {
	struct Individual* clone = Individual(original->numberOfGenes);
	clone->hardViolationFactor = original->hardViolationFactor;
	clone->softViolationFactor = original->softViolationFactor;
	for (int geneNumber = 0; geneNumber < clone->numberOfGenes; geneNumber++) {
		clone->genes[geneNumber] = Gene_clone(original->genes[geneNumber]);
	}
	return clone;
}
