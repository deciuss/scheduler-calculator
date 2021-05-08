/*
 * Step.h
 *
 *  Created on: 8 maj 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_STEP_H_
#define EVOLUTION_STEP_H_
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "Violation.h"

struct Step {
	int successArraySize;
	double incrementFactor;
	double incrementRule;
	bool* sucessArray;
	double currentFactor;
	double factorMax;
	double factorMin;
	int generationCounter;
	struct Violation* lastViolation;
};

struct Step* Step(
	int memorySize,
	double incrementFactor,
	double incrementRule,
	double factorMax,
	double factorMin
);

void Step_addCurrentGenerationViolation(struct Step* step, struct Violation* violation);

#endif /* EVOLUTION_STEP_H_ */
