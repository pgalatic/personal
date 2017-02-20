/// Path-finder definitions
///
/// @author Paul Galatic

#ifndef _PATH_FINDER_H_
#define _PATH_FINDER_H_

#define MAX_SOLUTIONS 2
#define BOARD_SIZE 5

/// FUNCTIONS

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
///
/// args - 
///		The file to read from.
///
/// returns - 
///		The root node of the list.

Node *parseNodeList(FILE *fp);

/// findAllPaths()
/// 	Traverses the list of nodes and determines
/// 	all possible (non-looping) paths, based on 
/// 	the Neighbors array of each Node.
///
/// args - 
///		Node *root - pointer to the root of the
///		linked list of nodes
///
/// returns - 
///		A 2D array populated with a list of 
///		paths.

StackADT findAllPaths(Node *root, int NUMNODES);


#endif // PATH_FINDER_H
