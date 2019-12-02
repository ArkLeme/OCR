#include "matrix.h"
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

/**
 * \file matrix.c
 * \brief This files contains almost every function using Matrix.
 * \author William.G
 */

/**
 * \fn Matrix* InitM(int l, int c)
 * \brief Init the Matrix structure, it calloc the good size of element, we set
 * it at 0 by default because in the pretraitement it represenent black pixel.
 *
 * \param l : height of the Matrix : number of line.
 * \param c : width of the Matrix : number of column.
 *
 * \return pointer to the structure
 */
Matrix* InitM(int l, int c)
{
	int size = l * c;
	Matrix* temp = malloc(sizeof(Matrix));
	temp -> line = l;
	temp -> col = c;
	temp -> size = size;
	temp -> matrix = calloc(size, sizeof(double));
	return temp;
}

/**
 * \fn void PutM(Matrix* m, int i, int j, double e)
 * \brief Place the element e at the position ith line and the jth column
 * in the Matrix m
 *
 * \param m : Matrix
 * \param i : ith line
 * \param j : jth column
 * \param e : element we insert
 */
void PutM(Matrix* m, int i, int j, double e)
{
	if(i < 0 || i >= m -> line || j < 0 || j > m -> col)
		errx(1, "Put Index outside of matrix i=%i, j=%i, h=%i, w=%i\n",
						i, j, m -> line, m -> col);
	*((m -> matrix) + (m -> col) * i + j) = e;
}

/**
 * \fn Matrix *InitStringM(int l, int c, char* str)
 * \brief Create a Matrix with a string as argument, the length of the string
 * must be l * c.
 *
 * \param l : number of line
 * \param c : number of column
 * \param str : the string
 *
 * \return pointer to the Matrix
 */
Matrix *InitStringM(int l, int c, char* str)
{
	Matrix *output = InitM(l, c);

	for(int i = 0; i < output -> size; i++)
	{
		PutPosM(output, i, '1' == str[i]);
	}

	return output;
}

/**
 * \fn void PutPosM(Matrix* m, int pos, double e)
 * \brief Since our Matrix are represented as a single array, we can insert an
 * element with only on index.
 *
 * \param m : Matrix
 * \param pos : index in the Matrix, pos = i * col + j
 * \param e : element inserted
 */
void PutPosM(Matrix* m, int pos, double e)
{
	if(pos < 0 || pos >= m -> size)
		errx(1, "Put Index outside of matrix pos=%i, size=%i\n",
						pos, m -> size);
	*(m -> matrix + pos) = e;
}


/**
 * \fn double GetM(Matrix* m, int i, int j)
 * \brief Get the element at the ith line and jth collumn in the m Matrix
 *
 * \param m : Matrix
 * \param i : ith line
 * \param j : jth column
 *
 * \return the element at this position
 */
double GetM(Matrix* m, int i, int j)
{
	return *(m -> matrix + m -> col * i + j);
}

/**
 * \fn double GetPosM(Matrix* m, int pos)
 * \brief Get the element at the pos index in the Matrix
 *
 * \param m : Matrix
 * \param pos : position of the element, pos = i * col + j
 *
 * \return the element at this position
 */
double GetPosM(Matrix* m, int pos)
{
	if(pos < 0 || pos >= m -> size)
		errx(1, "Get Index outside of matrix pos=%i, size=%i\n",
						pos, m -> size);
	return *(m -> matrix + pos);
}

/**
 * \fn void DisplayM(Matrix* m)
 * \brief Display the matrix in the console, display its components as double
 *
 * \param m : Matrix
 */
void DisplayM(Matrix* m)
{
	for(int i = 0; i < m -> line; i++)
	{
		printf("[ ");
		for(int j = 0; j < m -> col; j++)
		{
			printf("%i ",(int) GetM(m, i, j));
		}
		printf("]\n");
	}
	printf("\n");
}

/**
 * \fn void DisplayM_double(Matrix* m)
 * \brief Display the matrix in the console, display its components as double
 *
 * \param m : Matrix
 */
void DisplayM_double(Matrix* m)
{
	for(int i = 0; i < m -> line; i++)
	{
		printf("[ ");
		for(int j = 0; j < m -> col; j++)
		{
			printf("%f ",GetM(m, i, j));
		}
		printf("]\n");
	}
	printf("\n");
}

