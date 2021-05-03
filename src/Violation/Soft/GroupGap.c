/*
 * GroupGap.c
 *
 *  Created on: 3 maj 2021
 *      Author: deciuss
 */
#include "GroupGap.h"

struct GroupGap* GroupGap() {
	struct GroupGap* groupGap = malloc(sizeof(struct GroupGap));
	groupGap->dayOff = true;
	groupGap->gaps = 0;
	groupGap->tempGaps = 0;
	groupGap->eventPresentInPreviousStep = false;
	return groupGap;
}

void GroupGap_step(struct GroupGap* groupGap, bool eventPresentInCurrentStep) {

	if (eventPresentInCurrentStep == true) {
		groupGap->dayOff = false;
	}

	if (groupGap->dayOff == true) {
		return;
	}

	if (eventPresentInCurrentStep == false) {
		groupGap->tempGaps++;
	} else if (groupGap->eventPresentInPreviousStep == false) {
		groupGap->gaps += groupGap->tempGaps;
		groupGap->tempGaps = 0;
	}

	groupGap->eventPresentInPreviousStep = eventPresentInCurrentStep;
}

void GroupGap_endOfTheDay(struct GroupGap* groupGap) {
	groupGap->tempGaps = 0;
	groupGap->dayOff = true;
}

int GroupGap_calculate(struct Data* data, struct Individual* individual) {

	bool** timeslotGroup = Utils_constructBoolMatrix(data->numberOfTimeslots, data->numberOfGroups, false);

	for (int eventIndex = 0; eventIndex < individual->numberOfGenes; eventIndex++) {
		timeslotGroup[individual->genes[eventIndex]->timeslot][data->eventGroup[eventIndex]] = true;
	}

	struct GroupGap** groupGaps = malloc(sizeof(struct GroupGap) * data->numberOfGroups);
	for (int groupIndex = 0; groupIndex < data->numberOfGroups; groupIndex++) {
		groupGaps[groupIndex] = GroupGap();
	}

	for (int timeslotIndex = 0; timeslotIndex < data->numberOfTimeslots; timeslotIndex++) {
		for (int groupIndex = 0; groupIndex < data->numberOfGroups; groupIndex++) {
			GroupGap_step(groupGaps[groupIndex], timeslotGroup[timeslotIndex][groupIndex]);
			if (data->timeslotNeighborNext[timeslotIndex] < 0) {
				GroupGap_endOfTheDay(groupGaps[groupIndex]);
			}
		}
	}

	int gaps = 0;

	for (int groupIndex = 0; groupIndex < data->numberOfGroups; groupIndex++) {
		gaps += groupGaps[groupIndex]->gaps;
		free(groupGaps[groupIndex]);
	}

	free(groupGaps);
	Utils_destructBoolMatrix(timeslotGroup, data->numberOfTimeslots, data->numberOfGroups);

	return gaps;
}

