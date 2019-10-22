#include "comp_labeling.h"
#include <err.h>

//Apply connecting component labeling algorithm (two pass)
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

//First pass of the two pass algorithm
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
				//Get top and left pixel
				int top = i > 0 ? GetM(output, i - 1, j) : 0;
				int left = j > 0 ? GetM(output, i, j - 1) : 0;

				//Incremete label if there is no adjacent black pixel
				if(top == 0 && left == 0)
				{
					*maxLabel += 1;
					label = *maxLabel;
				}
				//Place the minimal label to our pixel
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

//Second pass of the two pass algorithm
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

//Create the graph of our matrix
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

//Find the number of different label in our image
int NumberLabel(Matrix *m, int ml)
{
	int* histo = calloc(ml + 1, sizeof(int));

	for(int i = 0; i < m -> size; i++)
	{
		histo[(int) GetPosM(m, i)] = 1;
	}

	int label = 0;
	for(int i = 0; i < ml + 1; i++)
		if(histo[i] == 1) label++;

	free(histo);
	return label;
}

//reduce the number of label (replace bigger label by lower one)
int* LabelReduceList (Matrix *m, int nbl, int ml)
{
	int* list = malloc(nbl * sizeof(int));
	int place = 1;
	int* listPlaced = calloc(ml + 1, sizeof(int));
	listPlaced[0] = 1; //Save label 0 as white and do not change is label
	list[0] = 0;

	for(int i = 0; i < m -> size; i++)
	{
		int pos = GetPosM(m, i);
		if(listPlaced[(int) pos] == 0)
		{
			list[place] = pos;
			place++;
			listPlaced[pos] = 1;
		}
	}

	free(listPlaced);
	return list;
}

//Reduce the number of label in our matrix
void ReduceLabel(Matrix *m, int* lab, int len)
{
	for(int i = 0; i < m -> size; i++)
	{
		PutPosM(m, i, BinSearch(lab, GetPosM(m, i), len));
	}

	free(lab);
}

//BinSearch not working (might be the comparaison between double and int)
int BinSearch(int* list, int x, int len)
{
	for(int i = 0; i < len; i++)
	{
		if(list[i] == x)
			return i;
	}

	errx(1, "Should have found a value for th binsearch");
}