/**
 * \fn void FreeM(Matrix *m)
 * \brief Free the Matrix and the array of double
 *
 * \param m : Matrix
 */
void FreeM(Matrix *m)
{
	free(m -> matrix);
	free(m);
}

//Fill up the Matrix with 0
void FillupM(Matrix* m)
{
	for(int i = 0; i < m -> line; i++)
	{
		for(int j = 0; j < m -> col; j++)
		{
			PutM(m, i, j,0);
		}
		
	}
	
}

//Addition atrix without creating a new Matrix
void Add_OptiM(Matrix* m1, Matrix* m2)
{
	if(m1 -> col != m2 -> col || m1 -> line != m2 -> line)
		errx(1, "Add Matrix do not have the same dimension :\
						m1w=%i, mw2=%i, m1h=%i, m2h=%i\n",
						m1 -> col, m2 -> col, m1 -> line, m2 -> line);

	
	for(int i = 0; i < m1 -> line; i++)
	{
		for(int j=0; j<m1->col;j++)
		{
			*((m1 -> matrix) + (m1 -> col) * i + j) +=  GetM(m2, i,j);
		}
	}
}

/**
 * \fn Matrix* AddM(Matrix* m1, Matrix* m2)
 * \brief Addition of 2 matrix, it return a new matrix.
 * It return an error if both matrix do not have the same size
 *
 * \param m1 : first matrix
 * \param m2 : second matrix
 *
 * \return new matrix
 */
Matrix* AddM(Matrix* m1, Matrix* m2)
{
	if(m1 -> col != m2 -> col || m1 -> line != m2 -> line)
		errx(1, "Add Matrix do not have the same dimension :\
						m1w=%i, mw2=%i, m1h=%i, m2h=%i\n",
						m1 -> col, m2 -> col, m1 -> line, m2 -> line);

	Matrix *m = InitM(m1 -> line, m2 -> col);
	for(int i = 0; i < m1 -> size; i++)
	{
		PutPosM(m, i, GetPosM(m1, i) + GetPosM(m2, i));
	}

	return m;
}

/**
 * \fn Matrix* MultM(Matrix *m1, Matrix *m2)
 * \brief Multiplication of 2 matrix, it return a new matrix.
 * It return an error if both matrix fo not have the good size
 *
 * \param m1 : first matrix
 * \param m2 : second matrix
 *
 * \return new matrix
 */
Matrix* MultM(Matrix *m1, Matrix *m2)
{
	if(m1 -> col != m2 -> line)
			errx(1, "Mul Matrix can not be multiply : m1w=%i, m2w=%i\n",
							m1 -> col, m2 -> line);

	Matrix *m = InitM(m1 -> line, m2 -> col);
	for(int i = 0; i < m1 -> line; i++)
	{
		for(int j = 0; j < m2 -> col; j++)
		{
			for(int k = 0; k < m1 -> col; k++)
			{
				PutM(m, i, j, GetM(m, i, j) + GetM(m1, i, k) * GetM(m2, k, j));
			}
		}
	}

	return m;
}

/**
 * \fn Matrix* TransM(Matrix* m1)
 * \brief Transpose of a matrix, it return a new one
 *
 * \param m1 : matrix
 *
 * \return new matrix
 */
Matrix* TransM(Matrix* m1)
{
	Matrix* m = InitM(m1 -> col, m1 -> line);
	for(int i = 0; i < m1 -> line; i++)
	{
		for(int j = 0; j < m1 -> col; j++)
		{
			PutM(m, j, i, GetM(m1, i, j));
		}
	}

	return m;
}

/**
 * \fn Matrix* AndM(Matrix *m1, Matrix *m2)
 * \brief compute the and gate on 2 matrix and return a new one.
 * return an error if both matrix do not have the same size
 *
 * \param m1 : first matrix
 * \param m2 : second matrix
 *
 * \return new matrix
 */
