/*
 * configuration.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#ifdef _WIN32
#define DIRECTORY_SEPARATOR "\\"
#else
#define DIRECTORY_SEPARATOR "/"
#endif

#define CONFIGURATION_LOG_MAX_ENTRY_LENGTH 1000
#define CONFIGURATION_LOG_PATH "var" DIRECTORY_SEPARATOR "log" DIRECTORY_SEPARATOR "log.log"
#define CONFIGURATION_INPUT_DATA_PATHNAME "sample" DIRECTORY_SEPARATOR "input_data"
#define CONFIGURATION_OUTPUT_DATA_PATHNAME "var" DIRECTORY_SEPARATOR "output"

#include <stdlib.h>

struct Configuration {
	char* inputDataPathname;
	char* outputDataPathname;
};

struct Configuration* Configuration(int argc, char * argv[]);


#endif /* CONFIGURATION_H_ */
