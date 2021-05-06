/*
 * Encoder.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */
#include "Encoder.h"

void _Encoder_writeIndividualToCsvFile(const char* pathname, struct Individual* individual) {
    FILE *fp;
    fp = fopen(pathname, "w+");
    fprintf(fp, "timeslot,room");
    for (int geneIndex = 0; geneIndex < individual->numberOfGenes; geneIndex++) {
        fprintf(fp, "\n%d,%d", individual->genes[geneIndex]->timeslot, individual->genes[geneIndex]->room);
    }
    fclose(fp);
}

void Encoder_writeIndividualToTempCsvFile(
	struct Configuration* configuration,
	int generation,
	struct Individual* individual
) {
	char path[255] = "";
	char pathname[255] = "";

	sprintf(
		path,
		"%s%s",
		configuration->outputDataPathname,
		"_tmp"
	);

	struct stat st = {0};
	if (stat(path, &st) == -1) {
	    mkdir(path, 0755);
	}

	sprintf(
		pathname,
		"%s%sgeneration%010d_hard%010d_soft%010d",
		path,
		DIRECTORY_SEPARATOR,
		generation,
		individual->hardViolationFactor,
		individual->softViolationFactor
	);

    _Encoder_writeIndividualToCsvFile(pathname, individual);
}

void Encoder_writeIndividualToFinalCsvFile(
	struct Configuration* configuration,
	struct Individual* individual
) {
	_Encoder_writeIndividualToCsvFile(configuration->outputDataPathname, individual);
}
