#include "comp_labeling.h"

Matrix FirstPass(Matrix m, int* maxLabel)
{
	Matrix output = InitM(m.line, m.col);
	
	int label = 1;

	for(int i = 0; i < m.line ; i ++)
	{
		if(label > *maxLabel)
		{
			*maxLabel = label;
		}

		for(int j = 0; j < m.col; j++)
		{
			if(GetM(m, i, j) != 0)
			{
				int top = i > 0 ? GetM(output, i - 1, j) : 0;
				int left = j > 0 ? GetM(output, i, j - 1) : 0;

				if(top == 0 && left == 0)
				{
					label++;
				}
				else
				{
					label = top < left ? left : top;
				}

				PutM(output, i, j, label);
			}
			else
			{
				label++;
			}
		}
	}

	return output;
}

Graph CreateGraph(int size)
{
	Graph graph = {size, malloc(size * sizeof(struct Subset))};
	return graph;
}
