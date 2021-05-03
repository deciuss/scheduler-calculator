/*
 * Logger.h
 *
 *  Created on: 3 maj 2021
 *      Author: deciuss
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Configuration.h"
#include "Evolution/Individual.h"

void Logger_logProgress(
	int generationNumber,
	struct Individual* currentBest,
	struct Individual* overallBest,
	bool verbose
);

#endif /* LOGGER_H_ */
