/*
 * Data.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef INPUT_DATA_H_
#define INPUT_DATA_H_
#include <stdbool.h>
#include <stdlib.h>
#include "EventBlock.h"

struct Data{
    int numberOfEvents;
    int numberOfRooms;
    int numberOfTimeslots;
    int numberOfEventBlocks;
    int* timeslotNeighborNext;
    struct EventBlock** eventBlocks;
    bool** eventTimeslotShare;
    bool** eventRoomFit;
};

struct Data* Data(int numberOfEvents, int numberOfRooms, int numberOfTimeslots, int numberOfEventBlocks);

#endif /* INPUT_DATA_H_ */
