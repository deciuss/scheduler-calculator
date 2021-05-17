/*
 * Configuration.c
 *
 *  Created on: 6 maj 2021
 *      Author: deciuss
 */
#include "Configuration.h"

struct Configuration* Configuration(int argc, char * argv[]) {

	struct Configuration* configuration = malloc(sizeof(struct Configuration));

	configuration->inputDataPathname = malloc(sizeof(char) * 255);
	configuration->outputDataPathname = malloc(sizeof(char) * 255);
	configuration->logPathname = malloc(sizeof(char) * 255);

	configuration->inputDataPathname = CONFIGURATION_INPUT_DATA_PATHNAME;
	configuration->outputDataPathname = CONFIGURATION_OUTPUT_DATA_PATHNAME;
	configuration->numberOfGenerations = CONFIGURATION_NUMBER_OF_GENERATIONS;

	if (argc >= 2) {
		configuration->inputDataPathname = argv[1];
	}

	if (argc >= 3) {
		configuration->outputDataPathname = argv[2];
	}

	if (argc >= 4) {
		configuration->numberOfGenerations = atoi(argv[3]);
	}

	strcat(configuration->logPathname, configuration->outputDataPathname);
	strcat(configuration->logPathname, ".log");

	return configuration;
}

