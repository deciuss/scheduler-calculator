/*
 * Fitness.h
 *
 *  Created on: 1 maj 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_FITNESS_H_
#define EVOLUTION_FITNESS_H_
#include "Individual.h"
#include "Gene.h"
#include "../Input/Data.h"
#include "../Utils.h"
#include "../Violation/Hard/Collision.h"
#include "../Violation/Soft/GroupGap.h"
#include "../Violation/Soft/TeacherGap.h"

int Fitness_calculateHardViolationFactor(struct Data* data, struct Individual* individual);
int Fitness_calculateSoftViolationFactor(struct Data* data, struct Individual* individual);

#endif /* EVOLUTION_FITNESS_H_ */
