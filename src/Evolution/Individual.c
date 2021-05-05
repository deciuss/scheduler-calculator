/*
 * Individual.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */
#include "Individual.h"

struct Individual* Individual(int numberOfGenes) {
    struct Individual* individual = malloc(sizeof(struct Individual));
    individual->numberOfGenes = numberOfGenes;
    individual->hardViolationFactor = INT_MAX;
    individual->softViolationFactor = INT_MAX;
    individual->genes = malloc(sizeof(struct Gene*) * numberOfGenes);
    for (int i = 0; i < numberOfGenes; i++) {
    	individual->genes[i] = Gene(0, 0);
    }
    return individual;
}

void Individual_updateGene(struct Individual* individual, int position, struct Gene * gene) {
    Gene_destruct(individual->genes[position]);
    individual->genes[position] = gene;
}

void Individual_destruct(struct Individual* individual) {
    for (int i = 0; i < individual->numberOfGenes; i++) {
        Gene_destruct(individual->genes[i]);
    }
    free(individual->genes);
    free(individual);
}

/**
 * Returns -1 if individualA violation > individualB violation <=> individualB is healthier
 * Returns  1 if individualA violation < individualB violation <=> individualA is healthier
 * Returns  0 if individualA violation == individualB violation
 */
int Individual_compare(struct Individual* individualA, struct Individual* individualB) {

	if (individualA->hardViolationFactor == individualB->hardViolationFactor) {
		if (individualA->softViolationFactor == individualB->softViolationFactor) {
			return 0;
		} else if(individualA->softViolationFactor > individualB->softViolationFactor) {
			return -1;
		} else {
			return 1;
		}
	} else if(individualA->hardViolationFactor > individualB->hardViolationFactor) {
		return -1;
	} else {
		return 1;
	}
}

struct Individual* Individual_clone(struct Individual* original) {
	struct Individual* clone = Individual(original->numberOfGenes);
	clone->hardViolationFactor = original->hardViolationFactor;
	clone->softViolationFactor = original->softViolationFactor;
	for (int geneNumber = 0; geneNumber < clone->numberOfGenes; geneNumber++) {
		Individual_updateGene(clone, geneNumber, Gene_clone(original->genes[geneNumber]));
	}
	return clone;
}

int _Individual_getRandomTimeslot(struct Data* data) {
	return Utils_getRandomInteger(0, data->numberOfTimeslots - 1);
}

int _Individual_getRoomForEvent(struct Data* data, int event) {
    int room;
    while (1) {
        room = Utils_getRandomInteger(0, data->numberOfRooms - 1);
        if (data->eventRoomFit[event][room] == true) return room;
    }
}

void Individual_initializeGeneBlock(struct Data* data, struct OneToMany* eventBlock, struct Individual* individual) {
    int room = _Individual_getRoomForEvent(data, eventBlock->items[0]);
    bool success = false;
    while (! success) {
        success = true;
        int timeslot = _Individual_getRandomTimeslot(data);
        int i = 0;
        while (true) {
			struct Gene* gene = Gene(timeslot, room);
			Individual_updateGene(individual, eventBlock->items[i], gene);
			if (++i == eventBlock->size) {
				gene->isLastBlock = true;
				break;
			}
			timeslot = data->timeslotNeighborNext[timeslot];
			if (timeslot < 0) {
				success = false;
				break;
			}
        }
    }
}

struct Individual* Individual_create(struct Data* data) {
	struct Individual* individual = Individual(data->numberOfEvents);
    for (int i = 0; i < data->numberOfEventBlocks; i++) {
    	Individual_initializeGeneBlock(data, data->eventBlocks[i], individual);
    }
    return individual;
}
