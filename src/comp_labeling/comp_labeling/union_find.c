#include "union_find.h"
#include <stdlib.h>

/**
 * \file union_find.c
 * \brief This file contains the function requiered
 * by the Union-find algorithm.
 * The purpose of the union-find is to create a set of element and to
 * connect every element together. It is use by the two pass algorithm.
 * \author William.G
 */

/**
 * \fn Graph *InitG(int size)
 * \brief Initialise our Graph structure and its components.
 *
 * \param size : number of Subset in our Graph
 *
 * \return An empty Graph with enough allocated memory for size Subset
 */
Graph *InitG(int size)
{
	Graph *g = malloc(sizeof(Graph));
	g -> size = size;
	g -> subsets = malloc(size * sizeof(Subset));

	for(int i = 0; i < size; i++)
	{
		g -> subsets[i].parent = i;
		g -> subsets[i].rank = 0;
	}

	return g;
}

/**
 * \fn void free_graph(Graph *g)
 * \brief Free the structure and the list of Subset. 
 *
 * \param g : The Graph
 */
void free_graph(Graph *g)
{
    free(g->subsets);
    free(g);
}

/**
 * \fn int FindParent(Subset *subsets, int i)
 * \brief Find the oldest parent of a Subset.
 * It also set every parent of the childrens
 * of the oldest parent to the oldest parent.
 *
 * Example :
 *
 * 1 has 2 as parent
 *
 * 2 has 3 as parent
 *
 * 3 has 4 as parent
 *
 * 4 has himself as parent (no parent)
 *
 * If we search the parent of 1, the function will return 4 and set
 * the parent of 1,2 and 3 to 4. It allows faster research afterward.
 *
 * \param subsets : list of every Subset in the Graph
 * \param i : position of the Subset whose we search the parent
 *
 * \return The parent of the Subset
 */
int FindParent(Subset *subsets, int i)
{
	if(subsets[i].parent != i)
	{
		subsets[i].parent = FindParent(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

/**
 * \fn void Union(Subset *subsets, int i, int j)
 * \brief When we must merge 2 Subset, we try to merge the smaller one to the
 * bigger one, if they have both the same size, we merge them as we want
 * and increase the size of the one whose get the other as children.
 *
 * \param subsets : list of every Subset
 * \param i : place of the first Subset
 * \param j : place of the second Subset
 */
void Union(Subset *subsets, int i, int j)
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
