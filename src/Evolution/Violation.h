/*
 * Violation.h
 *
 *  Created on: 8 maj 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_VIOLATION_H_
#define EVOLUTION_VIOLATION_H_
#include <limits.h>

struct Violation {
	int hard;
	int soft;
};

int Violation_compare(struct Violation* violationA, struct Violation* violationB);
float Violation_getInversed(struct Violation* violation, int biggestSoftViolation);

#endif /* EVOLUTION_VIOLATION_H_ */
