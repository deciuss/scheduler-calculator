/*
 * Encoder.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */
#include "Encoder.h"

void Encoder_writeIndividualToCsvFile(struct Individual* individual) {
	Encoder_writeIndividualToCsvFileWithName(individual, CONFIGURATION_OUTPUT_DATA_PATH);
}

void Encoder_writeIndividualToCsvFileWithName(struct Individual* individual, const char * filename) {
    FILE *fp;
    fp = fopen(filename, "w+");
    fprintf(fp, "timeslot,room");
    for (int geneIndex = 0; geneIndex < individual->numberOfGenes; geneIndex++) {
        fprintf(fp, "\n%d,%d", individual->genes[geneIndex]->timeslot, individual->genes[geneIndex]->room);
    }
    fclose(fp);
}
