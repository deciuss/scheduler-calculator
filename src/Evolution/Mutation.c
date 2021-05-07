/*
 * Mutation.c
 *
 *  Created on: 2 maj 2021
 *      Author: deciuss
 */

#include "Mutation.h"

void _Mutation_eventBlockRelocation(struct Data* data, struct Individual* individual) {
    Individual_initializeGeneBlock(
		data,
		data->eventBlocks[Utils_getRandomInteger(0, data->numberOfEventBlocks - 1)],
		individual
	);

    individual->hardViolationFactor = INT_MAX;
    individual->softViolationFactor = INT_MAX;

}

void Mutation_execute(struct Parameters* parameters, struct Data* data, struct Individual* individual) {
	for (int i = 0; i < Utils_floor(parameters->mutationRateEventBlockRelocation); i++) {
		_Mutation_eventBlockRelocation(data, individual);
	}
	if (
		(int) ((Utils_modf(parameters->mutationRateEventBlockRelocation)) * 1000)
		> Utils_getRandomInteger(0, 1000)
	) {
		_Mutation_eventBlockRelocation(data, individual);
	}
}
