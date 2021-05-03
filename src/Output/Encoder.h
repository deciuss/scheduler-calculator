/*
 * Encoder.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef OUTPUT_ENCODER_H_
#define OUTPUT_ENCODER_H_
#include <stdio.h>
#include "../Evolution/Individual.h"
#include "../Configuration.h"

void Encoder_writeIndividualToCsvFile(struct Individual* individual);
void Encoder_writeIndividualToCsvFileWithName(struct Individual* individual, const char * filename);

#endif /* OUTPUT_ENCODER_H_ */
