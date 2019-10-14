#ifndef UNION_LABELING
#define UNION_LABELING

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

#endif
