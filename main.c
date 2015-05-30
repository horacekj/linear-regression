////////////////////////////////////////////////////////////////////////////////
// main.c
// Linear regresion algorithm
// main executable file
// (c) Jan Horacek
// jan.horacek@seznam.cz
// 19.02.2015
// v1.0
// license: Apache License v2.0
////////////////////////////////////////////////////////////////////////////////

// program input: lines X Y on stdin (X and Y can be float) representing data
// program outut: one line A B, where A and B are line coeficients y = ax + b

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "gauss.h"

////////////////////////////////////////////////////////////////////////////////
// malloc gauss matrix

int init_matrix(matrix* mat, MATRIX_TYPE def)
{
	int row, col;
	if (!(mat->data = malloc(sizeof(MATRIX_TYPE*) * mat->height))) return 1;
	for (row = 0; row < mat->height; row++)
	{
		if (!(mat->data[row] = malloc(sizeof(MATRIX_TYPE) * mat->width))) return 2;
		for (col = 0; col < mat->width; col++)
			mat->data[row][col] = def;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// destroy gauss matrix

void free_matrix(matrix* mat)
{
	// second if is here because of possible insufficinet memory when mallocing
	for (int row=0; (row < mat->height) && (mat->data[row]); row++)
		free(mat->data[row]);
	free(mat->data);
}

////////////////////////////////////////////////////////////////////////////////
// main

int main(int argc, char* argv[])
{
	double x, y;
	double* solutions;
	int ret;
	matrix mat;

	mat.width  = 3;
	mat.height = 2;
	solutions = malloc(sizeof(double) * mat.height);

	// coefecients for gauss matrix:
	// (x_1^2 + x_2^2 + ... x_n^2)  | x_1 + x_2 + ... x_n | x_1 * y_1 + x_2 * y_2 + ... + x_n * y_n
	// x_1 + x_2 + ... + x_n        | n                   | y_1 + y_2 + ... y_n

	// init matrix for gauss:
	if (init_matrix(&mat, 0.0) > 0)
	{
		fprintf(stderr, "Cannot malloc\n");
		ret = 50;
		goto clean;
	}

	// parse data:
	int cnt;
	for (cnt = 0; (scanf("%lf %lf", &x, &y) == 2); cnt++)
	{
		mat.data[0][0] += x*x;
		mat.data[0][1] += x;
		mat.data[0][2] += x*y;
		mat.data[1][2] += y;
	}
	mat.data[1][1] = cnt;
	mat.data[1][0] = mat.data[0][1];

	// solve via gauss method:
	ret = gsolve(mat, solutions);
	if (ret > 0)
	{
		fprintf(stderr, "Gauss returned error %d\n", ret);
		goto clean;
	}
	printf("%f %f\n", solutions[0], solutions[1]);

clean:
	free_matrix(&mat);
	free(solutions);

	return ret;
}

