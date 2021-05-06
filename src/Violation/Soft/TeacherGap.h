/*
 * TeacherGap.h
 *
 *  Created on: 7 maj 2021
 *      Author: deciuss
 */

#ifndef VIOLATION_SOFT_TEACHERGAP_H_
#define VIOLATION_SOFT_TEACHERGAP_H_
#include <stdbool.h>
#include "Gap/Gap.h"
#include "../../Input/Data.h"
#include "../../Evolution/Individual.h"

int TeacherGap_calculate(struct Data* data, struct Individual* individual);


#endif /* VIOLATION_SOFT_TEACHERGAP_H_ */
