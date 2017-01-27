/// Node for pathfinding algorithm
///
/// @author Paul Galatic

#ifndef _NODE_H_
#define _NODE_H_

#include "stackADT.h"

/// b_node
///     Designed to hold data about a particular
///     image / location at Toracon. Data is
///     slightly abstracted from what it
///     represents.
///
/// fields -
///     int id : unique node identifier
///     bool visited : whether or not this node
///             has been visited by the DFS
///             algorithm in findPossiblePathes()
///     int numNeighbors : number of neighbors
///     int *neighbors : array of neighbors of
///             the node
///	StackADT visitedFrom: a stack of Nodes 
///		that this node has been visited
///		from
///     struct Node *next : pointer to next node
///             for use in a linked list

typedef struct b_node Node;

typedef struct b_node{
        int id;
        bool onPath;
        bool terminal;
        int numNeighbors;
        int *neighbors;
        StackADT visitedFrom;
        Node *next;
} Node;

/// n_init()
/// 	Allocates and returns a Node with default 
///	state.
///
/// args - 
///	char *line - the line containing the 
///		node's neighbors
///
/// alloc - 
///	Allocates the node being changed.

Node *n_init(char *line);

/// findNode()
///	Searches through a list to try and find a
///	specific Node. If it isn't present, 
///	return NULL.
///
/// args - 
///	Node **root - handle to the root of the 
///		linked lsit
///	int targetID - id of the node being 
///		searched for
///
/// returns - 
///	The Node with id = targetID, if found, or 
///	NULL.

Node *findNode(Node **root, int targetID);

/// setAllOnPathFalse()
///	For all the Nodes in a linked list, sets
///	the OnPath value to False.
///
/// args - 
///	Node *root - pointer to the head of the
///		linked list

void setAllOnPathFalse(Node *root);

/// setAllTerminalFalse()
///	For all the Nodes in a linked list, sets
///	the Terminal value to False.
///
/// args - 
///	Node *root - pointer to the head of the 
///		linked list

void setAllTerminalFalse(Node *root);

/// freeList()
///	Frees all the nodes in a linked list.
///
/// args - 
///	Node *root - pointer to the head of the
///		linked list

void freeList(Node *root);

/// n_free()
/// Frees all dynamically allocated memory
/// of a node.
///
/// args -
/// Node n - the node to be freed
void n_free(Node *n);
#endif // NODE_H_

