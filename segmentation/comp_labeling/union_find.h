#ifndef UNION_FIND
#define UNION_FIND

typedef struct Subset
{
	int parent;
	int rank;
}Subset;

typedef struct Graph
{
	//number of different label
	int size;
	
	//Our label grpah is represented as subset
	Subset* subsets;
}Graph;

int FindParent(Subset* subsets, int i);

void Union(Subset* subsets, int i, int j);

#endif
