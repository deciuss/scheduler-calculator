/*
 * Fitness.c
 *
 *  Created on: 1 maj 2021
 *      Author: deciuss
 */
#include "Fitness.h"

int Fitness_calculateHardViolationFactor(struct Data* data, struct Individual* individual) {

    int violation = 0;

    violation += Collision_calculate(data, individual);

    return violation;
}

int Fitness_calculateSoftViolationFactor(struct Data* data, struct Individual* individual) {

    int violation = 0;

    violation += GroupGap_calculate(data, individual);
    violation += TeacherGap_calculate(data, individual);

    return violation;
}
