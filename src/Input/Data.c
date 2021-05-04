/*
 * Data.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#include "Data.h"

struct Data* Data(
	int numberOfEvents,
	int numberOfRooms,
	int numberOfTimeslots,
	int numberOfEventBlocks,
	int numberOfGroups
) {

	struct Data* data = malloc(sizeof(struct Data));

	data->numberOfEvents = numberOfEvents;
	data->numberOfRooms = numberOfRooms;
	data->numberOfTimeslots = numberOfTimeslots;
	data->numberOfEventBlocks = numberOfEventBlocks;
	data->numberOfGroups = numberOfGroups;
	data->timeslotNeighborNext = malloc(sizeof(int) * numberOfTimeslots);
	data->eventGroup = malloc(sizeof(int) * numberOfEvents);
	data->eventBlocks = malloc(sizeof(struct EventBlock*) * numberOfEventBlocks);
	data->eventTimeslotShare = Utils_constructBoolMatrix(numberOfEvents, numberOfEvents, false);
	data->eventRoomFit = Utils_constructBoolMatrix(numberOfEvents, numberOfRooms, false);

	return data;
}


