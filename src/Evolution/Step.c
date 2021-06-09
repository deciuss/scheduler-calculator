/*
 * Step.c
 *
 *  Created on: 8 maj 2021
 *      Author: deciuss
 */
#include "Step.h"

struct Step* Step(
	int successArraySize,
	double incrementFactor,
	double incrementRule,
	double factorMax,
	double factorMin
) {

	struct Step* step = malloc(sizeof(struct Step));
	step->successArraySize = successArraySize;
	step->incrementFactor = incrementFactor;
	step->incrementRule = incrementRule;
	step->factorMax = factorMax;
	step->factorMin = factorMin;

	step->sucessArray = malloc(sizeof(bool) * successArraySize);
	step->currentFactor = 1;
	step->generationCounter = 0;

	step->lastViolation = malloc(sizeof(struct Violation));
	step->lastViolation->hard = INT_MAX;
	step->lastViolation->soft = INT_MAX;

	return step;
}

void _Step_updateCurrentFactor(struct Step* step) {
	if (step->generationCounter < step->successArraySize) {
		return;
	}

	double numberOfSuccesses = 0;

	for (int i = 0; i < step->successArraySize; i++) {
		if (step->sucessArray[i] == true) {
			numberOfSuccesses += 1.0;
		}
	}

	step->currentFactor *=
		((numberOfSuccesses / step->successArraySize) >= step->incrementRule)
//		? step->incrementFactor
//		: 1 / step->incrementFactor
		? 1 / step->incrementFactor
		: step->incrementFactor
	;

	if (step->currentFactor < step->factorMin || step->currentFactor > step->factorMax){
		step->currentFactor = 1;
	}
}

void Step_addCurrentGenerationViolation(struct Step* step, struct Violation* violation) {
	step->sucessArray[step->generationCounter % step->successArraySize] =
		(Violation_compare(step->lastViolation, violation) < 0)
			? true
			: false
	;
	step->lastViolation->hard = violation->hard;
	step->lastViolation->soft = violation->soft;

	step->generationCounter++;

	_Step_updateCurrentFactor(step);
}
