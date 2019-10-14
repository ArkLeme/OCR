#include "union_find.h"
#include <stdlib.h>

Graph *InitG(int size)
{
	Graph *g = malloc(sizeof(Graph));
	g -> size = size + 1;
	g -> subsets = malloc((g -> size) * sizeof(Subset));
}

//Find parent of a node and reduce heightof the tree
int FindParent(Subset subsets[], int i)
{
	if(subsets[i].parent != i)
	{
		subsets[i].parent = FindParent(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

//Create union of 2 sets (union bj rank)
void Union(Subset subsets[], int i, int j)
{
	int iParent = FindParent(subsets, i);
	int jParent = FindParent(subsets, j);

	if(subsets[iParent].rank > subsets[jParent].rank)
	{
		subsets[jParent].parent = iParent;
	}
	else if (subsets[iParent].rank < subsets[jParent].rank)
	{
		subsets[iParent].parent = jParent;
	}
	else
	{
		subsets[iParent].parent = jParent;
		subsets[jParent].rank++;
	}
}
