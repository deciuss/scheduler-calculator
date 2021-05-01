/*
 * Parameters.h
 *
 *  Created on: 28 kwi 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_PARAMETERS_H_
#define EVOLUTION_PARAMETERS_H_

struct Parameters {
    int populationCardinality;
    int numberOfFamilies;
    int numberOfChildrenInFamily;
    int mutation1Rate;
    int numberOfGenerations;
};

void Parameters_validate(struct Parameters* parameters);

#endif /* EVOLUTION_PARAMETERS_H_ */
