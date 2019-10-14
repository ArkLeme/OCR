#include "union_find.h"


//Find parent of a node and reduce heightof the tree
int FindParent(Subset subsets[], int i)
{
	if(subsets[i].parent != i)
	{
		subsets[i].parent = FindParent(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

//Create union of 2 sets (union by rank)
void Union(Subset subsets[], int i, int j)
{
	int xParent = FindParent(subsets, i);
	int yParent = FindParent(subsets, j);

	if(subsets[xParent].rank > subsets[yParent].rank)
	{
		subsets[yParent].parent = xParent;
	}
	else if (subsets[xParent].rank < subsets[yParent].rank)
	{
		subsets[xParent].parent = yParent;
	}
	else
	{
		subsets[xParent].parent = yParent;
		subsets[yParent].rank++;
	}
}
