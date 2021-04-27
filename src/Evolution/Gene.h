/*
 * Gene.h
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */

#ifndef GENE_H_
#define GENE_H_
#include <stdbool.h>
#include <stdlib.h>

struct Gene {
    unsigned int timeslot;
    unsigned int room;
    bool isLastBlock;
};

struct Gene* Gene(int timeslot, int room);
void Gene_destruct(struct Gene * gene);

#endif /* GENE_H_ */
