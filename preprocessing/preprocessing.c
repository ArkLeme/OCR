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
	int histogram[256] = {0}, newValue[256] = {0};
	float multiplicator = (float) 255 / (w * h);

	SDL_PixelFormat* format = InputImage -> format;
	SDL_Surface* OutputImage = CopySurface(InputImage);

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

int Otsu(SDL_Surface* InputImage)
{
	Uint32 pixel;
	Uint8 r,g,b;

	int w = InputImage -> w, h = InputImage -> h, totalPixel = w * h;
	int histogram[256] = {0};
	int weight1 = 0, weight2 = 0;
	float summTotal = 0, summ1 = 0;
	float varMax, varAct;
	int mean1 = 0, mean2 = 0;
	int threshold = 0;

	//Create copy of Surface and save format
	SDL_PixelFormat* format = InputImage -> format;

	//Create the histogram of our image
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, format, &r, &g, &b);

			histogram[(int) r]++;
		}
	}

	//Compute the global Mean (Esperance)
	for(int i = 0; i < 256; i++)
	{
		summTotal += i * histogram[i];
	}

	//Compute Variance (ecart-type) between class Variance
	//We can show that's finding the bigger between class
	//variance for a Threshold T is the same than finding
	//the lower within class variance but it's faster to compute.
	for(int i = 0; i < 256; i++)
	{
		weight1 += histogram[i];
		if(weight1 == 0) 
			continue;	//Variance will be 0

		weight2 = totalPixel - weight1;
		if(weight2 == 0)
			break;		//Variance will stay at 0

		summ1 = i * histogram[i];

		mean1 = summ1/weight1;
		mean2 = (summTotal - summ1)/weight2;

		varAct = weight1 * weight2 * (mean1 - mean2) * (mean1 - mean2);

		if(varAct > varMax)
		{
			varMax = varAct;
			threshold = i;
		}
	}

	return threshold;
}
