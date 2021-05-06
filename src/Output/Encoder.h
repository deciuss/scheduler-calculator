/*
 * Encoder.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef OUTPUT_ENCODER_H_
#define OUTPUT_ENCODER_H_
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../Evolution/Individual.h"
#include "../Configuration.h"

void Encoder_writeIndividualToTempCsvFile(
	struct Configuration* configuration,
	int generation,
		struct Individual* individual
);

void Encoder_writeIndividualToFinalCsvFile(
	struct Configuration* configuration,
	struct Individual* individual
);

#endif /* OUTPUT_ENCODER_H_ */
