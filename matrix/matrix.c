#include "matrix.h"
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

//Init matrix
Matrix InitM(int w, int h)
{
	Matrix temp = {w, h, calloc(w * h, sizeof(char* ))};
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
