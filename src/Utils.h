/*
 * Utils.h
 *
 *  Created on: 29 kwi 2021
 *      Author: deciuss
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <stdbool.h>

int Utils_getRandomInteger(int lower, int upper);
bool** Utils_constructBoolMatrix(int sizeX, int sizeY, bool defaultValue);

void Utils_destructBoolMatrix(bool** matrix, int sizeX, int sizeY);

#endif /* UTILS_H_ */
