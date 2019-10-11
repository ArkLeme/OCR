#include "matrix.h"
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

//Init matrix
Matrix InitM(int w, int h)
{
	Matrix temp = {w, h, w * h, calloc(w * h, sizeof(int* ))};
	temp.size = w * h;
	return temp;
}

//Put element e in matrix at [i,j]
void PutM(Matrix m, int i, int j, int e)
{
	if(i < 0 || i >= m.height || j < 0 || j > m.width)
		errx(1, "Index outside of matrix i=%c, j=%c, h=%c, w=%c\n",
						i, j, m.height, m.width);
	*(m.matrix + m.height * i + j) = e;
}

//Put element e in matrix at [i/col, i%col]
void PutPosM(Matrix m, int pos, int e)
{
	if(pos < 0 || pos >= m.size)
			errx(1, "Index outside of matrix pos=%i, size=%i", pos, m.size);
	*(m.matrix + pos) = e;
}

//Get element e in matrix at [i/width, i%width]
int GetPosM(Matrix m, int pos)
{
	if(pos < 0 || pos >= m.size)
			errx(1, "Index outside of matrix pos=%i, size=%i", pos, m.size);
	return *(m.matrix + pos);
}

//Get element e in matrix at [i,j]
int GetM(Matrix m, int i, int j)
{
	if(i < 0 || i >= m.height || j < 0 || j > m.width)
		errx(1, "Index outside of matrix i=%c, j=%c, h=%c, w=%c\n",
						i, j, m.height, m. width);
	return *(m.matrix + m.height * i + j);
}

//Display Matrix
void DisplayM(Matrix m)
{
	for(int i = 0; i < m.height; i++)
	{
		printf("[ ");
		for(int j = 0; j < m.width; j++)
		{
			printf("%i ", GetM(m, i, j));
		}
		printf("]\n");
	}
}

//Free Matrix
void FreeM(Matrix m)
{
	free(m.matrix);
}

//Addition Matrix
void AddM(Matrix m1, Matrix m2)
{
	if(m1.width != m2.width || m1.height != m2.height)
			errx(1, "Matrix do not have the same dimension");
	for(int i = 0; i < m1.size; i++)
	{
		PutPosM(m1, i, GetPosM(m1, i) + GetPosM(m2, i));
	}
}

//Multiplication Matrix:
