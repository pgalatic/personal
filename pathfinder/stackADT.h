/// Stack definitions.
///
/// @author: cs.rit.edu
///
/// Edited by Paul Galatic.

#ifndef _STACKADT_H_
#define _STACKADT_H_

#include <stdbool.h>

typedef struct stackStruct {
	void **contents;
	size_t capacity;
	size_t num;
} stackStruct;

typedef struct stackStruct* StackADT;

StackADT stk_create( void );
void stk_destroy( StackADT stack );
void stk_clear( StackADT stack );
void stk_push( StackADT stack, void *data );
void *stk_pop( StackADT stack );
void *stk_top( StackADT stack );
bool stk_empty( StackADT stack );
 //added by Paul Galatic
bool stk_contains( StackADT stack, void *data );
bool stk_search( StackADT s, StackADT tar );
StackADT stk_dup( StackADT stack );
#endif
