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
#include "Node.h"
#include "Input/Data.h"
#include "Input/Decoder.h"
#include "Evolution/Parameters.h"
#include "Evolution/Evolution.h"

int main(int argc, char * argv[]) {

	srand(time(0));

	struct Data* data = Decoder_decode(CONFIGURATION_INPUT_DATA_PATH);
	struct Parameters* parameters = malloc(sizeof(struct Parameters));

	parameters->populationCardinality = 100;
	parameters->numberOfFamilies = 4;
	parameters->numberOfChildrenInFamily = 20;
	parameters->mutationRateEventBlockRelocation = 1.1;
	parameters->numberOfGenerations = 1000000;
	Parameters_validate(parameters);

	Evolution_execute(parameters, data);
    return 0;
}
