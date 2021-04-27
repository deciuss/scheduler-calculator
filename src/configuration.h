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

#define CONFIGURATION_INPUT_DATA_PATH "sample" DIRECTORY_SEPARATOR "input_data"
#define CONFIGURATION_OUTPUT_DATA_PATH "var" DIRECTORY_SEPARATOR  "calculator_result"

#endif /* CONFIGURATION_H_ */
