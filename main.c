#include <err.h>
#include "sdl_tools/sdl_tools.h"
#include "preprocessing/preprocessing.h"

int main(int argc, char** argv)
{
	if(argc != 2)
		errx(1, "Error, bad input : expected path to image");

	SDL_Surface* InputImage = LoadImage(argv[1]);
	SDL_Surface* GrayImage = GrayScale(InputImage);
	//SDL_Surface* ContrastImage = Contrast(InputImage);

	SDL_Surface* BinImage = Otsu(GrayImage);

	SaveImage(GrayImage, "image_data/GrayImage.bmp");
	//SaveImage(ContrastImage, "image_data/ContrastImage.bmp");
	SaveImage(BinImage, "image_data/BinImage.bmp");

	SDL_FreeSurface(InputImage);
	return 0;
}
