#include <stdlib.h>
#include "../matrix/matrix.h"
#include "separate_matrix.h"

PosM* FindPosMat(Matrix m, int maxLabel)
{
	PosM *posM = malloc((maxLabel + 1) * sizeof(PosM));

	for(int i = 0; i < maxLabel + 1; i++)
	{
		posM[i].mx = -1;
		posM[i].my = -1;
		posM[i].Mx = -1;
		posM[i].My = -1;
	}

	for(int i = 0; i < m.line; i++)
	{
		for(int j = 0; j < m.col; j++)
		{
			int label = GetM(m, i, j);
			if(label != 0)
			{
				PosM *p = &posM[label];
				if(p -> mx < 0)
				{
					p -> mx = j;
					p -> Mx = j;
					p -> my = i;
					p -> My = i;
				}
				else
				{
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

List* ListOfMat(Matrix *m, PosM *p, int maxLabel)
{

	List *l = NULL;

	for(int i = 0; i < maxLabel; i++)
	{
		if(p[i].mx != -1)
		{
			Matrix mat = CopyMatrix(*m, p[i].mx, p[i].my, p[i].Mx, p[i].My);
			l = PrependL(l, &mat, &p[i]);

		}
	}

	return l;
}
