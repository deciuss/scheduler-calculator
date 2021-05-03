/*
 * Evolution.c
 *
 *  Created on: 28 kwi 2021
 *      Author: deciuss
 */
#include "Evolution.h"

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
    	Individual_updateGene(child, geneIndex, Gene_clone(parents[currentParentIndex]->genes[geneIndex]));
        if (parents[currentParentIndex]->genes[geneIndex]->isLastBlock == true){
        	currentParentIndex = Utils_getRandomInteger(0, 1);
        }
    }

    return child;
}

void _Evolution_mutate(struct Parameters* parameters, struct Data* data, struct Population* population) {
	for (int individualIndex = 0; individualIndex < population->size; individualIndex++){
		Mutation_execute(parameters, data, population->individuals[individualIndex]);
	}
}

void _Evolution_nextGeneration(struct Parameters* parameters, struct Data* data, struct Population* population) {

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

	_Evolution_mutate(parameters, data, population);
}

struct Population* Evolution_execute(struct Parameters* parameters, struct Data* data) {

	struct Population* population = Population_create(parameters->populationCardinality, data);

	struct Individual* bestIndividual = Individual(data->numberOfEvents);

	for (int generationNumber = 0; generationNumber < parameters->numberOfGenerations; generationNumber++) {

		_Evolution_calculatePopulationFitness(data, population);

		if (Individual_compare(bestIndividual, Population_getNthBestIndividual(population, 0)) < 0) {
			Individual_destruct(bestIndividual);
			bestIndividual = Individual_clone(Population_getNthBestIndividual(population, 0));
			Encoder_writeIndividualToCsvFile(bestIndividual);
		}

		Logger_logProgress(generationNumber, Population_getNthBestIndividual(population, 0), bestIndividual, true);

		_Evolution_nextGeneration(parameters, data, population);
	}


	return population;
}
