////////////////////////////////////////////////////////////////////////////////
// gauss`.c
// Gauss algorithm implementation
// Gauss algorithm lib executable file
// (c) Jan Horacek
// jan.horacek@seznam.cz
// 6.11.2014
// v1.1
// License: Apache license v 2.0
////////////////////////////////////////////////////////////////////////////////

// this algorithm is inspired
//	http://www.karlin.mff.cuni.cz/~tuma/2003/NNLinalg2.pdf,
//	where complete description can be found

#include "gauss.h"

#ifdef DEBUG
	#include <stdio.h>
#endif

typedef struct {
	int row, col;
} coords;

////////////////////////////////////////////////////////////////////////////////

// find first non-zero element, starting on \start column
//  it does not exist -> return last 0 in line
// returns coordinates of the element in \result
void gfind(matrix mat, coords start, coords* result)
{
	int row, col;
	result->row = start.row;

	for (col = 0; col < mat.width; col++)
	{
		for (row = start.row; row < mat.height; row++)
		{
			if (mat.data[row][col] != 0.0)
			{
				result->col = col;
				return;
			}
		}//for row
	}// for col

	result->row = -1;
}

////////////////////////////////////////////////////////////////////////////////

// switch 2 lines
// we switch one line below \start with non-zero in the column
// step 3)
void gswitch(matrix mat, coords start)
{
	int row;
	MATRIX_TYPE* tmp;

	for (row = start.row; row < mat.height; row++)
	{
		if (mat.data[row][start.col] != 0.0)
		{
			// we have found next 0.0 element -> switch it and exit
			tmp = mat.data[start.row];
			mat.data[start.row] = mat.data[row];
			mat.data[row] = tmp;
			return;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

// change one line of matrix
// step 4)
void gchange(matrix mat, coords start)
{
	double multip;
	int row, col;

	for (row = start.row+1; row < mat.height; row++)
	{
		if (mat.data[row][start.col] == 0.0) continue;

		multip = -(mat.data[row][start.col] / mat.data[start.row][start.col]);

		mat.data[row][start.col] = 0.0;
		for (col = start.col+1; col < mat.width; col++)
			mat.data[row][col] += (mat.data[start.row][col] * multip);
	}
}

////////////////////////////////////////////////////////////////////////////////

// Gauss algorithm execution
//  return codes:
//	0 : ok
//	1 : inifinite amount of solutions
//	2 : no solution
int gsolve(matrix mat, MATRIX_TYPE* sol)
{
	coords pos, result;
	int line, col;
	MATRIX_TYPE sum;

	pos.row = pos.col = 0;

	while (pos.row < mat.height)
	{
		// 1)
		gfind(mat, pos, &result);

		#ifdef DEBUG
		printf("Pivot: %d:%d\n", result.col, result.row);
		#endif

		if (result.row < 0)
			return 1;
		pos = result;

		// 3)
		if (mat.data[pos.row][pos.col] == 0.0)
			gswitch(mat, pos);

		// 4)
		if (mat.data[pos.row][pos.col] != 0.0);
			gchange(mat, pos);

		#ifdef DEBUG
		print_matrix(mat);
		#endif

		pos.row++;
		pos.col = 0;
	}

	// does it have a solution?
	if (mat.data[mat.width-2][mat.height-1] == 0)
		return 2;

	// search for solutions
	for (line = mat.height-1; line >= 0; line--)
	{
		// count sum
		sum = 0;
		for (col = line+1; col < mat.width-1; col++)
			sum += (mat.data[line][col] * sol[col]);
		mat.data[line][mat.width-1] -= sum;
		sol[line] = (mat.data[line][mat.width-1] / mat.data[line][line]);
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////

