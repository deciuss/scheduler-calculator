/*
 * Gap.h
 *
 *  Created on: 3 maj 2021
 *      Author: deciuss
 */

#ifndef VIOLATION_SOFT_GAP_H_
#define VIOLATION_SOFT_GAP_H_
#include <stdbool.h>
#include "../../../Utils.h"
#include "../../../Input/Data.h"

struct Gap {
	bool dayOff;
	int gaps;
	int tempGaps;
	bool eventPresentInPreviousStep;
};

int Gap_calculate(struct Data* data, int numberOfSubjects, bool** timeslotSubject);

#endif /* VIOLATION_SOFT_GAP_H_ */
