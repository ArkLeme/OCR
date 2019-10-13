#include "comp_labeling.h"

Matrix FirstPass(Matrix m, int* maxLabel)
{
	Matrix output = InitM(m.line, m.col);

	int label = 0;

	for(int i = 0; i < m.line ; i ++)
	{
		for(int j = 0; j < m.col; j++)
		{
			if(GetM(m, i, j) != 0)
			{
				int top = i > 0 ? GetM(output, i - 1, j) : 0;
				int left = j > 0 ? GetM(output, i, j - 1) : 0;

				if(top == 0 && left == 0)
				{
					*maxLabel += 1;
					label = *maxLabel;
				}
				else if(top == 0)
					label = left;
				else if(left == 0)
					label = top;
				else
					label = top < left ? top : left;

				PutM(output, i, j, label);
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
