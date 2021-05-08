/*
 * Evolution.h
 *
 *  Created on: 28 kwi 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_EVOLUTION_H_
#define EVOLUTION_EVOLUTION_H_
#include <stdio.h>
#include "Parameters.h"
#include "Population.h"
#include "Individual.h"
#include "Gene.h"
#include "Fitness.h"
#include "Mutation.h"
#include "Step.h"
#include "../Utils.h"
#include "../Configuration.h"
#include "../Logger.h"
#include "../Input/Data.h"
#include "../Input/OneToMany.h"
#include "../Output/Encoder.h"

struct Population* Evolution_execute(
	struct Parameters* p,
	struct Configuration* configuration,
	struct Data* data
);

#endif /* EVOLUTION_EVOLUTION_H_ */
