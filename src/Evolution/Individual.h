/*
 * Individual.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_
#include "Gene.h"

struct Individual {
    struct Gene** genes;
    int numberOfGenes;
    int hardViolationFactor;
    int softViolationFactor;
};

struct Individual* Individual(int numberOfGenes);
void Individual_updateGene(struct Individual* individual, int position, struct Gene * gene);
void Individual_destruct(struct Individual* individual);
int Individual_compare(struct Individual* individualA, struct Individual * individualB);
struct Individual* Individual_clone(struct Individual* original);

#endif /* INDIVIDUAL_H_ */
