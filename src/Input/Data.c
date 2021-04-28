/*
 * Data.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#include "Data.h"

bool** _Data_constructBoolMatrix(int sizeX, int sizeY) {
	bool** matrix = malloc(sizeof(bool *) * sizeX);
	for (int i = 0; i < sizeX; i++) {
		matrix[i] = malloc(sizeof(bool) * sizeY);
	}
	return matrix;
}

void _Data_destructBoolMatrix(bool** matrix, int sizeX, int sizeY) {
	//
}

struct Data* Data(int numberOfEvents, int numberOfRooms, int numberOfTimeslots, int numberOfEventBlocks) {

	struct Data* data = malloc(sizeof(struct Data));

	data->numberOfEvents = numberOfEvents;
	data->numberOfRooms = numberOfRooms;
	data->numberOfTimeslots = numberOfTimeslots;
	data->numberOfEventBlocks = numberOfEventBlocks;
	data->timeslotNeighborNext = malloc(sizeof(int) * numberOfTimeslots);
	data->eventBlocks = malloc(sizeof(struct EventBlock*) * numberOfEventBlocks);
	data->eventTimeslotShare = _Data_constructBoolMatrix(numberOfEvents, numberOfEvents);
	data->eventRoomFit = _Data_constructBoolMatrix(numberOfEvents, numberOfRooms);

	return data;
}


