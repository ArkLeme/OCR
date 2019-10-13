#include "matrix_image.h"

void SaveMatAsIm(Matrix m, char* path)
{
	SDL_Surface* temp = CreateSurface(m.col, m.line);
	Uint32 pixel;
	Uint8 r;

	for(int i = 0; i < m.line; i++)
	{
		for(int j = 0; j < m.col; j++)
		{
			int v = GetM(m, i, j);
			if(v == 0) r = 255;
			if(v == 1) r = 0;
			if(v == 2) r = 127;
			pixel = SDL_MapRGB(temp -> format, r, r, r); 
			PutPixel(temp, j, i, pixel);
		}
	}

	SaveImage(temp, path);
}

Matrix GetMatFromIm(SDL_Surface* InputImage)
{
	Matrix temp = InitM(InputImage -> h, InputImage -> w);
	Uint8 r;
	Uint32 pixel;

	for(int i = 0; i < temp.line; i++)
	{
		for(int j = 0; j < temp.col; j++)
		{
			pixel = GetPixel(InputImage, j, i);
			SDL_GetRGB(pixel, InputImage -> format, &r, &r, &r);
			PutM(temp, i, j, r == 0);
		}
	}

	return temp;
}
