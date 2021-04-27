/*
 * evolution.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#include "evolution.h"
int randInt(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

void copyIntMatrix(int sizeX, int sizeY, int oryginal[sizeX][sizeY], int replica[sizeX][sizeY]) {
    for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++)
            replica[i][j] = oryginal[i][j];
}

int calculateHardViolation(
        struct Params p,
        int individual[p.numberOfEvents][3],
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents]
) {
    int violation = 0;
    bool roomTimeslotPairUsed[p.numberOfTimeslots][p.numberOfRooms];
    populateBoolMatrix(p.numberOfTimeslots, p.numberOfRooms, roomTimeslotPairUsed, false);

    for (int i = 0; i < p.numberOfEvents; i++) {

        if (roomTimeslotPairUsed[individual[i][0]][individual[i][1]] == true) {
            violation++;
        }
        roomTimeslotPairUsed[individual[i][0]][individual[i][1]] = true;

        for (int j = i; j < p.numberOfEvents; j++) {
            if (i == j) continue;
            if (individual[i][0] != individual[j][0]) continue;
            if (eventTimeslotShare[i][j] == false) {
                violation++;
            }
        }
    }
    return violation * p.hardViolationFactor;
}

void populateTimeslotRoomEventMatrix(
        struct Params p,
        int individual[p.numberOfEvents][3],
        int timeslotRoomEventMatrix[p.numberOfTimeslots][p.numberOfRooms]
) {
    populateIntMatrix(p.numberOfTimeslots, p.numberOfRooms, timeslotRoomEventMatrix, -1);

    for (int i = 0; i < p.numberOfEvents; i++) {
        timeslotRoomEventMatrix[individual[i][0]][individual[i][1]] = i;
    }
}

int calculateRemainingBlockSize(
        struct Params p,
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int timeslotRoomEventMatrix[p.numberOfTimeslots][p.numberOfRooms],
        int timeslot,
        int room,
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int remainingBlockSize,
        bool timeslotRoomChecked[p.numberOfTimeslots][p.numberOfRooms]
) {

    int nextTimeslot = timeslotNeighborhoodFlat[timeslot][1];

    if (
            remainingBlockSize == 0
            || nextTimeslot < 0
            || eventSameSubject[timeslotRoomEventMatrix[timeslot][room]][timeslotRoomEventMatrix[nextTimeslot][room]] == false

    ) {
        return remainingBlockSize;
    }

    timeslotRoomChecked[nextTimeslot][room] = true;
    remainingBlockSize--;

    return calculateRemainingBlockSize(p,
            eventSameSubject,
            timeslotRoomEventMatrix,
            timeslot+1,
            room,
            timeslotNeighborhoodFlat,
            remainingBlockSize,
            timeslotRoomChecked
    );
}

int calculateViolation(
        struct Params p,
        int individual[p.numberOfEvents][3],
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int eventBlockSize[p.numberOfEvents],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2]
) {
    return calculateHardViolation(p, individual, eventTimeslotShare);
}

int getRoomForEvent(struct Params p, bool eventRoomFit[p.numberOfEvents][p.numberOfRooms], int event) {
    int room;
    while (1) {
        room = randInt(0, p.numberOfRooms - 1);
        if (eventRoomFit[event][room] == true) return room;
    }
}

void initializeGene(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        struct Node *eventBlock,
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int individual[p.numberOfEvents][3]
) {
    bool success = false;

    while (! success) {
        success = true;
        struct Node *node =  eventBlock;
        int room = getRoomForEvent(p, eventRoomFit, node->val);

        int timeslot = randInt(0, p.numberOfTimeslots - 1);

        individual[node->val][0] = timeslot;
        individual[node->val][1] = room;

        int lastEventInGene = node->val;

        while((node = node->next) != NULL) {
            timeslot = timeslotNeighborhoodFlat[timeslot][1];
            if (timeslot == -1) {
                success = false;
                break;
            }
            individual[node->val][0] = timeslot;
            individual[node->val][1] = room;
            lastEventInGene = node->val;
        }
        individual[lastEventInGene][2] = 1; // last gene element
    }

}

void initializeIndividual(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        struct Node *eventBlock[p.numberOfBlocks],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int individual[p.numberOfEvents][3]
) {
    for (int j = 0; j < p.numberOfBlocks; j++) {
        initializeGene(p, eventRoomFit, eventBlock[j], timeslotNeighborhoodFlat, individual);
    }
}

void initializePopulation(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        struct Node *eventBlock[p.numberOfBlocks],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int population[p.populationCardinality][p.numberOfEvents][3]
) {
    for (int i = 0; i < p.populationCardinality; i++) {
        initializeIndividual(p, eventRoomFit, eventBlock, timeslotNeighborhoodFlat, population[i]);
    }
}

int findBestIndividual(
        struct Params p,
        int population[p.populationCardinality][p.numberOfEvents][3],
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int eventBlockSize[p.numberOfEvents],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int rangeMin,
        int rangeMax
) {
    int bestIndividualIndex;
    int bestIndividualViolation = INT_MAX;

    for (int i = rangeMin; i < rangeMax; i++) {
        int violation = calculateViolation(
                p,
                population[i],
                eventTimeslotShare,
                eventSameSubject,
                eventBlockSize,
                timeslotNeighborhoodFlat

        );
        if (violation < bestIndividualViolation) {
            bestIndividualViolation = violation;
            bestIndividualIndex = i;
        }
    }

    printf("Survivor violation factor: %d\n", bestIndividualViolation);

    return bestIndividualIndex;
}

void selectSurvivors(
        struct Params p,
        int population[p.populationCardinality][p.numberOfEvents][3],
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int eventBlockSize[p.numberOfEvents],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int survivorIdexes[p.numberOfSurvivors]
) {

    for (int i = 0; i < p.numberOfSurvivors; i++) {
        survivorIdexes[i] = findBestIndividual(
                p,
                population,
                eventTimeslotShare,
                eventSameSubject,
                eventBlockSize,
                timeslotNeighborhoodFlat,
                p.broodSplit[i][0],
                p.broodSplit[i][1]
        );
    }
}

void reproduce(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        int parents[2][p.numberOfEvents][3],
        int child[p.numberOfEvents][3]
) {
    int selectedParentGene = randInt(0, 1);
    for (int i = 0; i < p.numberOfEvents; i++) {
        child[i][0] = parents[selectedParentGene][i][0];
        child[i][1] = parents[selectedParentGene][i][1];
        if (parents[selectedParentGene][i][2] == 1) selectedParentGene = randInt(0, 1);
    }

}

void mutation2 (
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        struct Node *eventBlock[p.numberOfBlocks],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        int individual[p.numberOfEvents][3]
) {
    for (int i = 0; i < p.mutation2Rate; i++) {
        int blockIndex = randInt(0, p.numberOfBlocks - 1);
        initializeGene(p, eventRoomFit, eventBlock[blockIndex], timeslotNeighborhoodFlat, individual);
    }
}

void mutate(
        struct Params p,
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        struct Node *eventBlock[p.numberOfBlocks],
        int individual[p.numberOfEvents][3]
) {
    mutation2(p, eventRoomFit, eventBlock, timeslotNeighborhoodFlat, individual);
}

void nextGeneration(
        struct Params p,
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        int survivorIdexes[p.numberOfSurvivors],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        struct Node *eventBlock[p.numberOfBlocks],
        int population[p.populationCardinality][p.numberOfEvents][3]
) {
    int parents[2][p.numberOfEvents][3];

    copyIntMatrix(p.numberOfEvents, 3, population[survivorIdexes[0]], parents[0]);
    copyIntMatrix(p.numberOfEvents, 3, population[survivorIdexes[1]], parents[1]);

    for (int i = 0; i < p.populationCardinality; i++) {
    	reproduce(p, eventRoomFit, parents, population[i]);
        mutate(p, eventRoomFit, timeslotNeighborhoodFlat, eventSameSubject, eventBlock, population[i]);
    }

}

void doEvolution(
        struct Params p,
        bool eventTimeslotShare[p.numberOfEvents][p.numberOfEvents],
        bool eventRoomFit[p.numberOfEvents][p.numberOfRooms],
        bool eventSameSubject[p.numberOfEvents][p.numberOfEvents],
        int eventBlockSize[p.numberOfEvents],
        int timeslotNeighborhoodFlat[p.numberOfTimeslots][2],
        struct Node *eventBlock[p.numberOfBlocks],
        int numberOfGenerations
) {

    int survivorIdexes[p.numberOfSurvivors];

    int population[p.populationCardinality][p.numberOfEvents][3];
    initializePopulation(p, eventRoomFit, eventBlock, timeslotNeighborhoodFlat, population);

    int lowestViolation = INT_MAX;
    int bestIndividual[p.numberOfEvents][3];

    for (int generation = 0; generation < numberOfGenerations; generation++) {

        selectSurvivors(
                p,
                population,
                eventTimeslotShare,
                eventSameSubject,
                eventBlockSize,
                timeslotNeighborhoodFlat,
                survivorIdexes
        );

        for (int j = 0; j < p.numberOfSurvivors; j++) {
            int violation = calculateViolation(
                    p,
                    population[survivorIdexes[j]],
                    eventTimeslotShare,
                    eventSameSubject,
                    eventBlockSize,
                    timeslotNeighborhoodFlat
            );
            if (violation < lowestViolation) {
                lowestViolation = violation;
                copyIntMatrix(p.numberOfEvents, 3, population[survivorIdexes[j]], bestIndividual);
                writeIntMatrixToCsvFile(p.numberOfEvents, 3, bestIndividual, CONFIGURATION_OUTPUT_DATA_PATH);
            }
        }

        printf("Generation: %d; Lowest violation: %d; Survivors indexes: %d, %d\n", generation, lowestViolation, survivorIdexes[0], survivorIdexes[1]);

        nextGeneration(p, eventTimeslotShare, eventRoomFit, survivorIdexes, timeslotNeighborhoodFlat, eventSameSubject, eventBlock, population);


    }
}
