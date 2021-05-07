/*
 * GroupGap.c
 *
 *  Created on: 3 maj 2021
 *      Author: deciuss
 */
#include "GroupGap.h"

int GroupGap_calculate(struct Data* data, struct Individual* individual) {

	bool** timeslotGroup = Utils_constructBoolMatrix(data->numberOfTimeslots, data->numberOfGroups, false);

	for (int eventIndex = 0; eventIndex < individual->numberOfGenes; eventIndex++) {
		for (int g = 0; g < data->eventGroups[eventIndex]->size; g++) {
			timeslotGroup[individual->genes[eventIndex]->timeslot][data->eventGroups[eventIndex]->items[g]] = true;
		}
	}

	int gapCounter = Gap_calculate(data, data->numberOfGroups, timeslotGroup);

	Utils_destructBoolMatrix(timeslotGroup, data->numberOfTimeslots, data->numberOfGroups);

	return gapCounter;
}