Matrix* AndM(Matrix *m1, Matrix *m2)
{
	if(m1 ->col != m2 -> col || m1 -> line != m2 -> line)
		errx(1, "Add Matrix do not have the same dimension :\
						m1w=%i, mw2=%i, m1h=%i, m2h=%i\n",
						m1 -> col, m2 -> col, m1 -> line, m2 -> line);

	Matrix *m = InitM(m1 -> line, m1 -> col);

	for(int i = 0; i < m1 -> line; i++)
	{
		for(int j = 0; j < m1 -> col; j++)
		{
			if(GetM(m1, i, j) && GetM(m2, i, j))
					PutM(m, i, j, 1);
		}
	}

	return m;
}

/**
 * \fn Matrix* OrM(Matrix *m1, Matrix *m2)
 * \brief compute the OR gate on 2 matrix and return a new one.
 * return an error if both matrix do not have the same size
 *
 * \param m1 : first matrix
 * \param m2 : second matrix
 *
 * \return new matrix
 */
Matrix* OrM(Matrix *m1, Matrix *m2)
{
	if(m1 -> col != m2 -> col || m1 -> line != m2 -> line)
		errx(1, "Add Matrix do not have the same dimension :\
						m1w=%i, mw2=%i, m1h=%i, m2h=%i\n",
						m1 -> col, m2 -> col, m1 -> line, m2 -> line);

	Matrix *m = InitM(m1 -> line, m1 -> col);

	for(int i = 0; i < m1 -> line; i++)
	{
		for(int j = 0; j < m1 -> col; j++)
		{
			if(GetM(m1, i, j) || GetM(m2, i, j))
					PutM(m, i, j, 1);
		}
	}

	return m;
}

/**
 * \fn Matrix* MultValM(Matrix* m1, Matrix* m2)
 * \brief Mult element by element, know as the hadamard product or element wise
 * operation.
 * Return an error if both matrix do not have the same size.
 *
 * \param m1 : first matrix
 * \param m2 : second matrix
 *
 * \return new matrix
 */
Matrix* MultValM(Matrix* m1, Matrix* m2)
{
	if(m1 -> col != m2 -> col || m1 -> line != m2 -> line)
		errx(1, "Add Matrix do not have the same dimension :\
						m1w=%i, mw2=%i, m1h=%i, m2h=%i\n",
						m1 -> col, m2 -> col, m1 -> line, m2 -> line);

	Matrix *m = InitM(m1 -> line, m1 -> col);
	for(int i = 0; i < m1 -> line; i++)
	{
		for(int j = 0; j < m1 -> col; j++)
		{
			PutM(m, i, j, GetM(m1, i, j) * GetM(m2, i, j));
		}
	}

	return m;
}

/**
 * Matrix* MultScalM(Matrix *m1, double v)
 * \brief Multiply matrix by a scalar.
 *
 * \param m1 : matrix
 * \param v : scalar
 *
 * \return new matrix
 */
Matrix* MultScalM(Matrix *m1, double v)
{
	Matrix *m = InitM(m1 -> line, m1 -> col);

	for(int i = 0; i < m1 -> line; i++)
	{
		for(int j = 0; j < m1 -> col; j++)
		{
			PutM(m, i, j, v * GetM(m1, i, j));
		}
	}

	return m;
}

void MultScalMP(Matrix *m, double v)
{
	for(int i = 0; i < m -> line; i++)
	{
		for(int j = 0; j < m -> col; j++)
		{
			PutM(m, i, j, v * GetM(m, i, j));
		}
	}
}


/**
 * \fn Matrix* CopyMatrix(Matrix *m, int mx, int my, int Mx, int My)
 * \brief Copy a Matrix from position (mx,my) to (Mx,My)
 *
 * \param m : matrix
 * \param mx : lower x position
 * \param my : lower y position
 * \param Mx : higher x position
 * \param My : higher y postion
 *
 * \return new matrix
 */
Matrix* CopyMatrix(Matrix *m, int mx, int my, int Mx, int My)
{
	int diffX = Mx - mx + 1;
	int diffY = My - my + 1;
	Matrix *out = InitM(diffY, diffX);

	for(int i = 0; i < diffY; i++)
	{
		for(int j = 0; j < diffX; j++)
		{
			int value = GetM(m, my + i, mx + j);
			PutM(out, i, j, value > 0 ? 1 : 0);
		}
	}

	return out;
}

/**
 * \fn Matrix* normalize_dimension(Matrix *m)
 * \brief Copy a matrix in a 28*28 matrix at the top left
 *
 * \param m : matrix
 *
 * \return new matrix
 */
