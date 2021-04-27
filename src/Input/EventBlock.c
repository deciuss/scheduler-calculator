/*
 * EventBlock.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#include "EventBlock.h"

struct EventBlock* EventBlock(int size) {
	struct EventBlock* eventBlock = malloc(sizeof(struct EventBlock));
	eventBlock->size = size;
	eventBlock->events = malloc(sizeof(int) * size);
	return eventBlock;
}
