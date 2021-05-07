/*
 * Violation.c
 *
 *  Created on: 8 maj 2021
 *      Author: deciuss
 */
#include "Violation.h"

/**
 * Returns -1 if violationA violation > violationB violation <=> violationB is healthier
 * Returns  1 if violationA violation < violationB violation <=> violationA is healthier
 * Returns  0 if violationA violation == violationB violation
 */
int Violation_compare(struct Violation* violationA, struct Violation* violationB) {

	if (violationA->hard == violationB->hard) {
		if (violationA->soft == violationB->soft) {
			return 0;
		} else if(violationA->soft > violationB->soft) {
			return -1;
		} else {
			return 1;
		}
	} else if(violationA->hard > violationB->hard) {
		return -1;
	} else {
		return 1;
	}
}

