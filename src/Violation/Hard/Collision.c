/*
 * Collision.c
 *
 *  Created on: 4 maj 2021
 *      Author: deciuss
 */
#include "Collision.h"

int Collision_calculate(struct Data* data, struct Individual* individual) {

    int collisions = 0;

    bool** roomTimeslotPairUsed = Utils_constructBoolMatrix(data->numberOfTimeslots, data->numberOfRooms, false);

    for (int i = 0; i < data->numberOfEvents; i++) {
        if (roomTimeslotPairUsed[individual->genes[i]->timeslot][individual->genes[i]->room] == true) {
            collisions++;
        }
        roomTimeslotPairUsed[individual->genes[i]->timeslot][individual->genes[i]->room] = true;

        for (int j = i; j < data->numberOfEvents; j++) {
            if (i == j) continue;
            if (individual->genes[i]->timeslot != individual->genes[j]->timeslot) continue;
            if (data->eventTimeslotShare[i][j] == false) {
                collisions++;
            }
        }
    }

    Utils_destructBoolMatrix(roomTimeslotPairUsed, data->numberOfTimeslots, data->numberOfRooms);

    return collisions;
}

