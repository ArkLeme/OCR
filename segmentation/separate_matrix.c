#include <stdlib.h>
#include "../matrix/matrix.h"
#include "separate_matrix.h"

//Find all the position of all component of our matrix
PosM** FindPosMat(Matrix *m, int maxLabel)
{
	//Create a pointeur to our list of pos
	PosM **posM = malloc(maxLabel * sizeof(PosM*));

	//Set their pos to -1
	for(int i = 0; i < maxLabel; i++)
	{
		posM[i] = InitP(-1, -1, -1, -1);
	}

	for(int i = 0; i < m -> line; i++)
	{
		for(int j = 0; j < m -> col; j++)
		{
			int label = (int) GetM(m, i, j);
			//If the pixel is not white (background)
			if(label != 0)
			{
				//If he is not initialized, initiate it
				PosM *p = posM[label];
				if(p -> mx < 0)
				{
					p -> mx = j;
					p -> Mx = j;
					p -> my = i;
					p -> My = i;
				}
				else
				{
					//Set his maximal and minimal x and y
					if(p -> mx > j)
						p -> mx = j;
					if(p -> Mx < j)
						p -> Mx = j;
					if(p -> my > i)
						p -> my = i;
					if(p -> My < i)
						p -> My = i;
				}
			}
		}
	}

	return posM;
}

//Create a list of our matrix and their position
List* ListOfMat(Matrix *m, PosM **p, int maxLabel)
{

	//Create the list so we can return it
	List *l = NULL;

	for(int i = 0; i < maxLabel; i++)
	{
		//Value of our matrix
		int mx = p[i] -> mx;
		int my = p[i] -> my;
		int Mx = p[i] -> Mx;
		int My = p[i] -> My;

		//Create the matrix and prepend it to the list
		Matrix *mat = CopyMatrix(m, mx, my, Mx, My);
		l = PrependL(l, mat, p[i]);

		}
	}

	return l;
}
