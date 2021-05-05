/*
 * GroupGap.h
 *
 *  Created on: 3 maj 2021
 *      Author: deciuss
 */

#ifndef VIOLATION_SOFT_GROUPGAP_H_
#define VIOLATION_SOFT_GROUPGAP_H_
#include <stdbool.h>
#include "Gap/Gap.h"
#include "../../Input/Data.h"
#include "../../Evolution/Individual.h"

int GroupGap_calculate(struct Data* data, struct Individual* individual);

#endif /* VIOLATION_SOFT_GROUPGAP_H_ */
