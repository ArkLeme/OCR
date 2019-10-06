// Include lib required

#include <stdlib.h>
#include "preprocessing.h"

// return a copy of an image after applying grayscale

SDL_Surface* GrayScale(SDL_Surface* InputImage)
{
	SDL_Init(SDL_INIT_VIDEO);

	Uint32 pixel;
	Uint8 r,g,b;
	float average;
	int w = InputImage -> w;
	int h = InputImage -> h;

	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, InputImage->format, &r, &g, &b);

			//Apply grayscale formule (REC. 709)
			average = r * 0.2126 + g * 0.7152 + b * 0.0722;
			r = (Uint8) average;

			PutPixel(InputImage, 
							i,
							j,
							SDL_MapRGB(InputImage -> format, r, r, r));
		}
	}

	SDL_Quit();
	return InputImage;
}
