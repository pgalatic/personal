/// Program for automatically assembling Tora-Con
/// Quest game boards for use at Tora-Con.
///
/// @author Paul Galatic

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stackADT.h" // cs.rit.edu
#include "node.h"
#include "path-finder.h"

#define HLINE "--------------------------\n"
#define VLINE "|"

void stk_print(StackADT s);

/// Takes lines one at a time from an input file
/// and assembles a linked list of Nodes with
/// neighbors. None of the nighbors should have 
/// the value 0. Returns the root node.
///
/// Proper file format:
///	NODE_ID [NEIGHBOR1] [NEIGHBOR2] [...]
///
/// Examples:
///	2 21 34 4 29
///	4 5
///	28
Node *parseNodeList(FILE *fp){
	Node *root;
	Node **curr = &root;
	
	char *buf = NULL;
	size_t len = 0;
	
	while ((getline(&buf, &len, fp)) > 0){
		*curr = n_init(buf);
		curr = &(*curr)->next;
	}

	return root;

}

/// Traverses the list of nodes and determines
/// all possible paths of SIZE, based on the
/// Neighbors array of each Node. Includes
/// paths that have a free space in the middle.
StackADT findAllPaths(Node *root, const unsigned int SIZE){
	Node *curr = root;
	StackADT allPaths = stk_create();

	while (curr != NULL){
		if (curr->numNeighbors < 1) { continue; }
		
		StackADT stack = stk_create();
		StackADT path = stk_create();
		Node *start = &(*curr);		
		Node *ptr;
		Node *val;
		stk_push(stack, start);
		do {
			ptr = stk_pop(stack);
			if (ptr->onPath){
				stk_pop(path);
				ptr->onPath = false;
				continue;
			}
			if (path->num == SIZE){
				continue;
			}
			if (path->num == SIZE - 1){
				stk_push(path, ptr);
				if (!(stk_empty(ptr->visitedFrom))){
					if (stk_search(ptr->visitedFrom, path)){
						stk_pop(path);
						continue;
					}
				}
				stk_push(ptr->visitedFrom, stk_dup(path));
				stk_print(path);
				stk_push(allPaths, path);

				ptr->onPath = true;
				stk_push(stack, ptr);
				continue;
			}
			ptr->onPath = true;
			stk_push(stack, ptr);
			for (int x = 0; x < ptr->numNeighbors; x++){
				val = findNode(&root, ptr->neighbors[x]);
				if (val == NULL){ continue; }
				if (!val->onPath){
					stk_push(stack, val);
				}
			}
			stk_push(path, ptr);

		} while (!stk_empty(stack));
		
		stk_destroy(stack);
		stk_destroy(path);
//printf("SWITCHING TO %d!\n", curr->id + 1);
		curr = curr->next;

	}
	
	return allPaths;
				
}

//TODO
void stk_print(StackADT stack){
	printf("STACK: ");
	if (stack == NULL){
		printf("NULL!");
	}else{
		for (unsigned int x = 0; x < stack->num; x++){
			Node *N = stack->contents[x];
			printf("%d", N->id);
/*
			if (N->onPath){
				printf("*");
			}
			if (N->terminal){
				printf("T");
			}
*/
			printf(" ; ");
		}
	}
	printf("\n");
}

