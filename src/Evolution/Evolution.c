/*
 * Evolution.c
 *
 *  Created on: 28 kwi 2021
 *      Author: deciuss
 */
#include "Evolution.h"

int _Evolution_getRandomTimeslot(struct Data* data) {
	return Utils_getRandomInteger(0, data->numberOfTimeslots - 1);
}

int _Evolution_getRoomForEvent(struct Data* data, int event) {
    int room;
    while (1) {
        room = Utils_getRandomInteger(0, data->numberOfRooms - 1);
        if (data->eventRoomFit[event][room] == true) return room;
    }
}

void _Evolution_initializeGeneBlock(struct Data* data, struct EventBlock* eventBlock, struct Individual* individual) {
    int room = _Evolution_getRoomForEvent(data, eventBlock->events[0]);
    bool success = false;
    while (! success) {
        success = true;
        int timeslot = _Evolution_getRandomTimeslot(data);
        int i = 0;
        while (true) {
			struct Gene* gene = Gene(timeslot, room);
			individual->genes[eventBlock->events[i]] = gene;
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

struct Individual* _Evolution_createIndividual(struct Data* data){
	struct Individual* individual = Individual(data->numberOfEvents);
    for (int i = 0; i < data->numberOfEventBlocks; i++) {
    	_Evolution_initializeGeneBlock(data, data->eventBlocks[i], individual);
    }
    return individual;
}

struct Population* _Evolution_createPopulation(struct Parameters* parameters, struct Data* data){
	struct Population* population = Population(parameters->populationCardinality);
    for (int i = 0; i < parameters->populationCardinality; i++) {
       population->individuals[i] = _Evolution_createIndividual(data);
    }
    return population;
}

void _Evolution_calculatePopulationFitness(struct Data* data, struct Population* population) {
	for (int individualIndex = 0; individualIndex < population->size; individualIndex++) {
		population->individuals[individualIndex]->hardViolationFactor =
				Fitness_calculateHardViolationFactor(data, population->individuals[individualIndex]);
		population->individuals[individualIndex]->softViolationFactor =
				Fitness_calculateSoftViolationFactor(data, population->individuals[individualIndex]);
	}
	Population_calculateRanking(population);
}

struct Individual* _Evolution_reproduce(struct Individual* parentA, struct Individual* parentB) {

    struct Individual* parents[2];
    parents[0] = parentA;
    parents[1] = parentB;
    int currentParentIndex = Utils_getRandomInteger(0, 1);

    struct Individual* child = Individual(parentA->numberOfGenes);

    for (int geneIndex = 0; geneIndex < parentA->numberOfGenes; geneIndex++) {
    	child->genes[geneIndex] = Gene_clone(parents[currentParentIndex]->genes[geneIndex]);
        if (parents[currentParentIndex]->genes[geneIndex]->isLastBlock == true){
        	currentParentIndex = Utils_getRandomInteger(0, 1);
        }
    }

    return child;
}

void _Evolution_nextGeneration(struct Parameters* parameters, struct Population* population) {

	int parentIndex = 0;
	int toReplaceIndex = 0;

	for (int family = 0; family < parameters->numberOfFamilies; family++) {
		for (int childInFamily = 0; childInFamily < parameters->numberOfChildrenInFamily; childInFamily++) {
			Population_replaceNthWorstIndividual(
					population,
					toReplaceIndex++,
					_Evolution_reproduce(
							Population_getNthBestIndividual(population, parentIndex),
							Population_getNthBestIndividual(population, parentIndex + 1)
					)
			);
		}
		parentIndex += 2;
	}
}

struct Population* Evolution_execute(struct Parameters* parameters, struct Data* data) {

	struct Population* population = _Evolution_createPopulation(parameters, data);

	struct Individual* bestIndividual = NULL;

	for (int generationNumber = 0; generationNumber < parameters->numberOfGenerations; generationNumber++) {

		_Evolution_calculatePopulationFitness(data, population);

		if (
			bestIndividual == NULL
			|| Individual_compare(bestIndividual, Population_getNthBestIndividual(population, 0)) < 0
		) {
			if (bestIndividual != NULL){
				Individual_destruct(bestIndividual);
			}
			bestIndividual = Individual_clone(Population_getNthBestIndividual(population, 0));
		}

		printf(
			"generation: %d; current best: %d/%d; overall best: %d/%d\n",
			generationNumber,
			Population_getNthBestIndividual(population, 0)->hardViolationFactor,
			Population_getNthBestIndividual(population, 0)->softViolationFactor,
			bestIndividual->hardViolationFactor,
			bestIndividual->softViolationFactor
		);

		_Evolution_nextGeneration(parameters, population);
	}


	return population;
}
