#ifndef MATRIX
#define MATRIX
/**
 * \file matrix.h
 * \brief header of matrix.c
 * It also defied the Matrix, PosM and List structure.
 * \author William.G
 */

/**
 * \struct Matrix
 * \brief Matrix structure. The Matrix is represented as a single array
 * instead of a two-dimensional. We can get the data faster
 *
 * \return new Matrix structure.
 */
typedef struct Matrix
{
    /**
     * Number of line in the Matrix.
     */
	int line;

    /**
     * Number of column in the Matrix.
     */
	int col;

    /**
     * Size of the matrix, it is line * col.
     */
	int size;

    /**
     * array of all element in the matrix.
     * It is represented as a single vector
     * instead of two-dimensional array.
     */
	double* matrix;
}Matrix;

/**
 * \struct PosM
 * \brief Contain the position of the 4 corner in a part of the matrix.
 *
 * A part of the matrix can represent :
 * A paragraph if the matrix was the text.
 * A line if the matrix was a paragrah.
 * A word if the matrix was a line.
 * A character if th Matrix was a word.
 *
 * We use mx, my, Mx and My to only copy a part of the matrix.
 */
typedef struct PosM
{
    /**
     * mx is the lower x y position of a part of the matrix.
     */
	int mx,;

    /**
     * my is the lower y position of a part of the matrix.
     */
    int my;

    /**
     * mX is the higher x position of a part of the matrix.
     */
    int Mx;

    /**
     * My is the higher y position of a part of the matrix.
     */
    int My;

}PosM;

/**
 * \struct List
 * \brief Linked list, we use it to get a list of all element in the text,
 * each element has for child is successor :
 *
 * The List of paragraph has the list of line for child.
 * The List of line has the list of word for child.
 * The List of word ahs the list of char for child.
 * The list of char has no child.
 *
 * This structure allow an easy iteration over every child, it will help the
 * reconstruction of the docuement afterward.
 *
 * Each List contain a matrix which reprensent itself (para, line, word, char)
 * and the PosM structure which is the position of the matrix in its parent.
 */
typedef struct  List List;
struct List
{
    /**
     * PosM structure, the ith element reprensent the position
     * of the ith Matrix in the parent Matrix.
     */
	PosM* pos;

    /**
     * Void pointer, we can stock every data we want, it is mostly used for
     * Matrix but I have implemented this methid to try using void pointer.
     */
	void* mat;

    /**
     * Next element in our List, NULL pointeur if it is the last element.
     */
	List* next;

    /**
     * Child of the actual element, NULL in case of character.
     */
    List* child;
};

/*
 * Init the matrix struct
 * col is the number of col
 * line is the number of line
 * return a pointeur to the matrix
 */
Matrix* InitM(int line, int col);

/*
 * Init a matrix from a string
 * line is the number of line
 * col is the number of col
 * string is the input string to create the matrix, 1 = black, 0 = white
 * return a pointeur to the matrix
 */
Matrix* InitStringM(int line, int col, char* string);

/*
 * Put a value in the matrix
 * m is the matrix
 * i is the line
 * j the col
 * e the value
 */
void PutM(Matrix* m, int i, int j, double e);

/*
 * Put a value in the matrix
 * m is the matrix
 * pos the position (m + pos)
 * e is the value
 */
void PutPosM(Matrix* m, int pos, double e);

/*
 * Get a value in a matrix
 * m is the matrix
 * i the line
 * j the col
 * return the value
 */
double GetM(Matrix *m, int i, int j);

/*
 * Get a value in a matrix
 * m is the matrix
 * pos the position of the value (m + pos)
 * return the value
 */
double GetPosM(Matrix *m, int pos);

/*
 * Display a matrix
 * m is the matrix
 */
void DisplayM(Matrix* m);

/*
 * Display a matrix and its components as double
 * m is the matrix
 */
void DisplayM_double(Matrix* m);

/*
 * Free the matrix structure
 * m is the matrix
 */
void FreeM(Matrix *m);


/*
 * Fill up the Matrix with 0
 * m is the matrix
 */

void FillupM(Matrix *m);

/* DEPRECATED DESCRIPTION
 * Add two matrix and return the first one
 * m1 is the first matrix
 * m3 the second
 * return m1
 */

void Add_OptiM(Matrix *m1, Matrix *m2);



/*
 * Add two matrix and return a new one
 * m1 is the first matrix
 * m3 the second
 * return a new matrix
 */

Matrix *AddM(Matrix *m1, Matrix *m2);

/*
 * Multiplication between two matrix and return a new one
 * m1 is the first matrix
 * m2 the second
 * return a newt matrix
 */ 
Matrix *MultM(Matrix *m1, Matrix *m2);

/*
 * Create the transpose of a matrix and return a new one
 * m1 the matrix we transpose
 * return a new matrix
 */
Matrix *TransM(Matrix *m1);

/*
 * Apply logic and on two matrix and return a new one
 * m1 is the first matrix
 * m3 the second
 * return a new matrix
 */
Matrix *AndM(Matrix *m1, Matrix *m2);

/*
 * Apply logic or on two matrix and return a new one
 * m1 is the first matrix
 * m2 the second
 * return a new matrix
 */
Matrix *OrM(Matrix *m1, Matrix *m2);

/*
 * Apply element wise multiplication on two matrix
 * m1 is the first matrix
 * m2 the second
 * return a new matrix
 */
Matrix *MultValM(Matrix *m1, Matrix *m2);

/*
 * Multiply a matrix by a sclar
 * m1 is the matrix
 * v the scalar
 * return a new matrix
 */
Matrix *MultScalM(Matrix *m1, double v);
void MultScalMP(Matrix *m, double v);

/*
 * Copy a part of a matrix
 * mx is the left pos
 * my the top pos
 * Mx the right pos
 * My the bottom pos
 * return a new matrix
 */
Matrix* CopyMatrix(Matrix *m, int mx, int my, int Mx, int My);

/*
 * Normalize matrix to 28x28
 * m is the matrix
 * return the matrix and free the old one
 */
Matrix* normalize_dimension(Matrix *m);

/*
 * Initiate the structure PosM
 * mx is the left pos
 * my the top pos
 * Mx the right pos
 * My the bottom pos
 * return the structure
 */
PosM* InitP(int mx, int my, int Mx, int My);

/*
 * Initiate the list of structure
 * m is the structure we stock (matrix or list of matrix)
 * p is the position of the matrix
 * return the list
 */
List* InitL(void *m, void *p);

/*
 * Free a list and it's components
 * l is the list
 */
void FreeL(List *l);

/*
 * Append an element to the list
 * old is the list we append the element to
 * m is the struct
 * p the position
 * return old pointeur
 */
List* AppendL(List* old, void *m, void *p);

/*
 * Prepend an element to the list
 * old is the list we preprend the element to
 * m the struct
 * p the position
 * return new first element pointeur
 */
List* PrependL(List* old, void *m, void *p);

/*
 * remove first element of our list
 * l is the list
 * return the new first element
 */
List* RemoveFL(List *l);

/*
 * Remove the last elemnt of a list
 * l is the list
 * return the l
 */
List * RemoveLL(List* l);

/*
 * delete a list and free everything
 */
void DeleteL(List* l);

Matrix* InitMWithValues(int c, int l, double*m);
#endif