Matrix* normalize_dimension(Matrix *m)
{

    int wl = m->line > 28 ? 28 : m->line;
    int wc = m->col > 28 ? 28 : m->col;

    Matrix* m1 = InitM(28,28);
    for(int i = 0; i < wl; i++)
    {
        for(int j = 0; j < wc; j++)
        {
            PutM(m1, i, j, GetM(m, i, j) != 0);
        }
    }
	//FreeM(m);
    return m1;
}

/**
 * \fn List* InitL(void *m, void *p)
 * \brief Initiate the List structure, set next and child to NULL by default
 *
 * \param m : matrix
 * \param p : position of the matrix
 *
 * \return pointer to the list
 */
List* InitL(void *m, void *p)
{
	List *l = malloc(sizeof(List));
	if(l)
	{
		l -> mat = m;
		l -> pos = p;
		l -> next = NULL;
        l -> child = NULL;
	}

	return l;
}

/**
 * \fn PosM* InitP(int mx, int my, int Mx, int My)
 * \brief Initiate the Position of the matrix structure
 *
 * \param mx : lower x position
 * \param my : lower y position
 * \param Mx : higher x position
 * \param My : higher y postion
 *
 * \return pointer to the position
 */
PosM* InitP(int mx, int my, int Mx, int My)
{
	PosM* pos = malloc(sizeof(PosM));
	pos -> mx = mx;
	pos -> my = my;
	pos -> Mx = Mx;
	pos -> My = My;
	return pos;
}

/**
 * \fn List* PrependL(List* old, void *m, void *p)
 * \brief Add an element to the start of the List
 *
 * \param old : list
 * \param m : matrix
 * \param p : position of matrix
 *
 * \return pointeur to the new first element of the List
 */
List* PrependL(List* old, void *m, void *p)
{
	if(!old)
		return InitL(m, p);

	List *l = InitL(m, p);
	if(l)
		l -> next = old;

	return l;
}

/**
 * \fn List* AppendL(List* old, void *m, void *p)
 * \brief Add an element to the end of the List
 *
 * \param old : list
 * \param m : matrix
 * \param p : position of the matrix
 *
 * \return pointeur to the first element of the List
 */
List* AppendL(List* old, void *m, void *p)
{
	if(!old)
	{
		old = InitL(m, p);
		return old;
	}

	List *l = InitL(m, p);
	List *current = old;

	while(current -> next)
	{
		current = current -> next;
	}

	current -> next = l;
	return old;
}

/**
 * \fn void FreeL(List *l)
 * \brief Free the list and all of it components
 *
 * \param l : the list
 */
void FreeL(List *l)
{
    if(l != NULL)
    {
        if(l->pos != NULL)
            free(l -> pos);
        if(l->mat != NULL)
            FreeM((Matrix*) (l -> mat));
        DeleteL(l->child);
        free(l);
    }
}

/**
 * \fn List* RemoveFL(List *l)
 * \brief Remove the first element of the List
 *
 * \param l : the list
 *
 * \return Pointeur to the new first element, NULL if we delete all the list
 */
List* RemoveFL(List *l)
{
	if(l == NULL)
		errx(1, "Can not remove NULL");

	List *first = l;
	l = l -> next;
    FreeL(first);

	return l;
}

/**
 * \fn List* RemoveLL(List *l)
 * \brief Remove the last element of the List
 *
 * \param l : the list
 *
 * \return Pointer to the first element, NULL if we delete all the list
 */
List* RemoveLL(List *l)
{
	if(l == NULL)
		errx(1, "Can not remove NULL");

	List *last = l;
	while(last->next->next)
	{
		last = last->next;
	}

	FreeL(last->next);
    last->next = NULL;

	return l;
}

/**
 * \fn DeleteL(List *l)
 * \brief delete all element in the List.
 *
 * \param l : the list
 */
void DeleteL(List *l)
{
	while(l)
	{
		l = RemoveFL(l);
	}
}

Matrix* InitMWithValues(int c, int l, double*m)
{
	Matrix* temp = malloc(sizeof(Matrix));
	temp -> line = l;
	temp -> col = c;
	temp -> size = c*l;
	temp->matrix = m;
	return temp;
}
