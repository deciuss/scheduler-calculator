/*
 * Parameters.c
 *
 *  Created on: 1 maj 2021
 *      Author: deciuss
 */
#include "Parameters.h"

void Parameters_validate(struct Parameters* parameters) {
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

