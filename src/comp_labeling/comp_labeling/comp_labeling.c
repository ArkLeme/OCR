#include "comp_labeling.h"
#include <err.h>

/**
 * \file comp_labeling.c
 * \brief This file contains the functions requiered to apply the two pass
 * algorithm which is a connecting components labeling algorithm.
 * The purpose of the algorithm is to assign a label to every isolated bloc.
 * It allow us to separe our initial Matrix into many Matrix where each new
 * Matrix contains one bloc. This is our way to segment a text.
 * \author William.G
 */

/**
 * \fn Matrix *CompLabeling(Matrix *m, int *maxlabel)
 * \brief Apply the two pass algorithm, every 1 in the Matrix are considered
 * full and every 0 empty, so we label every 1 in the Matrix
 *
 * \param m : Matrix we want to label
 * \param maxLabel : number of different label in the Matrix (modif by ref)
 * \return Matrix where each bloc have a label
 */
Matrix *CompLabeling(Matrix *m, int* maxLabel)
{
	Matrix *fp = FirstPass(m, maxLabel);
	Graph *g = CreateGraph(fp, *maxLabel);
	Matrix *sp = SecondPass(fp, g);

    free_graph(g);
	FreeM(fp);

	return sp;
}

/**
 * \fn Matrix *FirstPass(Matrix *m, int *maxLabel)
 * \brief First pass in the Matrix, the purpose is to set a temporary label to
 * each pixel in the Matrix, we also create a tree where each label directly
 * connected are set as parent and children, it will help in the second pass
 * to merge both label together.
 *
 * \param m : Matrix we want to label
 * \param maxLabel : number of different label (set by ref)
 *
 * \return Matrix with label to each pixel
 */
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

/**
 * \fn Matrix *SecondPass(Matrix *m, Graph *g)
 * \brief Second pass in the Matrix, the purpose is to merge connected label
 * since they are the same bloc, we use the Graph struct where every label are
 * merged with their parent.
 *
 * \param m : Matrix we apply the second pass
 * \param g : Graph of label, it allow use to know which label are connected
 * together, it use the union-find implementation, more info : union_find.c
 *
 * \return Matrix where each bloc has a unique label
 */
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

/**
 * \fn Graph *CreateGraph(Matrix *m, int maxLabel)
 * \brief Create the Graph of the connection between every label
 *  in the Matrix, it use the union-find implementation
 *  for more info : union-find.c
 *
 * \param m : Matrix with the label
 * \param maxLabel : number of different label in the Matrix
 *
 * \return Graph with the connection of label
 */
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

/**
 * \fn int NumberLabel(Matrix *m, int ml)
 * \brief Find the number of usefull label in the Matrix.
 * After the second pass,
 * some label are merged so it create a gap between label.
 * For example, label 1 and 3 can be set in the Matrix, but not the label 2.
 * It is necessary to find the number of usefull label
 * to create the graph of connection
 * between label and free the memory correctly.
 *
 * To find the number of usefull label, we create and histogramm of every label.
 * For some of them,
 * the value will be 0 because there is no longer any label with
 * this value in our Matrix, they are the useeless label.
 *
 * \param m : Matrix we want to find the number of label
 * \param ml : maximum number of label in the Matrix.
 *
 * \return Number of usefull label in the Matrix
 */
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

/**
 * \fn int *LabelReduceList(Matrix *m,  int ml)
 * \brief This function replace every label by a lower one if it exist, for
 * example if label 2 is free and a bloc has the label 3, the bloc will have for
 * new label 2. It is necessary to reduce the number of label for realease the
 * allocated memory correctly.
 *
 * \param m : Matrix we want to reduce label value
 * \param nbl : number of usefull label
 * \param ml : number of the maximum label
 *
 * \return List of int where the new value of the label is 
 * at the index of the value of the old label.
 */
int* LabelReduceList (Matrix *m, int ml)
{
	int* list = malloc((ml + 1) * sizeof(int));
	int place = 1;
	int* listPlaced = calloc(ml + 1, sizeof(int));
	listPlaced[0] = 1; //Save label 0 as white and do not change is label
	list[0] = 0;

	for(int i = 0; i < m -> size; i++)
	{
		int pos = GetPosM(m, i);
		if(listPlaced[(int) pos] == 0)
		{
			list[pos] = place;
			place++;
			listPlaced[pos] = 1;
		}
	}

	free(listPlaced);
	return list;
}

/**
 * \fn void ReduceLabel(Matrix *m, int *lab)
 * \brief Replace the old label value in the Matrix by the new one found with
 * the LabelReduceList function
 *
 * \param m : Matrix we want to set the new label
 * \param lab : list of the new label
 * \param len : length of lab
 */
void ReduceLabel(Matrix *m, int *lab)
{
	for(int i = 0; i < m -> size; i++)
	{
		PutPosM(m, i, lab[(int) GetPosM(m, i)]);
	}

	free(lab);
}
