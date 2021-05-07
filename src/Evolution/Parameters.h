/*
 * Parameters.h
 *
 *  Created on: 28 kwi 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_PARAMETERS_H_
#define EVOLUTION_PARAMETERS_H_
#include <stdlib.h>

struct Parameters {
    int populationCardinality;
    int numberOfFamilies;
    int numberOfChildrenInFamily;
    int numberOfSurvivors;
    int numberOfClones;
    int numberOfGenerations;
    double mutationRateEventBlockRelocation;
    double stepIncrementFactor;
    double stepIncrementRule;
    int stepMemorySize;
};

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
);

#endif /* EVOLUTION_PARAMETERS_H_ */
