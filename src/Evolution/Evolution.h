/*
 * Evolution.h
 *
 *  Created on: 28 kwi 2021
 *      Author: deciuss
 */

#ifndef EVOLUTION_EVOLUTION_H_
#define EVOLUTION_EVOLUTION_H_
#include "Parameters.h"
#include "Population.h"
#include "Individual.h"
#include "Gene.h"
#include "../Utils.h"
#include "../Input/Data.h"
#include "../Input/EventBlock.h"

struct Population* Evolution_execute(struct Parameters* p, struct Data* data);

#endif /* EVOLUTION_EVOLUTION_H_ */
