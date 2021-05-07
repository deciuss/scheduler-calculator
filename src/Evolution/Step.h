/*
 * Step.h
 *
 *  Created on: 8 maj 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_STEP_H_
#define EVOLUTION_STEP_H_
#include "Violation.h"

struct Step {
	int memorySize;
	double incrementFactor;
	int* memory;
	double currentFactor;
};

struct Step* Step(
	int memorySize,
	double incrementFactor
);

void Step_addCurrentGenerationViolation(struct Violation* violation);

#endif /* EVOLUTION_STEP_H_ */
