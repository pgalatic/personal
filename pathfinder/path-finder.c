/// Program for algorithmically determining all 
/// finite-length paths in a graph. Designed for 
/// undirected graphs, but will also work for 
/// directed graphs (nodes are constructed based
/// on user input).
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
/// neighbors. Returns the root node.
///
/// Proper line format for file:
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
/// all possible paths of length SIZE, based on 
/// the Neighbors array of each Node. Includes
/// paths that have a free space in the middle.
StackADT findAllPaths(Node *root, const int SIZE){
	Node *curr = root;
	StackADT allPaths = stk_create();

	while (curr != NULL){
		if (curr->numNeighbors < 1) { continue; } //skip unconnected nodes
		
		StackADT stack = stk_create();	//Keeps a record of the total node stack.
		StackADT path = stk_create(); 	//Keeps a record of the current path.
		Node *start = &(*curr);		
		Node *ptr;
		Node *val;
		stk_push(stack, start); //Start recursive DFS
		do {
			ptr = stk_pop(stack); 	//Looking at current node.
			if (ptr->onPath){		//If it's on the path, we're backtracking.
				stk_pop(path);		//So, get it off the path and go on.
				ptr->onPath = false;
				continue;
			}
			if (path->num == SIZE){ //Ignore paths longer than SIZE.
				continue;
			}
			if (path->num == SIZE - 1){ 				//If the path is almost at the size cap:
				stk_push(path, ptr);					//Check to make sure this node hasn't been
				if (!(stk_empty(ptr->visitedFrom))){	//visited from here before.
					if (stk_search(ptr->visitedFrom, path)){
						stk_pop(path);	//If we have, skip it and go on.
						continue;
					}
				}
				stk_push(ptr->visitedFrom, stk_dup(path)); //Otherwise, we found
				stk_print(path);			//a solution! Now, print it out and
				stk_push(allPaths, path);	//add it to the stack that'll return.

				ptr->onPath = true;			//Make sure it's on the path, then
				stk_push(stack, ptr);		//continue.
				continue;
			}
			ptr->onPath = true;
			stk_push(stack, ptr);				//A solution wasn't found, but this
			for (int x = 0; x < ptr->numNeighbors; x++){	//might just be the start
				val = findNode(&root, ptr->neighbors[x]);	//of a path. So, add it
				if (val == NULL){ continue; }	//to the path and then add all the
				if (!val->onPath){				//necessary branches to the DFS tree,
					stk_push(stack, val);		//as long as they're not already on
				}								//the path. No looping allowed.
			}
			stk_push(path, ptr);				//Add the current node to the stack
												//last. If we reach it, we're backtracking.
		} while (!stk_empty(stack));
		
		stk_destroy(stack);		//Free dynamically allocated memory.
		stk_destroy(path);
printf("SWITCHING TO %d!\n", curr->id + 1);
		curr = curr->next;

	}
	
	return allPaths;
				
}

///Prints out the contents of a stack.
void stk_print(StackADT stack){
	printf("STACK: ");
	if (stack == NULL){
		printf("NULL!");
	}else{
		for (unsigned int x = 0; x < stack->num; x++){
			Node *N = stack->contents[x];
			printf("%d", N->id);
			printf(" ; ");
		}
	}
	printf("\n");
}

