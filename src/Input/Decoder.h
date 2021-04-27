/*
 * Decoder.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef INPUT_DECODER_H_
#define INPUT_DECODER_H_
#include <stdio.h>
#include "Data.h"
#include "EventBlock.h"

struct Data* Decoder_decode(const char * inputDataFilePathName);

#endif /* INPUT_DECODER_H_ */
