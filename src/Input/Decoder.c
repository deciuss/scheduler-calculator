/*
 * Decoder.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#include "Decoder.h"

void _Decoder_assertEndOfLine(FILE *fp, int code) {
	if (fgetc(fp) != '\n') exit(code);
}

void _Decoder_assertEndOfChunk(FILE *fp, int code) {
	if (fgetc(fp) != '\n') exit(code);
}

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
}

void _Decoder_populateBoolMatrixWithFileLine(FILE *fp, int sizeX, int sizeY, bool** matrix) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            matrix[i][j] = (fgetc(fp) == '0') ? false : true;
        }
    }
    _Decoder_assertEndOfLine(fp, 222);

}

void _Decoder_populateOneToManyWithFileLines(FILE *fp, int size, struct OneToMany** eventBlocks) {
    for (int i = 0; i < size; i++) {
    	eventBlocks[i] = malloc(sizeof(struct OneToMany));
    	eventBlocks[i]->size = _Decoder_getIntFromFileLine(fp);
    	eventBlocks[i]->items = malloc(sizeof(int) * eventBlocks[i]->size);
        for (int j = 0; j < eventBlocks[i]->size; j++) {
        	eventBlocks[i]->items[j] = _Decoder_getIntFromFileLine(fp);
        }
    }
}

struct Data* Decoder_decode(const char* inputDataFilePathName) {

    FILE *fp;
    fp = fopen(inputDataFilePathName, "r");
    int numberOfEvents = _Decoder_getIntFromFileLine(fp);
    _Decoder_assertEndOfChunk(fp, 210);
    int numberOfRooms = _Decoder_getIntFromFileLine(fp);
    _Decoder_assertEndOfChunk(fp, 211);
    int numberOfTimeslots = _Decoder_getIntFromFileLine(fp);
    _Decoder_assertEndOfChunk(fp, 212);
    int numberOfGroups = _Decoder_getIntFromFileLine(fp);
    _Decoder_assertEndOfChunk(fp, 213);
    int numberOfBlocks = _Decoder_getIntFromFileLine(fp);
    _Decoder_assertEndOfChunk(fp, 214);

	struct Data* data = Data(numberOfEvents, numberOfRooms, numberOfTimeslots, numberOfBlocks, numberOfGroups);

	_Decoder_populateOneToManyWithFileLines(fp, numberOfBlocks, data->eventBlocks);
    _Decoder_assertEndOfChunk(fp, 215);
	_Decoder_populateBoolMatrixWithFileLine(fp, numberOfEvents, numberOfEvents, data->eventTimeslotShare);
    _Decoder_assertEndOfChunk(fp, 216);
	_Decoder_populateBoolMatrixWithFileLine(fp, numberOfEvents, numberOfRooms, data->eventRoomFit);
    _Decoder_assertEndOfChunk(fp, 217);
	_Decoder_populateIntArrayWithFileLines(fp, numberOfTimeslots, data->timeslotNeighborNext);
    _Decoder_assertEndOfChunk(fp, 218);
    _Decoder_populateOneToManyWithFileLines(fp, numberOfEvents, data->eventGroups);
    _Decoder_assertEndOfChunk(fp, 219);

	fclose(fp);

	return data;
}
