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

void Individual_destruct(struct Individual* individual) {
    for (int i = 0; i < individual->numberOfGenes; i++) {
        Gene_destruct(individual->genes[i]);
    }
    free(individual);
}

int Individual_compare(struct Individual* individualA, struct Individual* individualB) {
	if (individualA->hardViolationFactor == NULL) exit(263);
	if (individualB->hardViolationFactor == NULL) exit(264);
	if (individualA->softViolationFactor == NULL) exit(263);
	if (individualB->softViolationFactor == NULL) exit(264);

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
