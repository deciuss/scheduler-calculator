/*
 * evolution.h
 *
 *  Created on: 26 kwi 2021
 *      Author: sbak
 */

#ifndef EVOLUTION_H_
#define EVOLUTION_H_
#include <limits.h>
#include <stdbool.h>
#include "Node.h"
#include "Params.h"
#include "configuration.h"

int randInt(int lower, int upper);

void copyIntMatrix(int sizeX, int sizeY, int oryginal[sizeX][sizeY], int replica[sizeX][sizeY]);

int calculateHardViolation(
        struct Params p,
        int individual[p.numberOfEvents][3],
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents]
);

void populateTimeslotRoomEventMatrix(
        struct Params p,
        int individual[p.numberOfEvents][3],
        int timeslotRoomEventMatrix[p.numberOfTimeslots][p.numberOfRooms]
);

int calculateRemainingBlockSize(
        struct Params p,
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int timeslotRoomEventMatrix[p.numberOfTimeslots][p.numberOfRooms],
        int timeslot,
        int room,
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int remainingBlockSize,
        bool timeslotRoomChecked[p.numberOfTimeslots][p.numberOfRooms]
);



int calculateViolation(
        struct Params p,
        int individual[p.numberOfEvents][3],
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int eventBlockSize[p.numberOfEvents],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2]
);

int getRoomForEvent(struct Params p, bool eventRoomFit[p.numberOfEvents][p.numberOfRooms], int event);

void initializeGene(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        struct Node *eventBlock,
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int individual[p.numberOfEvents][3]
);

void initializeIndividual(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        struct Node *eventBlock[p.numberOfBlocks],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int individual[p.numberOfEvents][3]
) ;

void initializePopulation(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        struct Node *eventBlock[p.numberOfBlocks],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int population[p.populationCardinality][p.numberOfEvents][3]
);

int findBestIndividual(
        struct Params p,
        int population[p.populationCardinality][p.numberOfEvents][3],
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int eventBlockSize[p.numberOfEvents],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int rangeMin,
        int rangeMax
);

void selectSurvivors(
        struct Params p,
        int population[p.populationCardinality][p.numberOfEvents][3],
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int eventBlockSize[p.numberOfEvents],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int survivorIdexes[p.numberOfSurvivors]
);

void reproduce(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        int parents[2][p.numberOfEvents][3],
        int child[p.numberOfEvents][3]
);

void mutation1 (
        struct Params p,
        int individual[p.numberOfEvents][3]
);

void mutation2 (
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        struct Node *eventBlock[p.numberOfBlocks],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int individual[p.numberOfEvents][3]
);

void mutation3 (
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int individual[p.numberOfEvents][3]
);

void mutate(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        struct Node *eventBlock[p.numberOfBlocks],
        int individual[p.numberOfEvents][3]
);

void nextGeneration(
        struct Params p,
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        int survivorIdexes[p.numberOfSurvivors],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        struct Node *eventBlock[p.numberOfBlocks],
        int population[p.populationCardinality][p.numberOfEvents][3]
) ;

void doEvolution(
        struct Params p,
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int eventBlockSize[p.numberOfEvents],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        struct Node *eventBlock[p.numberOfBlocks],
        int numberOfGenerations
);


#endif /* EVOLUTION_H_ */
