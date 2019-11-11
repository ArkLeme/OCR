#ifndef UNION_FIND_H
#define UNION_FIND_H

/**
 * \file union_find.h
 * \brief header of union_find.c
 * It also define the Subset and Graph structure.
 * \author William.G
 */

/**
 * \struct Subset
 * \brief It contains the parent of the Subset and the rank,
 * which is the number of parent the subset has.
 * It is use by the Union-find algorithm.
 */
typedef struct Subset
{
    /**
     * The direct parent of this Subset.
     * The meaning of parent depend of the usage of the struct.
     * Subset are stock in a list, where the Subset
     * is a the ith position in the list.
     * The parent is the ith position of the Subset.
     * For a Subset without parent, his parent is i (itself)
     */
	int parent;

    /**
     * Number of "parents" the Subset has.
     * Subset has only one parent, but a parent can have an other parent.
     * In order to merge 2 Subset (set Subset x as parent of Subset y)
     * we need to know which is the smallest for optimising the research later.
     */
	int rank;
}Subset;

/**
 * \struct Graph
 * \brief Graph of Subset, it contain the size which is the number of Subset
 * and a list of every Subset.
 * It is use by the Union-find algorithm.
 */
typedef struct Graph
{
    /**
     * Number of Subset in the graph, it is the number of element.
     */
	int size;

    /**
     * List of Subset, the Subset i is save at the ith position.
     * It allows use to find the parent of a Subset very easily.
     */
    Subset *subsets;

}Graph;

/*
 * Create the union of 2 subsets
 * subsets is the list of subsets
 * i the index of the first subset
 * j the index of the second subset
 */
Graph *InitG(int size);

/*
 * Free the graph
 * g is the graph
 */
void free_graph(Graph *g);

/*
 * Create the union of 2 subsets
 * subsets is the list of subsets
 * i the index of the first subset
 * j the index of the second subset
 */
int FindParent(Subset *subsets, int i);

/*
 * Create the union of 2 subsets
 * subsets is the list of subsets
 * i the index of the first subset
 * j the index of the second subset
 */
void Union(Subset *subsets, int i, int j);

#endif
