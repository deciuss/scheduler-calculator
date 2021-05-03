/*
 * GroupGap.h
 *
 *  Created on: 3 maj 2021
 *      Author: deciuss
 */

#ifndef VIOLATION_SOFT_GROUPGAP_H_
#define VIOLATION_SOFT_GROUPGAP_H_
#include <stdbool.h>
#include "../../Utils.h"
#include "../../Input/Data.h"
#include "../../Evolution/Individual.h"

struct GroupGap {
	bool dayOff;
	int gaps;
	int tempGaps;
	bool eventPresentInPreviousStep;
};

#endif /* VIOLATION_SOFT_GROUPGAP_H_ */
