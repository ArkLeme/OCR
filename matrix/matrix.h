#ifndef MATRIX
#define MATRIX

//Define matrix struct in header to avoid error
typedef struct Matrix
{
	int line;
	int col;
	int size;
	double* matrix;
}Matrix;

typedef struct List
{
	int x;
	struct list *next;
}List;

//init Matrix
Matrix InitM(int w, int h);

//init matrix from string
Matrix InitStringM(int line, int col, char* string);

//Put element in Matrix
void PutM(Matrix m, int i, int j, int e);
void PutPosM(Matrix m, int pos, int e);

//Get element in Matrix
double GetM(Matrix m, int i, int j);
double GetPosM(Matrix m, int pos);

//Display Matrix
void DisplayM(Matrix m);

//Free Matrix
void FreeM(Matrix m);

//Addition Matrix
Matrix AddM(Matrix m1, Matrix m2);

//Multiplication Matrix
Matrix MultM(Matrix m1, Matrix m2);

//Transpose Matrix
Matrix TransM(Matrix m1);

//And Matrix
Matrix AndM(Matrix m1, Matrix m2);

//Or Matrix
Matrix OrM(Matrix m1, Matrix m2);

//Mutliple 2 Matrix value by value
Matrix MultValM(Matrix m1, Matrix m2);

//Multiply Matrix by scalar
Matrix MultScalM(Matrix m1, double v);

#endif
