#include <stdlib.h>
#include <err.h>
#include "preprocessing.h"

/**
 * \file preprocessing.c
 * \brief This file contains every functions related to the basic preprocessing
 * we apply on the image. It contains a grayscale, a contrast
 * and binarization function.
 * This file do not return a Matrix, but a SDL_Surface which is something
 * close to an image.
 * \author William.G
 */

/**
 * \fn SDL_Surface* GrayScale(SDL_Surface* InputImage)
 * \brief Create a new SDL_Surface but every pixel are gray.
 * It removes the color in the image
 * since it is an useless information in our case.
 *
 * \param InputImage : The image ito which we apply the grayscale
 *
 * \return New SDL_Surface, it does not modify the InputImage
 */
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

			//avg = r * 0.2126 + g * 0.7152 + b * 0.0722;
			avg = (g+b+r)/3;

			//r = r > g ? g : r;
			//avg = r > b ? b : r;

			pixel = SDL_MapRGB(OutputImage -> format, avg, avg, avg);
			PutPixel(OutputImage, i, j, pixel);
		}
	}

	return OutputImage;
}

/**
 * \fn SDL_Surface* Contrast(SDL_Surface* InputImage)
 * \brief Create contrast in the image, the goal of this function is to create
 * a bigger difference between the gray pixel. It helps the binarization to
 * find the best threshold.
 *
 * The algorithm is an equalization of histogram. The new value of a pixel is
 * basically the mean of the intensity of a pixel divided by the number of pixel.
 *
 * \param InputImage : The image to which we apply the contrast
 *
 * \return New SDL_Surface, it does not modify InputImage
 */
SDL_Surface* Contrast(SDL_Surface* InputImage)
{
	Uint32 pixel;
	Uint8 r,g,b;

	int w = InputImage -> w, h = InputImage -> h, sum = 0;

	//histogram of the image and new output of the image
	int histogram[256] = {0}, newValue[256] = {0};

	//Multiplicator to apply our weight
	float multiplicator = (float) 255 / (w * h);

	SDL_PixelFormat* format = InputImage -> format;
	SDL_Surface* OutputImage = CopySurface(InputImage);

	//Create the histogram
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, format, &r, &g, &b);

			histogram[(int) r]++;
		}
	}

	//Apply the equalization
	for(int i = 0; i < 256; i++)
	{
		sum += histogram[i];
		newValue[i] = (int) (sum * multiplicator);
	}

	//Create our new surface
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, InputImage -> format, &r, &g, &b);
			//r = r < 232 ? newValue[r] : 255;
			r = newValue[r];
			pixel = SDL_MapRGB(OutputImage -> format, r, r, r);
			PutPixel(OutputImage, i, j, pixel);
		}
	}

	return OutputImage;
}

/**
 * \fn SDL_Surface* Otsu(SDL_Surface* InputImage)
 * \brief The function of binarization, we use the Otsu's method which is a global
 * binarization.
 *
 * The goal of the function is to find a threshold to delimit the
 * which pixel will become black and which pixel will become white.
 *
 * The principle of this function is to try every threshold and test if this
 * threshold create a minimim variance between pixel with higher and lower
 * intensity. If the variance is minimal it mean the  black pixels have an
 * intensoty close to each other. The same goes for the white pixel.
 *
 * When we found the threshold, we can change pixel to black if they have a
 * lower intensity, we change them in white otherwise.
 *
 * \param InputImage : The image we binazrize
 *
 * \return New SDL_Surface, it does not modify the InputImage
 */
SDL_Surface* Otsu(SDL_Surface* InputImage)
{
	Uint32 pixel;
	Uint8 r,g,b;

	float w = InputImage -> w, h = InputImage -> h, totalPixel = w * h;

	//Histogram of our image
	unsigned long histogram[256] = {0};

	//Weight of class 1 and class 2
	unsigned long weight1 = 0, weight2 = 0;

	//Total summ is pt*t where pt is the probability of a pixel of t intensity
	unsigned long summTotal = 0, summ1 = 0;

	//Variance max and variance of the actual class
	float varMax, varAct;

	//Mean of class 1 and class 2
	unsigned long mean1 = 0, mean2 = 0;

	//Our threshold
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
		if(weight2 == 0) break;

		summ1 += i * histogram[i];

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

/**
 * \fn SDL_Surface* Binarization(SDL_Surface* InputImage, int threshold)
 * \brief It transform every pixel in black or white according to a threshold.
 *
 * \param InputImage : The image we binarize
 * \param threshold : The intensity threshold between black and white pixel.
 *
 * \return New SDL_Surface, It does not modify the InputImage
 */
SDL_Surface* Binarization(SDL_Surface* InputImage, int threshold)
{
	Uint32 pixel;
	Uint8 r, g, b;

	//Save format and copy Surface
	SDL_PixelFormat* format = InputImage -> format;
	SDL_Surface* OutputImage = CopySurface(InputImage);

	int w = InputImage -> w, h = InputImage -> h;

	//Create the new image
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, format, &r, &g, &b);
			if(r < threshold)
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

SDL_Surface* testIm(SDL_Surface* InputImage)
{
	Uint32 pixel;
	Uint8 r, g, b;

	//Save format and copy Surface
	SDL_PixelFormat* format = InputImage -> format;
	SDL_Surface* OutputImage = CopySurface(InputImage);

    double l = 50;

	int w = InputImage -> w, h = InputImage -> h;

	//Create the new image
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			pixel = GetPixel(InputImage, i, j);
			SDL_GetRGB(pixel, format, &r, &g, &b);

            r = r + l > 255 ? 255 : r + l;
            g = g + l > 255 ? 255 : g + l;
            b = b + l > 255 ? 255 : b + l;

		    pixel = SDL_MapRGB(format, r, g, b);
			PutPixel(OutputImage, i, j, pixel);
		}
	}

    return OutputImage;
}
