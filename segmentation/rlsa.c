#include "rlsa.h"

void SaveMatAsIm(Matrix m, char* path)
{
	SDL_Surface* temp = CreateSurface(m.col, m.line);
	Uint32 pixel;
	Uint8 r;

	for(int i = 0; i < m.line; i++)
	{
		for(int j = 0; j < m.col; j++)
		{
			r = GetM(m, i, j) ? 0 : 255;
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
