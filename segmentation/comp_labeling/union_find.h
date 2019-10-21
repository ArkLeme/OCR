#ifndef UNION_FIND
#define UNION_FIND

/*
 * Structure to stock the parent and the rank of each label
 * the value of a label is the position in the list of subset (in our graph)
 * parent is the parent of the label (lower lael connected)
 * rank is the height (mosly accurate) of our tree of label
 */
typedef struct Subset
{
	int parent;
	int rank;
}Subset;

/*
 * Graph of our subset
 * size is the number of subset
 * subsets the list of subset
 */
typedef struct Graph
{
	//number of different label
	int size;
	
	//Our label grpah is represented as subset
	Subset* subsets;
}Graph;

/*
 * Init our graph of subset
 * size is the number of subset
 * return the graph
 */
Graph *InitG(int size);

/*
 * Find the parent of a label
 * subsets is the list of subsets
 * i is the label value and the index of his subset
 * return the parent's value
 */
int FindParent(Subset* subsets, int i);

/*
 * Create the union of 2 subsets
 * subsets is the list of subsets
 * i the index of the first subset
 * j the index of the second subset
 */
void Union(Subset* subsets, int i, int j);

#endif
