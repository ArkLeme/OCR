#ifndef MATRIX
#define MATRIX

//Define matrix struct in header to avoid error
typedef struct Matrix
{
	int width;
	int height;
	int* matrix;
}Matrix;

//init Matrix
Matrix InitM(int w, int h);

//Put element in Matrix
void PutM(Matrix m, int i, int j, int e);

//Get element in Matrix
int GetM(Matrix m, int i, int j);

//Display Matrix
void DisplayM(Matrix m);

//Free Matrix
void FreeM(Matrix m);

#endif
