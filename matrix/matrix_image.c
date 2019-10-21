#include <stdlib.h>
#include "matrix_image.h"
#include "../string/string_operation.h"

//Save Matrix as and image
void SaveMatAsIm(Matrix *m, char* path)
{
	SDL_Surface* temp = CreateSurface(m -> col, m -> line);
	Uint32 pixel;
	Uint8 r;

	for(int i = 0; i < m -> line; i++)
	{
		for(int j = 0; j < m -> col; j++)
		{
			int v = GetM(m, i, j);
			if(v == 0) r = 255;
			else if(v == 2) r = 127;
			else r = 0;
			pixel = SDL_MapRGB(temp -> format, r, r, r); 
			PutPixel(temp, j, i, pixel);
		}
	}

	SaveImage(temp, path);
}

//Create a matrix from an image
Matrix *GetMatFromIm(SDL_Surface* InputImage)
{
	Matrix *temp = InitM(InputImage -> h, InputImage -> w);
	Uint8 r;
	Uint32 pixel;

	for(int i = 0; i < temp -> line; i++)
	{
		for(int j = 0; j < temp -> col; j++)
		{
			pixel = GetPixel(InputImage, j, i);
			SDL_GetRGB(pixel, InputImage -> format, &r, &r, &r);
			PutM(temp, i, j, r == 0);
		}
	}

	return temp;
}

//Save matrix as image with random color depending on the data in the matrix
void SaveMatAsImRand(Matrix *m, char* path, int label)
{
	//Create a list of pixel color for each label
	Uint32* labelColor = (Uint32 *) calloc(label + 1, sizeof(Uint32));

	SDL_Surface* temp = CreateSurface(m -> col, m -> line);

	//Assign random color to each pixel in the list
	labelColor[0] = SDL_MapRGB(temp -> format, 255, 255, 255);
	for(int i = 1; i < label + 1; i++)
	{
		labelColor[i] = SDL_MapRGB(temp -> format,
						rand() % 255, rand() % 255, rand() % 255);
	}

	for(int i = 0; i < m -> line; i++)
	{
		for(int j = 0; j < m -> col; j++)
		{
			/*
			 * If the label is one, we just want to print one char,
			 * but is label might be something random, and we do not want to
			 * create a list for just one color, so we assign random color if
			 * the pixel is not white.
			 * */
			int v = GetM(m, i, j);
			if(label == 1)
				PutPixel(temp, j, i, labelColor[v != 0]);
			else
				PutPixel(temp, j, i, labelColor[v]);
		}
	}

	free(labelColor);
	SaveImage(temp, path);
}

//Save a list of matrix
void SaveMatsAsIm(List *l, int stop, char* path)
{
	List* actual = l;
	
	while(actual != NULL && stop > 0)
	{
		//Create the string to sve all our image
		char* sint = Itoa(stop);
		char* s1 = Concatene(path, sint);
		char* s2 = Concatene(s1, ".bmp");

		//Save the matrix as an image with random color
		Matrix *m = (Matrix *) (actual -> mat);
		SaveMatAsImRand(m, s2, 1);

		actual = actual -> next;

		//Free the string we malloc earlier
		free(s1);
		free(s2);
		free(sint);

		stop--;
	}
}
