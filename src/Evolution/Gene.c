/*
 * Gene.c
 *
 *  Created on: 27 kwi 2021
 *      Author: deciuss
 */
#include "Gene.h"

struct Gene* Gene(int timeslot, int room) {
    struct Gene * gene = malloc(sizeof(struct Gene));
    gene->timeslot = timeslot;
    gene->room = room;
    return gene;

}

void Gene_destruct(struct Gene * gene) {
    free(gene);
}

struct Gene* Gene_clone(struct Gene * original) {
	struct Gene* clone = Gene(original->timeslot, original->room);
	clone->isLastBlock = original->isLastBlock;
	return clone;
}
