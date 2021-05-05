/*
 * EventBlock.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#include "OneToMany.h"

struct OneToMany* OneToMany(int size) {
	struct OneToMany* oneToMany = malloc(sizeof(struct OneToMany));
	oneToMany->size = size;
	oneToMany->items = malloc(sizeof(int) * size);
	return oneToMany;
}
