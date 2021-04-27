/*
 * Node.h
 *
 *  Created on: 26 kwi 2021
 *      Author: sbak
 */


#ifndef NODE_H
#define NODE_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node{
	int val;
	struct Node *next;
};

struct Node* Node_getNextNode(struct Node *node);
struct Node* Node_getLasNode(struct Node *node);
void Node_add(struct Node *node, int val);
struct Node** Node_addOrCreate(struct Node** node, int val);
void Node_deleteWithAllLinks(struct Node *node);
bool Node_containsValue(struct Node *node, int val);

#endif

