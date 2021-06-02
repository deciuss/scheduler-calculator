/*
 * Logger.c
 *
 *  Created on: 3 maj 2021
 *      Author: deciuss
 */
#include "Logger.h"

char* _Logger_getDateTimeNowFormated() {
	char format[] = "%Y-%m-%d %H:%M:%S";
	int formatSize = sizeof("2021-05-03 17:51:53");
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
	char* report = malloc(CONFIGURATION_LOG_MAX_ENTRY_LENGTH);
	char* dateTime = _Logger_getDateTimeNowFormated();

	sprintf(
		logEntry,
		"[%s] scheduler-calculator progress: generation: %d; step factor: %f; current best: %d/%d; overall best: %d/%d\n",
		dateTime,
		generationNumber,
		stepCurrentFactor,
		currentBest->violation->hard,
		currentBest->violation->soft,
		overallBest->violation->hard,
		overallBest->violation->soft
	);

    FILE *logFile;
    logFile = fopen(configuration->logPathname, "a");
    fprintf(logFile, "%s", logEntry);
    fclose(logFile);

	sprintf(
		report,
		"date_time,generation_number,step_current_factor,current_best_hard,current_best_soft,overall_best_hard,overall_best_soft\n%s,%d,%f,%d,%d,%d,%d",
		dateTime,
		generationNumber,
		stepCurrentFactor,
		currentBest->violation->hard,
		currentBest->violation->soft,
		overallBest->violation->hard,
		overallBest->violation->soft
	);

    FILE *reportFile;
    reportFile = fopen(configuration->reportPathname, "w");
    fprintf(reportFile, "%s", report);
    fclose(reportFile);


	if (verbose == true) {
		printf("%s", logEntry);
	}

	free(dateTime);
	free(logEntry);
	free(report);
}
