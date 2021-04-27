/*
 * Population.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef POPULATION_POPULATION_H_
#define POPULATION_POPULATION_H_
#include <stdlib.h>

struct Population {
    struct Individual** individuals;
    int size;
};

struct Population* Population(int size);

#endif /* POPULATION_POPULATION_H_ */
