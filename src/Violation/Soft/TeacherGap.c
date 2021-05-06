/*
 * TeacherGap.c
 *
 *  Created on: 7 maj 2021
 *      Author: deciuss
 */
#include "TeacherGap.h"

int TeacherGap_calculate(struct Data* data, struct Individual* individual) {

	bool** timeslotTeacher = Utils_constructBoolMatrix(data->numberOfTimeslots, data->numberOfTeachers, false);

	for (int eventIndex = 0; eventIndex < individual->numberOfGenes; eventIndex++) {
		timeslotTeacher[individual->genes[eventIndex]->timeslot][data->eventTeacher[eventIndex]] = true;
	}

	int gapCounter = Gap_calculate(data, timeslotTeacher);

	Utils_destructBoolMatrix(timeslotTeacher, data->numberOfTimeslots, data->numberOfTeachers);

	return gapCounter;
}
