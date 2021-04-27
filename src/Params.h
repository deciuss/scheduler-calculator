/*
 * Params.h
 *
 *  Created on: 26 kwi 2021
 *      Author: sbak
 */

#ifndef PARAMS_H
#define PARAMS_H
struct Params {
    int numberOfEvents;
    int numberOfTimeslots;
    int numberOfRooms;
    int populationCardinality;
    int numberOfSurvivors;
    int maxBlockSize;
    int numberOfBlocks;
    int hardViolationFactor;
    int mutation1Rate;
    int mutation2Rate;
    int mutation3Rate;
    int broodSplit[2][2];
};
#endif
