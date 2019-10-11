#include "matrix.h"
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

//Init matrix
Matrix InitM(int l, int c)
{
	int size = l * c;
	Matrix temp = {l, c, size, calloc(size, sizeof(int* ))};
	return temp;
}

//Put element e in matrix at [i,j]
void PutM(Matrix m, int i, int j, int e)
{
	if(i < 0 || i >= m.line || j < 0 || j > m.col)
		errx(1, "Put Index outside of matrix i=%i, j=%i, h=%i, w=%i\n",
						i, j, m.line, m.col);
	*(m.matrix + m.col * i + j) = e;
}

//Put element e in matrix at [i/col, i%col]
void PutPosM(Matrix m, int pos, int e)
{
	if(pos < 0 || pos >= m.size)
		errx(1, "Put Index outside of matrix pos=%i, size=%i\n",
						pos, m.size);
	*(m.matrix + pos) = e;
}


//Get element e in matrix at [i,j]
int GetM(Matrix m, int i, int j)
{
	if(i < 0 || i >= m.line || j < 0 || j > m.col)
		errx(1, "Get Index outside of matrix i=%i, j=%i, h=%i, w=%i\n",
						i, j, m.line, m. col);
	return *(m.matrix + m.col * i + j);
}

//Get element e in matrix at [i/col, i%col]
int GetPosM(Matrix m, int pos)
{
	if(pos < 0 || pos >= m.size)
		errx(1, "Get Index outside of matrix pos=%i, size=%i\n",
						pos, m.size);
	return *(m.matrix + pos);
}

//Display Matrix
void DisplayM(Matrix m)
{
	for(int i = 0; i < m.line; i++)
	{
		printf("[ ");
		for(int j = 0; j < m.col; j++)
		{
			printf("%i ", GetM(m, i, j));
		}
		printf("]\n");
	}
	printf("\n");
}

//Free Matrix
void FreeM(Matrix m)
{
	free(m.matrix);
}

//Addition Matrix
void AddM(Matrix m1, Matrix m2)
{
	if(m1.col != m2.col || m1.line != m2.line)
		errx(1, "Add Matrix do not have the same dimension :\
						m1w=%i, mw2=%i, m1h=%i, m2h=%i\n",
						m1.col, m2.col, m1.line, m2.line);
	for(int i = 0; i < m1.size; i++)
	{
		PutPosM(m1, i, GetPosM(m1, i) + GetPosM(m2, i));
	}
}

Matrix AddMM(Matrix m1, Matrix m2)
{
	if(m1.col != m2.col || m1.line != m2.line)
		errx(1, "Add Matrix do not have the same dimension :\
						m1w=%i, mw2=%i, m1h=%i, m2h=%i\n",
						m1.col, m2.col, m1.line, m2.line);

	Matrix m = InitM(m1.line, m2.col);
	for(int i = 0; i < m1.size; i++)
	{
		PutPosM(m, i, GetPosM(m1, i) + GetPosM(m2, i));
	}

	return m;
}

//Multiplication Matrix
Matrix MultM(Matrix m1, Matrix m2)
{
	if(m1.col != m2.line)
			errx(1, "Mul Matrix can not be multiply : m1w=%i, m2w=%i\n",
							m1.col, m2.line);

	Matrix m = InitM(m1.line, m2.col);
	for(int i = 0; i < m1.line; i++)
	{
		for(int j = 0; j < m2.col; j++)
		{
			for(int k = 0; k < m1.col; k++)
			{
				PutM(m, i, j, GetM(m, i, j) + GetM(m1, i, k) * GetM(m2, k, j));
			}
		}
	}

	return m;
}
