#ifndef MATRIX
#define MATRIX

/*
 * Struct of matrix, we use it in both neural network and segmentation.
 * line is the height of the matrix.
 * col is the width of the matrix.
 * size is col * line
 * matrix is our array of double
 */
typedef struct Matrix
{
	int line;
	int col;
	int size;
	double* matrix;
}Matrix;

/*
 * Structure of the position of the matrix
 * mx and my are the top left pos
 * Mx and My are the bottm right pos
 */
typedef struct PosM
{
	int mx, my, Mx, My;
}PosM;

/*
 * Structure of list, we use it to stock our list and the position of them
 * Posm* is a pointeur to the structure PosM, which is the pos of the matrix
 * void* is a pointeur to the structure we want to stock, it can be a matrix
 * or a list of matrix.
 * List* is a pointeur to the next element of our list, NULL if none
 */
typedef struct  List List;
struct List
{
	PosM* pos;
	void* mat;

	List* next;
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
void PutM(Matrix *m, int i, int j, double e);

/*
 * Put a value in the matrix
 * m is the matrix
 * pos the position (m + pos)
 * e is the value
 */
void PutPosM(Matrix *m, int pos, double e);

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
void DisplayM(Matrix *m);

/*
 * Free the matrix structure
 * m is the matrix
 */
void FreeM(Matrix *m);

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

#endif
