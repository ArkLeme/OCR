#include "rlsa.h"
#include <stdio.h>
#include "../matrix/matrix_image.h"

/**
 * \file rlsa.c
 * \brief This files containes all the function to apply the rlsa algorithm
 * \author William.G
 */

/**
 * \fn Matrix *Hrlsa(Matrix *m, int limit)
 * \brief Apply rlsa horizontaly, limit is the treshold, if the treshold is 0
 * it return a new matrix without any modification.
 *
 * \param m : The matrix
 * \param limit : threshold of white pixel tolerance
 *
 * \return New  matrix
 */
Matrix *Hrlsa(Matrix *m, int limit)
{
    if(limit == 0)
        return CopyMatrix(m, 0, 0, m->col - 1, m->line - 1);

    Matrix* output = InitM(m -> line, m -> col);
	int zero_count = 0; //Number of 0 aside

	for(int i = 0; i < m -> line; i++)
	{
		//Reset the number of 0 found on a line
		zero_count = 0;
		for(int j = 0; j < m -> col; j++)
		{
			//If the pixel is black
			if(GetM(m, i, j))
			{
                PutM(output, i, j, 1);
				//If the number of 0 is suffisant
				if(zero_count <= limit)
				{
					//Replace them by black pixel
					for(int k = zero_count; k > 0; k--)
					{
						PutM(output, i, j - k, 1);
					}
				}
				//Reset the number of zero
				zero_count = 0;
			}
			else
			{
				zero_count++;
			}
		}
	}

return output;
}

/**
 * \fn Matrix *Vrlsa(Matrix *m, int limit)
 * \brief Apply the rlsa vertically, limit is the treshold, if the treshold is
 * 0 it return a new matrix without any modification.
 *
 * \param m : The matrix
 * \param limit : threshold of white pixel tolerance
 *
 * \return New  matrix
 */
Matrix *Vrlsa(Matrix *m, int limit)
{
    if(limit == 0)
	{
        return CopyMatrix(m, 0, 0, m->col - 1, m->line - 1);
	}
	Matrix *output = InitM(m -> line, m -> col);
	int zero_count = 0; //Number of 0 aside

	for(int j = 0; j < m -> col; j++)
	{
	    //Reset the number of zero found of the col
		zero_count = 0;
		for(int i = 0; i < m -> line; i++)
		{
			//If the pixel is black
			if(GetM(m, i, j) == 1)
			{
                PutM(output, i, j, 1);
				//if the number of zero is suffisant
				if(zero_count <= limit)
				{
					//Replace them by black pixel
					for(int k = zero_count; k > 0; k--)
					{
						PutM(output, i - k, j, 1);
					}
				}
			//reset the number of 0 found
			zero_count = 0;
			}
				else
			{
				zero_count++;
			}
		}
	}

	return output;
}

/**
 * \fn Matrix *rlsa(Matrix *m, int vr, int cr)
 * \brief Apply the rlsa vertically and horizontally, vr and cr are the
 * treshold of vertical and horizontal rlsa.
 *
 * \param m : The matrix
 * \param vr : vertical limit
 * \param cr : horizontal limit
 *
 * \return New  matrix
 */
Matrix *rlsa(Matrix *m, int vr, int cr)
{
    //if(m->size==952) SaveMatAsIm(m, "image_data/rlsa/m_rlsa.bmp");
    Matrix *v = Vrlsa(m, vr);

    //if(m->size==952) SaveMatAsIm(v, "image_data/rlsa/mv_rlsa.bmp");
	Matrix *h = Hrlsa(m, cr);
	Matrix *a = AndM(v, h);

	FreeM(v);
	FreeM(h);
	return a;
}
