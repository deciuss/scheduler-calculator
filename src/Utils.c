/*
 * Utils.c
 *
 *  Created on: 29 kwi 2021
 *      Author: deciuss
 */
#include "Utils.h"

int Utils_getRandomInteger(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

bool** Utils_constructBoolMatrix(int sizeX, int sizeY, bool defaultValue) {
	bool** matrix = malloc(sizeof(bool *) * sizeX);
	for (int i = 0; i < sizeX; i++) {
		matrix[i] = malloc(sizeof(bool) * sizeY);
		for (int j = 0; j < sizeY; j++) {
			matrix[i][j] = defaultValue;
		}
	}
	return matrix;
}

void Utils_destructBoolMatrix(bool** matrix, int sizeX, int sizeY) {
	for (int i = 0; i < sizeX; i++) {
		free(matrix[i]);
	}
	free(matrix);
}
