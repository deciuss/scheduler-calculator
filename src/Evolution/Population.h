/*
 * Population.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_POPULATION_H_
#define EVOLUTION_POPULATION_H_
#include <stdlib.h>

struct Population {
    struct Individual** individuals;
    int size;
};

struct Population* Population(int size);

#endif /* EVOLUTION_POPULATION_H_ */
