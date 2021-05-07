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
#include "Params.h"
#include "Input/Data.h"
#include "Input/Decoder.h"
#include "Evolution/Parameters.h"
#include "Evolution/Evolution.h"

int main(int argc, char * argv[]) {

	srand(time(0));

	struct Configuration* configuration = Configuration(argc, argv);

	struct Data* data = Decoder_decode(CONFIGURATION_INPUT_DATA_PATHNAME);

	struct Parameters* parameters = malloc(sizeof(struct Parameters));
	parameters->populationCardinality = 1000;
	parameters->numberOfFamilies = 3;
	parameters->numberOfChildrenInFamily = 300;
	parameters->numberOfSurvivors = 1;
	parameters->numberOfClones = 20;
	parameters->mutationRateEventBlockRelocation = 1.2;
	parameters->numberOfGenerations = 1000000;
	Parameters_validate(parameters);

	struct Population* population = Evolution_execute(parameters, configuration, data);

	Encoder_writeIndividualToFinalCsvFile(configuration, Population_getNthBestIndividual(population, 0));

    return 0;
}
