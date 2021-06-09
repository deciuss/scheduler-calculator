/*
 * main.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Configuration.h"
#include "Input/Data.h"
#include "Input/Decoder.h"
#include "Evolution/Parameters.h"
#include "Evolution/Evolution.h"

int main(int argc, char * argv[]) {

	srand(time(0));

	struct Configuration* configuration = Configuration(argc, argv);

	struct Data* data = Decoder_decode(configuration->inputDataPathname);

	struct Parameters* parameters = Parameters(
		/* selectionMethod */					0, /* 0 for mi+lambda, 1 for roulette selection */
		/* populationCardinality */				400,
		/* numberOfFamilies */					2,
		/* numberOfChildrenInFamily */			198,
		/* numberOfSurvivors */					0,
		/* numberOfClones */					0,
		/* numberOfGenerations */				configuration->numberOfGenerations,
		/* mutationRateEventBlockRelocation */	1.0,
		/* stepIncrementFactor */				1.01,
		/* stepIncrementRule */					0.2,
		/* stepFactorMax */						10.0,
		/* stepFactorMin */						0.0000001,
		/* stepMemory */						15
	);

	struct Population* population = Evolution_execute(parameters, configuration, data);

	if (Population_getNthBestIndividual(population, 0)->violation->hard > 0) {
		return 13;
	}

	Encoder_writeIndividualToFinalCsvFile(configuration, Population_getNthBestIndividual(population, 0));

    return 0;
}
