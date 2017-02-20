/// Utility functions for b_node
///
/// @author Paul Galatic

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "node.h"
#include "stackADT.h"

#define START_SIZE 10

/// Allocates and returns a node with default state.
Node *n_init(char *line){
	char *tok = strtok(line, " ");
	int mem = START_SIZE;
	Node *new = malloc(sizeof(Node));

	new->id = strtod(tok, NULL);
	new->onPath = false;
	new->terminal = false;
	new->next = NULL;
	new->visitedFrom = stk_create();
	new->numNeighbors = 0;
	new->neighbors = malloc(mem * sizeof(int));

	tok = strtok(NULL, " ");
	while (tok != NULL){
		if (new->numNeighbors > mem){
			mem *= 2;
			new->neighbors = realloc(new->neighbors, mem * sizeof(int));
		}
		new->neighbors[new->numNeighbors] = strtod(tok, NULL);
		new->numNeighbors += 1;

		tok = strtok(NULL, " ");
	}

	return new;
}

/// Searches through a list to try and find a
/// specific Node. If it isn't present, returns
/// NULL.
Node *findNode(Node **root, int targetID){

        Node **curr = root;

        while ((*curr) != NULL){
                if ((*curr)->id == targetID){
                        return *curr;
                }
                curr = &(*curr)->next;
        }
        return NULL;

}

/// Sets the 'visited' value of all Nodes in a
/// linked list to False.
void setAllOnPathFalse(Node *root){
        Node *curr = root;

        while (curr != NULL){
                curr->onPath = false;
                curr = curr->next;
        }

}

/// Sets the 'terminal' value of all Nodes in a
/// linked list to False.
void setAllTerminalFalse(Node *root){
        Node *curr = root;

        while (curr != NULL){
                curr->terminal = false; 
		if (curr->visitedFrom != NULL){
			stk_destroy(curr->visitedFrom);
			curr->visitedFrom = NULL;
		}
		curr = curr->next;
        }

	
}

int listSize(Node *root){
	int size = 0;
	while (root != NULL){
		size++;
		root = root->next;
	}
	return size;
}

/// Frees a linked list of Nodes and marks it
/// as NULL.
void freeList(Node *root){
        Node *curr = root;
        Node *prev;

        while (curr != NULL){
                prev = curr;
                curr = curr->next;
                n_free(prev);
        }

}

/// Frees a Node.
void n_free(Node *n){
	StackADT curr;
	while (!stk_empty(n->visitedFrom)){
		curr = (StackADT)stk_pop(n->visitedFrom);
		stk_destroy(curr);
	}
	stk_destroy(n->visitedFrom);
	free(n->neighbors);
	free(n);
}
