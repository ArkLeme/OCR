#include "rlsa.h"
#include <stdio.h>

Matrix Hrlsa(Matrix m, int limit)
{
	Matrix output = InitM(m.line, m.col);
	int zero_count = 0; //Number of 0 aside

	for(int i = 0; i < m.line; i++)
	{
		if(zero_count <= limit)
		{
			for(int k = zero_count; k >=0; k--)
			{
				PutM(output, i, m.col - k, 1);
			}
		}
		zero_count = 0;
		for(int j = 0; j < m.col; j++)
		{
			if(GetM(m, i, j))
			{
				if(zero_count <= limit)
				{
					for(int k = zero_count; k >= 0; k--)
					{
						PutM(output, i, j - k, 1);
					}
				}
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

Matrix Vrlsa(Matrix m, int limit)
{
	Matrix output = InitM(m.line, m.col);
	int zero_count = 0; //Number of 0 aside

	for(int j = 0; j < m.col; j++)
	{
		if(zero_count <= limit)
		{
			for(int k = zero_count; k >=0; k--)
			{
				PutM(output, m.line - k - 1, j, 1);
			}
		}
		zero_count = 0;
		for(int i = 0; i < m.line; i++)
		{
			if(GetM(m, i, j) == 1)
			{
				if(zero_count <= limit)
				{
					for(int k = zero_count; k >= 0; k--)
					{
						PutM(output, i - k, j, 1);
					}
				}
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

Matrix rlsa(Matrix m, int limit)
{
	Matrix v = Vrlsa(m, limit);
	Matrix h = Hrlsa(m, limit);
	Matrix a = AndM(v, h);

	FreeM(v);
	FreeM(h);
	return a;
}
