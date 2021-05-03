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
#define CONFIGURATION_INPUT_DATA_PATH "sample" DIRECTORY_SEPARATOR "input_data"
#define CONFIGURATION_OUTPUT_DATA_PATH "var" DIRECTORY_SEPARATOR "output" DIRECTORY_SEPARATOR "output.csv"


#endif /* CONFIGURATION_H_ */
