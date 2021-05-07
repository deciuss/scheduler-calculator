/*
 * Evolution.c
 *
 *  Created on: 28 kwi 2021
 *      Author: deciuss
 */
#include "Evolution.h"

void _Evolution_calculatePopulationFitness(struct Data* data, struct Population* population) {
	for (int individualIndex = 0; individualIndex < population->size; individualIndex++) {
		population->individuals[individualIndex]->violation->hard =
				Fitness_calculateHardViolationFactor(data, population->individuals[individualIndex]);

		if (population->individuals[individualIndex]->violation->hard > 0) {
			continue;
		}

		population->individuals[individualIndex]->violation->soft =
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
	bool isProtected;
	for (int individualIndex = 0; individualIndex < population->size; individualIndex++){
		isProtected = false;
		for (int survivor = 0; survivor < parameters->numberOfSurvivors; survivor++) {
			if (population->ranking[survivor] == individualIndex) {
				isProtected = true;
				break;
			}
		}
		if (isProtected) continue;
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

	for (int clone = 0; clone < parameters->numberOfClones; clone++) {
		Population_replaceNthWorstIndividual(
			population,
			toReplaceIndex++,
			Individual_clone(Population_getNthBestIndividual(population, clone))
		);
	}

	_Evolution_mutate(parameters, data, population);
}

void _Evolution_assertNoDegenerationIfSurvivorsPresent(
	struct Parameters* parameters,
	struct Individual* bestIndividual,
	struct Population* population
) {
	if (
		parameters->numberOfSurvivors > 0
		&& Individual_compare(bestIndividual, Population_getNthBestIndividual(population, 0)) > 0
	) {
		exit(67);
	}
}

struct Population* Evolution_execute(
	struct Parameters* parameters,
	struct Configuration* configuration,
	struct Data* data
) {

	struct Population* population = Population_create(parameters->populationCardinality, data);

	struct Individual* bestIndividual = Individual(data->numberOfEvents);
	struct Individual* lastBestIndividual = Individual(data->numberOfEvents);

	double sigma1 = 1.01;
	double sigma2 = 0.99;

	for (int generationNumber = 0; generationNumber < parameters->numberOfGenerations; generationNumber++) {

		_Evolution_calculatePopulationFitness(data, population);

		if (Individual_compare(bestIndividual, Population_getNthBestIndividual(population, 0)) < 0) {
			Individual_destruct(bestIndividual);
			bestIndividual = Individual_clone(Population_getNthBestIndividual(population, 0));
			if (bestIndividual->violation->hard == 0) {
				Encoder_writeIndividualToTempCsvFile(configuration, generationNumber, bestIndividual);
			}
		}

		printf("%f\n", parameters->mutationRateEventBlockRelocation);

		Logger_logProgress(
			configuration,
			generationNumber,
			Population_getNthBestIndividual(population, 0),
			bestIndividual,
			true
		);

		if (bestIndividual->violation->hard == 0 && bestIndividual->violation->soft == 0) {
			break;
		}

		_Evolution_assertNoDegenerationIfSurvivorsPresent(parameters, bestIndividual, population);

		int result = Individual_compare(lastBestIndividual, Population_getNthBestIndividual(population, 0));
		int lastDecission = 1;

		if (result < 0 ) {
			// improvement!
			// enlarge
			parameters->mutationRateEventBlockRelocation = parameters->mutationRateEventBlockRelocation * sigma1;
			lastDecission = 1;
		} else if (result > 0 ) {
			// degeneration
			// decrese
			parameters->mutationRateEventBlockRelocation = parameters->mutationRateEventBlockRelocation * sigma2;
			lastDecission = -1;
		} else {
			//equal

//			parameters->mutationRateEventBlockRelocation = parameters->mutationRateEventBlockRelocation * sigma2;

			if (parameters->mutationRateEventBlockRelocation < 1.2) {
//////			if (lastDecission > 0) {
				parameters->mutationRateEventBlockRelocation = parameters->mutationRateEventBlockRelocation * 1.01;
			} else {
				parameters->mutationRateEventBlockRelocation = parameters->mutationRateEventBlockRelocation * 0.99;
			}



		}

		Individual_destruct(lastBestIndividual);
		lastBestIndividual = Individual_clone(Population_getNthBestIndividual(population, 0));


		_Evolution_nextGeneration(parameters, data, population);





	}


	return population;
}
