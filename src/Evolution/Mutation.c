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

    individual->violation->hard = INT_MAX;
    individual->violation->soft = INT_MAX;

}

void Mutation_execute(
	struct Parameters* parameters,
	struct Data* data,
	struct Step* step,
	struct Individual* individual
) {

	double mutationRate = parameters->mutationRateEventBlockRelocation * step->currentFactor;

	for (int i = 0; i < Utils_floor(mutationRate); i++) {
		_Mutation_eventBlockRelocation(data, individual);
	}
	if (
		(int) ((Utils_modf(mutationRate)) * 10000)
		> Utils_getRandomInteger(0, 10000)
	) {
		_Mutation_eventBlockRelocation(data, individual);
	}
}
