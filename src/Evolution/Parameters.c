/*
 * Parameters.c
 *
 *  Created on: 1 maj 2021
 *      Author: deciuss
 */
#include "Parameters.h"

void _Parameters_validate(struct Parameters* parameters) {
	if (
		parameters->numberOfFamilies * parameters->numberOfChildrenInFamily
		+ parameters->numberOfFamilies * 2
		> parameters->populationCardinality
	) {
		exit(233);
	}

	if (
		parameters->numberOfFamilies * parameters->numberOfChildrenInFamily
		+ parameters->numberOfClones
		+ parameters->numberOfSurvivors
		> parameters->populationCardinality
	) {
		exit(234);
	}
}

struct Parameters* parameters(
	int populationCardinality,
	int numberOfFamilies,
	int numberOfChildrenInFamily,
	int numberOfSurvivors,
	int numberOfClones,
	int numberOfGenerations,
	double mutationRateEventBlockRelocation,
	double stepIncrementFactor,
	double stepIncrementRule,
	int stepMemorySize
) {
	struct Parameters* parameters = malloc(sizeof(struct Parameters));
	parameters->populationCardinality = populationCardinality;
	parameters->numberOfFamilies = numberOfFamilies;
	parameters->numberOfChildrenInFamily = numberOfChildrenInFamily;
	parameters->numberOfSurvivors = numberOfSurvivors;
	parameters->numberOfClones = numberOfClones;
	parameters->numberOfGenerations = numberOfGenerations;
	parameters->mutationRateEventBlockRelocation = mutationRateEventBlockRelocation;
	parameters->stepIncrementFactor = stepIncrementFactor;
	parameters->stepMemorySize = stepMemorySize;

	_Parameters_validate(parameters);

	return parameters;

}



