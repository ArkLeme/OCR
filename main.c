#include <err.h>
#include "sdl_tools/sdl_tools.h"
#include "preprocessing/preprocessing.h"

int main(int argc, char** argv)
{
	if(argc != 2)
		errx(1, "Error, bad input : expected path to image");

	SDL_Surface* InputImage = LoadImage(argv[1]);
	SDL_Surface* OutPutImage = GrayScale(InputImage);

	SaveImage(OutPutImage, "image_data/epitaGray.bmp");
	return 0;
}
