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
    int numberOfGenerations;
    double mutationRateEventBlockRelocation;
};

void Parameters_validate(struct Parameters* parameters);

#endif /* EVOLUTION_PARAMETERS_H_ */
