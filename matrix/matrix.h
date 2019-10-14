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

//Position of matrix
typedef struct PosM
{
	int mx, my, Mx, My;
}PosM;

//List of Matrix
typedef struct  List List;
struct List
{
	PosM* pos;
	void* mat;

	List* next;
};

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

//Copy matrix from index
Matrix CopyMatrix(Matrix m, int mx, int my, int Mx, int My);

//Init Pos
PosM* InitP(int mx, int my, int Mx, int My);

//Init list
List* InitL(void *m, void *p);

//Free list
void FreeL(List *l);

//Append an element to the list
List* AppendL(List* old, void *m, void *p);

//Prepend an element to the list
List* PrependL(List* old, void *m, void *p);

//Remove first element
List* RemoveFL(List *l);

//Remove last element
List * RemoveLL(List* l);

//Delete list
void DeleteL(List* l);

#endif
