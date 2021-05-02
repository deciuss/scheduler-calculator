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
			> parameters->populationCardinality - parameters->numberOfFamilies * 2
	) {
		exit(233);
	}
}

