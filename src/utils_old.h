/*
 * utils.h
 *
 *  Created on: 26 kwi 2021
 *      Author: sbak
 */

#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void populateBoolMatrix(int sizeX, int sizeY, bool matrix[sizeX][sizeY], bool value);
void populateIntMatrix(int sizeX, int sizeY, int matrix[sizeX][sizeY], bool value);
void writeIntMatrixToCsvFile(int sizeX, int sizeY, int matrix[sizeX][sizeY], const char * filename);

#endif
