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
	struct Configuration* configuration,
	int generationNumber,
	struct Individual* currentBest,
	struct Individual* overallBest,
	double stepCurrentFactor,
	bool verbose
) {
	char* logEntry = malloc(CONFIGURATION_LOG_MAX_ENTRY_LENGTH);
	char* dateTime = _Logger_getDateTimeNowFormated();

	sprintf(
		logEntry,
		"%s scheduler-calculator progress: generation: %d; step factor: %f; current best: %d/%d; overall best: %d/%d\n",
		dateTime,
		generationNumber,
		stepCurrentFactor,
		currentBest->violation->hard,
		currentBest->violation->soft,
		overallBest->violation->hard,
		overallBest->violation->soft
	);

    FILE *fp;
    fp = fopen(configuration->logPathname, "a");
    fprintf(fp, "%s", logEntry);
    fclose(fp);

	if (verbose == true) {
		printf("%s", logEntry);
	}

	free(dateTime);
	free(logEntry);
}
