/// @author : cs.rit.edu
///
/// Edited by Paul Galatic

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "stackADT.h"

#define	STACK_ALLOC_UNIT	5

StackADT stk_create( void ) {
	StackADT new;

	new = (StackADT) malloc( sizeof(struct stackStruct) );
	if( new != 0 ) {
		new->contents = 0;
		new->capacity = 0;
		new->num = 0;
	}

	return( new );
}

void stk_destroy( StackADT stack ) {
	assert( stack != 0 );

	if( stack->contents != 0 ) {
		free( stack->contents );
	}

	free( stack );
}

void stk_clear( StackADT stack ) {
	if( stack->contents != 0 ) {
		free( stack->contents );
		stack->contents = 0;
	}
	stack->capacity = 0;
	stack->num = 0;
}

void stk_push( StackADT stack, void *data ) {

	if( stack->contents == 0 ) {
		stack->contents = malloc( sizeof(void *) * STACK_ALLOC_UNIT );
		assert( stack->contents != 0 );
		stack->capacity = STACK_ALLOC_UNIT;
	}
	if( stack->num >= stack->capacity ) {
		void *tmp;
		tmp = realloc( stack->contents,
			sizeof(void *) * (stack->capacity + STACK_ALLOC_UNIT) );
		assert( tmp != 0 );
		stack->contents = tmp;
		stack->capacity += STACK_ALLOC_UNIT;
	}

	stack->contents[stack->num] = data;
	stack->num += 1;
}

void *stk_pop( StackADT stack ) {
	int n;
	void *data;

	assert( stack->num > 0 );

	n = stack->num -= 1;
	data = stack->contents[n];

	return( data );
}

void *stk_top( StackADT stack ) {
	int n;
	void *data;

	assert( stack->num > 0 );

	n = stack->num - 1;
	data = stack->contents[n];

	return( data );
}

bool stk_empty( StackADT stack ) {
	return( stack->num == 0 );
}

/// added by Paul Galatic
 
/// Determines if a particular piece of data is
/// in the Stack based on its MEMORY ADDRESS. 
/// This is a bit of cheating, as the stack is 
/// supposed to contain 'obfuscated' values, 
/// but... shh!
bool stk_contains( StackADT stack, void *data ){
	for (unsigned int x = 0; x < stack->num; x++){
		if (stack->contents[x] == data){
			return true;
		}
	}
	return false;
}

/// Searches one stack to see if it holds 
/// another, identical stack.
///
/// s is assumed to be a stack of stacks.
bool stk_search( StackADT s, StackADT tar ){
	bool foundIt = false;
	bool skip = false;
	StackADT v = stk_dup(s);
	StackADT c;
	while (!stk_empty(v) && !foundIt){
		c = (StackADT)stk_pop(v);
		if (c->num != tar->num){continue;}
		for (unsigned int x = 0; x < c->num; x++){
			if ( c->contents[x] != tar->contents[x] ){
				skip = true;
				break;
			}
		}
		if (skip){skip = false; continue;}
		foundIt = true;
	}
	stk_destroy(v);

	return foundIt;
}

/// Duplicates a stack.

StackADT stk_dup( StackADT stack ){
	StackADT new = stk_create();
	for (unsigned int x = 0; x < stack->num; x++){
		stk_push(new, stack->contents[x]);
	}
	return new;
}
