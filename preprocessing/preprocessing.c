// Include lib required

#include <stdlib.h>
#include <err.h>
#include "preprocessing.h"

//Grayscale REC.709
SDL_Surface* GrayScale(SDL_Surface* InputImage)
{
	Uint32 pixel;
	Uint8 r,g,b;

	float avg;
	int w = InputImage -> w, h = InputImage -> h;

	SDL_Surface* OutputImage = CopySurface(InputImage);

	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, InputImage -> format, &r, &g, &b);

			//Apply grayscale formule (REC. 709)
			
			avg = r * 0.2126 + g * 0.7152 + b * 0.0722;
			avg = (g+b+r)/3;

			r = r > g ? g : r;
			avg = r > b ? b : r;

			pixel = SDL_MapRGB(OutputImage -> format, avg, avg, avg);
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
			r = r < 200 ? newValue[r] : 255;
			pixel = SDL_MapRGB(OutputImage -> format, r, r, r);
			PutPixel(OutputImage, i, j, pixel);
		}
	}

	return OutputImage;
}

SDL_Surface* Otsu(SDL_Surface* InputImage)
{
	Uint32 pixel;
	Uint8 r,g,b;

	int w = InputImage -> w, h = InputImage -> h, totalPixel = w * h;
	int histogram[256] = {0};
	double weight1 = 0, weight2 = 0;
	double summTotal = 0, summ1 = 0;
	double varMax, varAct;
	double mean1 = 0, mean2 = 0;
	int threshold = 0;

	//Save format
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
		if(weight1 == 0) continue;

		weight2 = totalPixel - weight1;
		if(weight2 == 0) continue;

		summ1 = (double) i * histogram[i];

		mean1 = summ1/weight1;
		mean2 = (summTotal - summ1)/weight2;

		varAct = weight1 * weight2 * (mean1 - mean2) * (mean1 - mean2);

		if(varAct > varMax)
		{
			varMax = varAct;
			threshold = i;
		}
	}
	return Binarization(InputImage, threshold);
}


SDL_Surface* Binarization(SDL_Surface* InputImage, int threshold)
{
	Uint32 pixel;
	Uint8 r, g, b;

	//Save format and copy Surface
	SDL_PixelFormat* format = InputImage -> format;
	SDL_Surface* OutputImage = CopySurface(InputImage);

	int w = InputImage -> w, h = InputImage -> h;

	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, format, &r, &g, &b);
			if(r <= threshold)
			{
				pixel = SDL_MapRGB(format, 0, 0, 0);
				PutPixel(OutputImage, i, j, pixel);
			}
			else
			{
				pixel = SDL_MapRGB(format, 255, 255, 255);
				PutPixel(OutputImage, i, j, pixel);
			}
		}
	}

	return OutputImage;
}
