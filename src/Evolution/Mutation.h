/*
 * Mutation.h
 *
 *  Created on: 2 maj 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_MUTATION_H_
#define EVOLUTION_MUTATION_H_
#include "Parameters.h"
#include "Individual.h"
#include "Step.h"
#include "../Input/Data.h"
#include "../Utils.h"

void Mutation_execute(
	struct Parameters* parameters,
	struct Data* Data,
	struct Step* step,
	struct Individual* individual
);

#endif /* EVOLUTION_MUTATION_H_ */
