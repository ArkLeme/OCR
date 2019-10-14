#include <stdlib.h>
#include "matrix_image.h"
#include "../string/string_operation.h"

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

void SaveMatAsImRand(Matrix *m, char* path, int label)
{

	Uint32* labelColor = (Uint32 *) calloc(label + 1, sizeof(Uint32));

	SDL_Surface* temp = CreateSurface(m -> col, m -> line);

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

void SaveMatsAsIm(List *l, int stop)
{
	char* s = "image_data/char";
	List* actual = l;
	
	while(actual != NULL && stop > 0)
	{
		char* sint = Itoa(stop);
		char* s1 = Concatene(s, sint);
		char* s2 = Concatene(s1, ".bmp");

		Matrix *m = (Matrix *) (actual -> mat);
		SaveMatAsImRand(m, s2, 1);

		actual = actual -> next;

		free(s1);
		free(s2);
		free(sint);

		stop--;
	}
}
