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

	struct Data* data = Decoder_decode(CONFIGURATION_INPUT_DATA_PATHNAME);

	struct Parameters* parameters = Parameters(
		1000,		// populationCardinality
		3,			// numberOfFamilies
		330,		// numberOfChildrenInFamily
		0,			// numberOfSurvivors
		0,			// numberOfClones
		999999,		// numberOfGenerations
		1.2,		// mutationRateEventBlockRelocation
		1.01,		// stepIncrementFactor
		1/5,		// stepIncrementRule
		10.0,		// stepFactorMax
		0.0000001,	// stepFactorMin
		10			// stepMemory
	);

	struct Population* population = Evolution_execute(parameters, configuration, data);

	Encoder_writeIndividualToFinalCsvFile(configuration, Population_getNthBestIndividual(population, 0));

    return 0;
}
