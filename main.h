////////////////////////////////////////////////////////////////////////////////
// main.c
// Main header file
// Structures definition
// (c) Jan Horacek
// jan.horacek@seznam.cz
// 4.12.2014
// v1.1
// License: Apache license v 2.0
////////////////////////////////////////////////////////////////////////////////

#ifndef _H_MAIN_
#define _H_MAIN_

#define MATRIX_TYPE double

typedef struct {
	MATRIX_TYPE **data;
	int width, height;
} matrix;

void print_matrix(matrix mat);
void print_solutions(MATRIX_TYPE* sol, unsigned int len);

#endif
