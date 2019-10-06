// Include lib required

#include <stdlib.h>
#include <err.h>
#include "preprocessing.h"

//Grayscale REC.709
SDL_Surface* GrayScale(SDL_Surface* InputImage)
{
	Uint32 pixel;
	Uint8 r,g,b;

	float average;
	int w = InputImage -> w, h = InputImage -> h;

	SDL_PixelFormat* format = InputImage -> format;
	SDL_Surface* OutputImage = CopySurface(InputImage);

	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, format, &r, &g, &b);

			//Apply grayscale formule (REC. 709)
			average = r * 0.2126 + g * 0.7152 + b * 0.0722;
			r = (Uint8) average;

			pixel = SDL_MapRGB(format, r, r, r);
			PutPixel(OutputImage, i, j, pixel);
		}
	}

	return OutputImage;
}

//Histogram equalization
SDL_Surface* Contrast(SDL_Surface* InputImage)
{
	Uint32 pixel;
	Uint8 r,g,b;

	int w = InputImage -> w, h = InputImage -> h, sum = 0;
	int histogram[256], newValue[256];
	float multiplicator = (float) 255 / (w * h);

	SDL_PixelFormat* format = InputImage -> format;
	SDL_Surface* OutputImage = CopySurface(InputImage);

	//Set array to 0 
	for(int i = 0; i < 256; i++)
	{
		histogram[i] = 0;
		newValue[i] = 0;
	}
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, format, &r, &g, &b);

			histogram[(int) r]++;
		}
	}

	for(int i = 0; i < 256; i++)
	{
		sum += histogram[i];
		newValue[i] = (int) (sum * multiplicator);
	}

	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, InputImage -> format, &r, &g, &b);
			r = newValue[r];
			pixel = SDL_MapRGB(OutputImage -> format, r, r, r);
			PutPixel(OutputImage, i, j, pixel);
		}
	}

	return OutputImage;
}
/*
SDL_Surface* Otsu(SDL_Surface* InputImage)
{
	Uint32 pixel;
	Uint8 r,g,b;

	int w = InputImage -> w, h = InputImage -> h, sum = 0;
	int histogram[256], newValue[256];

	//Create copy of Surface and save format
	SDL_PixelFormat* format = InputImage -> format;
	SDL_Surface* OutputImage = CopySurface(InputImage);

	//Set array to 0
	for(int i = 0, i < 256; i++)
	{
		histogram[i] = 0;
		newValue[i] = 0;
	}

	for(i = 0; i < w; i++)
	{
		for(j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRgb(pixel, format, &r, &g, &b);

			histogram[(int) r]++;
		}


	}
}*/
