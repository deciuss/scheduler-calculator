/*
 * Decoder.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#include "Decoder.h"

int _Decoder_getIntFromFileLine(FILE *fp) {
    char buff[255];
    fgets(buff, 255, (FILE*)fp);
    return atoi(buff);
}

void _Decoder_populateIntArrayWithFileLines(FILE *fp, int size, int* array) {
    for (int i = 0; i < size; i++) {
        char buff[255];
        fgets(buff, 255, (FILE*)fp);
    	array[i] = atoi(buff);
    }
    if (fgetc(fp) != '\n') exit(221);
}

void _Decoder_populateBoolMatrixWithFileLine(FILE *fp, int sizeX, int sizeY, bool** matrix) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            matrix[i][j] = (fgetc(fp) == '0') ? false : true;
        }
    }
    if (fgetc(fp) != '\n') exit(222);

}

void _Decoder_populateEventBlocksArrayWithFileLines(FILE *fp, int size, struct EventBlock** eventBlocks) {
    for (int i = 0; i < size; i++) {
    	eventBlocks[i] = malloc(sizeof(struct EventBlock));
    	eventBlocks[i]->size = _Decoder_getIntFromFileLine(fp);
    	eventBlocks[i]->events = malloc(sizeof(int) * eventBlocks[i]->size);
        for (int j = 0; j < eventBlocks[i]->size; j++) {
        	eventBlocks[i]->events[j] = _Decoder_getIntFromFileLine(fp);
        }
    }
    if (fgetc(fp) != '\n') exit(223);
}

struct Data* Decoder_decode(const char* inputDataFilePathName) {

    FILE *fp;
    fp = fopen(inputDataFilePathName, "r");
    int numberOfEvents = _Decoder_getIntFromFileLine(fp);
    int numberOfRooms = _Decoder_getIntFromFileLine(fp);
    int numberOfTimeslots = _Decoder_getIntFromFileLine(fp);
    int numberOfGroups = _Decoder_getIntFromFileLine(fp);
    int numberOfBlocks = _Decoder_getIntFromFileLine(fp);

	struct Data* data = Data(numberOfEvents, numberOfRooms, numberOfTimeslots, numberOfBlocks, numberOfGroups);

	_Decoder_populateEventBlocksArrayWithFileLines(fp, numberOfBlocks, data->eventBlocks);
	_Decoder_populateBoolMatrixWithFileLine(fp, numberOfEvents, numberOfEvents, data->eventTimeslotShare);
	_Decoder_populateBoolMatrixWithFileLine(fp, numberOfEvents, numberOfRooms, data->eventRoomFit);
	_Decoder_populateIntArrayWithFileLines(fp, numberOfTimeslots, data->timeslotNeighborNext);
	_Decoder_populateIntArrayWithFileLines(fp, numberOfEvents, data->eventGroup);


	fclose(fp);

	return data;
}
