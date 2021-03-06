/*
 * Utils.h
 *
 *  Created on: 29 kwi 2021
 *      Author: deciuss
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <stdbool.h>
#include <stdlib.h>

int Utils_getRandomInteger(int lower, int upper);
bool** Utils_constructBoolMatrix(int sizeX, int sizeY, bool defaultValue);
void Utils_destructBoolMatrix(bool** matrix, int sizeX, int sizeY);
int Utils_floor(double x);
double Utils_modf(double x);

#endif /* UTILS_H_ */
