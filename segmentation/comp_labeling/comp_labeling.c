#include "comp_labeling.h"

Matrix *CompLabeling(Matrix *m, int* maxLabel)
{
	Matrix *fp = FirstPass(m, maxLabel);
	Graph *g = CreateGraph(fp, *maxLabel);
	Matrix *sp = SecondPass(fp, g);

	free(g -> subsets);
	free(g);
	FreeM(fp);

	return sp;
}

Matrix* FirstPass(Matrix* m, int* maxLabel)
{
	Matrix *output = InitM(m -> line, m -> col);

	int label = 0;

	for(int i = 0; i < m -> line ; i ++)
	{
		for(int j = 0; j < m -> col; j++)
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

Matrix *SecondPass(Matrix *m, Graph *g)
{
	Matrix *output = InitM(m -> line, m -> col);
	
	for(int i = 0; i < m -> line; i++)
	{
		for(int j = 0; j < m -> col; j++)
		{
			int value = FindParent(g -> subsets, GetM(m, i, j));
			PutM(output, i, j, value);
		}
	}

	return output;
}

Graph *CreateGraph(Matrix *m, int maxLabel)
{
	Graph *g = InitG(maxLabel + 1);

	for(int i = 0; i < m -> line; i++)
	{
		for(int j = 0; j < m -> col; j++)
		{
			int top = i > 0 ? GetM(m, i - 1, j) : 0;
			int left = j > 0 ? GetM(m, i, j - 1) : 0;

			if(top != 0 && left != 0 && top != left)
			{
				if(top > left)
					Union(g -> subsets, top, left);
				else
					Union(g -> subsets, left, top);
			}
		}
	}

	return g;
}

int NumberLabel(Matrix *m)
{
	int label = 0;

	for(int i = 0; i < m -> size; i ++)
	{
		if(GetPosM(m, i) > label)
			label++;
	}

	return label;
}
