#include <stdlib.h>
#include "separate_matrix.h"
#include <err.h>

/**
 * \file separate_matrix.c
 * \brief This files contains all function to separate one matrix into a List
 * of matrix.
 * \author William.G
 */

/**
 * \fn PosM** FindPosMat(Matrix *m, int maxLabel)
 * \brief Find the 4 coordinates of every component in a matrix
 *
 * \param m : Matrix
 * \param maxLabel : number of label in the matrix
 *
 * \return List of pointer of the PosM structure
 */
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

	return posM;
}

/**
 * \fn List* ListOfMat(Matrix *m, PosM **p, int maxLabel)
 * \brief Create a List of Matrix from a single labeled Matrix
 *
 * \param m : Matrix
 * \param p : List of pointer of position structure
 * \param maxLabel : number of label in the matrix
 *
 * \return List of Matrix and their position
 */
List* ListOfMat(Matrix *m, PosM **p, int maxLabel)
{

	//Create the list so we can return it
	List *l = NULL;
    List **first = &l;

	for(int i = 0; i < maxLabel; i++)
	{
		if(p[i] -> mx != -1)
		{
			//Value of our matrix
			int mx = p[i] -> mx;
			int my = p[i] -> my;
			int Mx = p[i] -> Mx;
			int My = p[i] -> My;

			//Create the matrix and prepend it to the list
			Matrix *mat = CopyMatrix(m, mx, my, Mx, My);
			l = AppendL(l, mat, p[i]);
		}
		else
		{
			errx(1, "index = %i", i);
		}
	}

    free(p);

	return RemoveFL(*first);
}
