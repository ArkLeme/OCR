#ifndef MATRIX
#define MATRIX

//Define matrix struct in header to avoid error
typedef struct Matrix
{
	int line;
	int col;
	int size;
	int* matrix;
}Matrix;

//init Matrix
Matrix InitM(int w, int h);

//Put element in Matrix
void PutM(Matrix m, int i, int j, int e);
void PutPosM(Matrix m, int pos, int e);

//Get element in Matrix
int GetM(Matrix m, int i, int j);
int GetPosM(Matrix m, int pos);

//Display Matrix
void DisplayM(Matrix m);

//Free Matrix
void FreeM(Matrix m);

//Addition Matrix
void AddM(Matrix m1, Matrix m2);

//Multiplication Matrix
Matrix MultM(Matrix m1, Matrix m2);

//Transpose Matrix
Matrix TransM(Matrix m1);

//And Matrix
Matrix AndM(Matrix m1, Matrix m2);

#endif
