/*
 * Population.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */
#include "Population.h"
#include "Individual.h"

struct Population* Population(int size) {
    struct Population* population = malloc(sizeof(struct Population));
    population->size = size;
    population->individuals = malloc(sizeof(struct Individual*) * size);
    return population;
}
