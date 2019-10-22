#include "rlsa.h"
#include <stdio.h>

//Apply horizontal lrsa
Matrix *Hrlsa(Matrix *m, int limit)
{
	Matrix* output = InitM(m -> line, m -> col);
	int zero_count = 0; //Number of 0 aside

	for(int i = 0; i < m -> line; i++)
	{
		//End of col
		if(zero_count <= limit)
		{
			for(int k = zero_count; k > 0; k--)
			{
				PutM(output, i, m -> col - k, 1);
			}
		}
		//Reset the number of 0 found on a line
		zero_count = 0;
		for(int j = 0; j < m -> col; j++)
		{
			//If the pixel is black
			if(GetM(m, i, j))
			{
				//If the number of 0 is suffisant
				if(zero_count <= limit)
				{
					//Replace them by black pixel
					for(int k = zero_count; k >= 0; k--)
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

//Aplly vertical lrsa
Matrix *Vrlsa(Matrix *m, int limit)
{
	Matrix *output = InitM(m -> line, m -> col);
	int zero_count = 0; //Number of 0 aside

	for(int j = 0; j < m -> col; j++)
	{
		//To handle the case of the end line
		if(zero_count <= limit)
		{
			for(int k = zero_count; k > 0; k--)
			{
				PutM(output, m -> line - k, j, 1);
			}
		}
		//Reset the number of zero found of the col
		zero_count = 0;
		for(int i = 0; i < m -> line; i++)
		{
			//If the pixel is black
			if(GetM(m, i, j) == 1)
			{
				//if the number of zero is suffisant
				if(zero_count <= limit)
				{
					//Replace them by black pixel
					for(int k = zero_count; k >= 0; k--)
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

//Apply both horizontal and vertical rlsa
Matrix *rlsa(Matrix *m, int limit)
{
	Matrix *v = Vrlsa(m, limit);
	Matrix *h = Hrlsa(m, limit);
	Matrix *a = AndM(v, h);

	FreeM(v);
	FreeM(h);
	return a;
}
