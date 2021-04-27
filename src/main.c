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
#include "evolution.h"
#include "Params.h"
#include "utils.h"
#include "Node.h"
#include "configuration.h"
#include "Input/Data.h"
#include "Input/Decoder.h"

int main(int argc, char * argv[]) {




	struct Data* data = Decoder_decode(CONFIGURATION_INPUT_DATA_PATH);




//    srand(time(0));
//
//    FILE *fp;
//    fp = fopen(CONFIGURATION_INPUT_DATA_PATH, "r");
//
//    struct Params p;
//    p.numberOfEvents = getIntFromFileLine(fp);
//    p.numberOfRooms = getIntFromFileLine(fp);
//    p.numberOfTimeslots = getIntFromFileLine(fp);
//    p.numberOfSurvivors = 2;
//    p.maxBlockSize = 9;
//    p.hardViolationFactor = 1;
//    p.mutation1Rate = 0;
//    p.mutation2Rate = 1;
//    p.mutation3Rate = 0;
//    p.populationCardinality = 100;
//    p.broodSplit[0][0] = 0;
//    p.broodSplit[0][1] = p.populationCardinality / 2 - 1;
//    p.broodSplit[1][0] = p.populationCardinality / 2;
//    p.broodSplit[1][1] = p.populationCardinality;



//    doEvolution(
//            p,
//            eventTimeslotShare,
//            eventRoomFit,
//            eventSameSubject,
//            eventBlockSize,
//            timeslotNeighborhoodFlat,
//            eventBlock,
//            100000000
//    );

    return 0;
}
