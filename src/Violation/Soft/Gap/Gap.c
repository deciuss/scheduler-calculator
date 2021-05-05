/*
 * Gap.c
 *
 *  Created on: 3 maj 2021
 *      Author: deciuss
 */
#include "Gap.h"

struct Gap* Gap() {
	struct Gap* gap = malloc(sizeof(struct Gap));
	gap->dayOff = true;
	gap->gaps = 0;
	gap->tempGaps = 0;
	gap->eventPresentInPreviousStep = false;
	return gap;
}

void _Gap_step(struct Gap* gap, bool eventPresentInCurrentStep) {

	if (eventPresentInCurrentStep == true) {
		gap->dayOff = false;
	}

	if (gap->dayOff == true) {
		return;
	}

	if (eventPresentInCurrentStep == false) {
		gap->tempGaps++;
	} else if (gap->eventPresentInPreviousStep == false) {
		gap->gaps += gap->tempGaps;
		gap->tempGaps = 0;
	}

	gap->eventPresentInPreviousStep = eventPresentInCurrentStep;
}

void _Gap_endOfTheDay(struct Gap* gap) {
	gap->tempGaps = 0;
	gap->dayOff = true;
}

int Gap_calculate(struct Data* data, bool** timeslotSubject) {

	struct Gap** gaps = malloc(sizeof(struct Gap) * data->numberOfGroups);
	for (int groupIndex = 0; groupIndex < data->numberOfGroups; groupIndex++) {
		gaps[groupIndex] = Gap();
	}

	for (int timeslotIndex = 0; timeslotIndex < data->numberOfTimeslots; timeslotIndex++) {
		for (int groupIndex = 0; groupIndex < data->numberOfGroups; groupIndex++) {
			_Gap_step(gaps[groupIndex], timeslotSubject[timeslotIndex][groupIndex]);
			if (data->timeslotNeighborNext[timeslotIndex] < 0) {
				_Gap_endOfTheDay(gaps[groupIndex]);
			}
		}
	}

	int gapCounter = 0;

	for (int groupIndex = 0; groupIndex < data->numberOfGroups; groupIndex++) {
		gapCounter += gaps[groupIndex]->gaps;
		free(gaps[groupIndex]);
	}

	free(gaps);

	return gapCounter;
}

