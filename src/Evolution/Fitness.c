/*
 * Fitness.c
 *
 *  Created on: 1 maj 2021
 *      Author: deciuss
 */
#include "Fitness.h"


int Fitness_calculateHardViolationFactor(struct Data* data, struct Individual* individual) {

    int violation = 0;

    bool** roomTimeslotPairUsed = Utils_constructBoolMatrix(data->numberOfTimeslots, data->numberOfRooms, false);

    for (int i = 0; i < data->numberOfEvents; i++) {

        if (roomTimeslotPairUsed[individual->genes[i]->timeslot][individual->genes[i]->room] == true) {
            violation++;
        }
        roomTimeslotPairUsed[individual->genes[i]->timeslot][individual->genes[i]->room] = true;

        for (int j = i; j < data->numberOfEvents; j++) {
            if (i == j) continue;
            if (individual->genes[i]->timeslot != individual->genes[j]->timeslot) continue;
            if (data->eventTimeslotShare[i][j] == false) {
                violation++;
            }
        }
    }

    Utils_destructBoolMatrix(roomTimeslotPairUsed, data->numberOfTimeslots, data->numberOfRooms);

    return violation;
}

int Fitness_calculateSoftViolationFactor(struct Data* data, struct Individual* individual) {
	return 0; // @todo
}
