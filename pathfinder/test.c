/// Testing program for the functions in 
/// board-builder.c.
///
/// @author Paul Galatic

#include <stdlib.h>
#include <stdio.h>
#include "stackADT.h" //cs.rit.edu
#include "node.h"
#include "path-finder.h"

void stk_print(StackADT s);

/// TESTING

void test_board_printing(void);
void test_linked_list(void);
void test_path_finding(void);
void test_stack_addons(void);
void test_node(void);

/// UTILITY

void print_list(Node *root);

/// the "training grounds"
///
/// No code should be here except function calls.
int main(void){
	//test_node();			FIXME strtok() breaks
	//test_stack_addons();	FIXME strtok() breaks
	//test_linked_list();
	test_path_finding();

}

/// Tests path finding functionality. Requires
/// a test file to be redirected into main.
/// 1:	Builds all linked lists into a graph.
/// 2:	Searches for all possible paths through
///	the graph.
/// 3:	Prints all the paths.
/// 4:	Destroys the stacks involved.
void test_path_finding(void){
	printf("\nTESTING PATH FINDING:\n");

	FILE *fp = stdin;

	Node *root = parseNodeList(fp);
	print_list(root);

	unsigned int size = (unsigned int)listSize(root);
	StackADT allPaths;
	for (unsigned int x = 1; x < size + 1; x++){
		printf("---PATHS OF LEGNTH: %u---\n", x);
		allPaths = findAllPaths(root, x);
		stk_destroy(allPaths);
	}
	
	freeList(root);
}

/// Tests linked list functionality. Requires a 
/// test file to be redirected into main. 
/// 1:	Traverses the list and prints the IDs and 
///	neighbors 
/// 2:	Searches for specific predefined Nodes
/// 3:	Frees the list
void test_linked_list(void){
	printf("\nTESTING LINKED LIST:\n");

	FILE *fp = stdin;
	
	Node *root = parseNodeList(fp);
	print_list(root);

	Node *ptr;
	int lostNode_1 = 3;
	int lostNode_2 = 50;

	ptr = findNode(&root, lostNode_1);
	if (ptr != NULL){
		printf("findNode() has located lostNode_1! ID: %d\n", ptr->id);
	}else{
		printf("findNode() could not locate lostNode_1! ID: %d\n", lostNode_1);
	}

	ptr = findNode(&root, lostNode_2);
	if (ptr != NULL){
		printf("findNode() has located lostNode_2! ID: %d\n", ptr->id);
	}else{
		printf("findNode() could not locate lostNode_2! ID: %d\n", lostNode_2);
	}

	freeList(root);

	printf("\nDONE.");
}

/// Tests stk_contains(), stk_print(), and 
/// stk_search().
void test_stack_addons(void){
	StackADT s = stk_create();

	Node *n = n_init("1");

	stk_push(s, n);

	if (stk_contains(s, n)){
		printf("stk_contains(): SUCCESS\n");
	}else{
		printf("stk_contains(): FAILURE\n");
	}

	StackADT d = stk_dup(s);

	printf("ORIGINAL ");
	stk_print(s);
	printf("DUPLICATED ");
	stk_print(d);

	StackADT a = stk_create();
	StackADT a2 = stk_create();
	Node *aa = n_init("1");
	stk_push(a, aa);
	stk_push(a2, aa);
	StackADT b = stk_create();
	Node *bb = n_init("2");
	stk_push(b, bb);
	StackADT c = stk_create();
	StackADT c2 = stk_create();
	stk_push(c, aa);
	stk_push(c2, aa);

	StackADT tot = stk_create();
	stk_push(tot, a);
	stk_push(tot, c);

	printf("stk_search() tot-->[a][aa];[c][aa] and [b][bb]: ");
	if (stk_search(tot, b)){
		printf("TRUE\n");
	}else{
		printf("FALSE\n");
	}

	printf("stk_search() tot-->[a][aa];[c][aa] and [c2][aa]: ");
	if (stk_search(tot, c2)){
		printf("TRUE\n");
	}else{
		printf("FALSE\n");
	}

	StackADT e = stk_create();
	StackADT e2 = stk_create();
	Node *ee = n_init("3");
	stk_push(e, ee);
	stk_push(e2, ee);
	stk_push(tot, e);

	printf("stk_search() tot-->[a][aa];[c][aa];[e][ee] and [a2][aa]: ");
	if (stk_search(tot, a2)){
		printf("TRUE\n");
	}else{
		printf("FALSE\n");
	}

	printf("stk_search() tot-->[a][aa];[c][aa];[e][ee] and [e2][ee]: ");
	if (stk_search(tot, e2)){
		printf("TRUE\n");
	}else{
		printf("FALSE\n");
	}
	
	stk_destroy(tot);
	stk_destroy(s);
	stk_destroy(d);
	stk_destroy(a);
	stk_destroy(b);
	stk_destroy(c);
	stk_destroy(a2);
	stk_destroy(c2);
	stk_destroy(e2);
	free(aa);
	free(bb);
	free(ee);
	free(n);
}

/// Tests node functionality.
void test_node(void){
	Node *n1 = n_init("1");
	Node *n2 = n_init("2");

	n1->next = n2;

	print_list(n1);

	freeList(n1);
}

/// Prints out a list for debugging purposes.
void print_list(Node *root){
	Node *curr = root;
	
	while (curr != NULL){
		printf("N%d:\t", curr->id);
		if (curr->numNeighbors > 0){
			printf("%d ", curr->neighbors[0]);
			for (int x = 1; x < curr->numNeighbors; x++){	
				printf("| %d ", curr->neighbors[x]);
			}
		}
		
		printf("\n");
		curr = curr->next;
	}
}
