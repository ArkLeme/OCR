#include "matrix.h"
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

//Init matrix
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

//Put element e in matrix at [i,j]
void PutM(Matrix* m, int i, int j, double e)
{
	if(i < 0 || i >= m -> line || j < 0 || j > m -> col)
		errx(1, "Put Index outside of matrix i=%i, j=%i, h=%i, w=%i\n",
						i, j, m -> line, m -> col);
	*((m -> matrix) + (m -> col) * i + j) = e;
}

//Create Matrix from string
Matrix *InitStringM(int l, int c, char* str)
{
	Matrix *output = InitM(l, c);

	for(int i = 0; i < output -> size; i++)
	{
		PutPosM(output, i, '1' == str[i]);
	}

	return output;
}

//Put element e in matrix at [i/col, i%col]
void PutPosM(Matrix* m, int pos, double e)
{
	if(pos < 0 || pos >= m -> size)
		errx(1, "Put Index outside of matrix pos=%i, size=%i\n",
						pos, m -> size);
	*(m -> matrix + pos) = e;
}


//Get element e in matrix at [i,j]
double GetM(Matrix* m, int i, int j)
{
	if(i < 0 || i >= m -> line || j < 0 || j > m -> col)
		errx(1, "Get Index outside of matrix i=%i, j=%i, h=%i, w=%i\n",
						i, j, m -> line, m -> col);
	return *(m -> matrix + m -> col * i + j);
}

//Get element e in matrix at [i/col, i%col]
double GetPosM(Matrix* m, int pos)
{
	if(pos < 0 || pos >= m -> size)
		errx(1, "Get Index outside of matrix pos=%i, size=%i\n",
						pos, m -> size);
	return *(m -> matrix + pos);
}

//Display Matrix
void DisplayM(Matrix* m)
{
	for(int i = 0; i < m -> line; i++)
	{
		printf("[ ");
		for(int j = 0; j < m -> col; j++)
		{
			printf("%i ", (int) GetM(m, i, j));
		}
		printf("]\n");
	}
	printf("\n");
}

//Free Matrix
void FreeM(Matrix *m)
{
	free(m -> matrix);
	free(m);
}

//Addition Matrix
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

//Multiplication Matrix
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

//Transpose Matrix
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

//And on Matrix
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


//Or on Matrix
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

//Multiple 2 Matrix value by value
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

//Multiple Matrix by scalar
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

//Copy one matrix from position to another position
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

Matrix* normalize_dimension(Matrix *m)
{
    Matrix *out = InitM(28,28);

    for(int i = 0; i < m->line; i++)
    {
        for(int j = 0; j < m->col; j++)
        {
            PutM(out, i, j, GetM(m, i, j) != 0);
        }
    }

    FreeM(m);
    return out;
}
//Initiate List of struct
//We use it to stock our list of matrix and their position
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

//Initiate Position structure
//Position of the matrix in the original matrix
PosM* InitP(int mx, int my, int Mx, int My)
{
	PosM* pos = malloc(sizeof(PosM));
	pos -> mx = mx;
	pos -> my = my;
	pos -> Mx = Mx;
	pos -> My = My;
	return pos;
}

//Preprend a element to our list
List* PrependL(List* old, void *m, void *p)
{
	if(!old)
		return InitL(m, p);

	List *l = InitL(m, p);
	if(l)
		l -> next = old;

	return l;
}

//Append to a list
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

//Free our list
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
//Remove first
List* RemoveFL(List *l)
{
	if(l == NULL)
		errx(1, "Can not remove NULL");

	List *first = l;
	l = l -> next;
    FreeL(first);

	return l;
}

//Remove last
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

//Delete all the list
void DeleteL(List *l)
{
	while(l)
	{
		l = RemoveFL(l);
	}
}

Matrix* InitMWithValues(int s, double*m)
{
	Matrix* temp = malloc(sizeof(Matrix));
	temp -> line = s;
	temp -> col = s;
	temp -> size = s*s;
	temp -> matrix = m; 
	return temp;
}
