/*
 * Collision.h
 *
 *  Created on: 4 maj 2021
 *      Author: deciuss
 */

#ifndef VIOLATION_HARD_COLLISION_H_
#define VIOLATION_HARD_COLLISION_H_
#include <stdbool.h>
#include "../../Input/Data.h"
#include "../../Evolution/Individual.h"

int Collision_calculate(struct Data* data, struct Individual* individual);

#endif /* VIOLATION_HARD_COLLISION_H_ */
