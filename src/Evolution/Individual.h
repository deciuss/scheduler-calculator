/*
 * Individual.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_
#include <limits.h>
#include "Gene.h"
#include "Violation.h"
#include "../Utils.h"
#include "../Input/Data.h"

struct Individual {
    struct Gene** genes;
    int numberOfGenes;
    struct Violation* violation;
};

struct Individual* Individual(int numberOfGenes);
void Individual_updateGene(struct Individual* individual, int position, struct Gene * gene);
void Individual_destruct(struct Individual* individual);
int Individual_compare(struct Individual* individualA, struct Individual * individualB);
struct Individual* Individual_clone(struct Individual* original);
void Individual_initializeGeneBlock(struct Data* data, struct OneToMany* eventBlock, struct Individual* individual);
struct Individual* Individual_create(struct Data* data);

#endif /* INDIVIDUAL_H_ */
