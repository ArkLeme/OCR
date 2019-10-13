#include "rlsa.h"
#include "../sdl_tools/sdl_tools.h"

void SaveMatAsIm(Matrix m)
{
	SDL_Surface* temp = CreateSurface(m.col, m.line);
	Uint32 pixel;
	Uint8 r;

	for(int i = 0; i < m.col; i++)
	{
		for(int j = 0; j < m.line; j++)
		{
			r = GetM(m, i, j) ? 0 : 255;
			pixel = SDL_MapRGB(temp -> format, r, r, r); 
			PutPixel(temp, i, j, pixel);
		}
	}

	SaveImage(temp, "image_data/testMat.bmp");
}

