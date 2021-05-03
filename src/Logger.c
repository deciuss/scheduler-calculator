/*
 * Logger.c
 *
 *  Created on: 3 maj 2021
 *      Author: deciuss
 */
#include "Logger.h"

char* _Logger_getDateTimeNowFormated() {
	char format[] = "[%Y-%m-%d %H:%M:%S]";
	int formatSize = sizeof("[2021-05-03 17:51:53]");
	char* buffer = malloc(formatSize);
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime(buffer, formatSize, format, timeinfo);
	return buffer;
}

void Logger_logProgress(
	int generationNumber,
	struct Individual* currentBest,
	struct Individual* overallBest,
	bool verbose
) {
	char* logEntry = malloc(CONFIGURATION_LOG_MAX_ENTRY_LENGTH);
	char* dateTime = _Logger_getDateTimeNowFormated();

	sprintf(
		logEntry,
		"%s Progress: generation: %d; current best: %d/%d; overall best: %d/%d\n",
		dateTime,
		generationNumber,
		currentBest->hardViolationFactor,
		currentBest->softViolationFactor,
		overallBest->hardViolationFactor,
		overallBest->softViolationFactor
	);

    FILE *fp;
    fp = fopen(CONFIGURATION_LOG_PATH, "a");
    fprintf(fp, "%s", logEntry);
    fclose(fp);

	if (verbose == true) {
		printf("%s", logEntry);
	}

	free(dateTime);
	free(logEntry);
}
