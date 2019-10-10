#include <err.h>
#include "sdl_tools/sdl_tools.h"
#include "preprocessing/preprocessing.h"
#include "matrix/matrix.h"

void testBin(char* path);
void testM();

int main(int argc, char** argv)
{
	if(argc == 2)
		testBin(argv[1]);

	testM();

	return 0;
}

void testBin(char* path)
{
	SDL_Surface* InputImage = LoadImage(path);

	SDL_Surface* GrayImage = GrayScale(InputImage);
	//SDL_Surface* ContrastImage = Contrast(InputImage);
	SDL_Surface* BinImage = Otsu(GrayImage);

	SaveImage(GrayImage, "image_data/GrayImage.bmp");
	//SaveImage(ContrastImage, "image_data/ContrastImage.bmp");
	SaveImage(BinImage, "image_data/BinImage.bmp");

	SDL_FreeSurface(InputImage);
}

void testM()
{
	Matrix m = InitM(2, 2);
	PutM(m, 0, 0, 1);
	PutM(m, 1, 1, 1);

	DisplayM(m);

	FreeM(m);
}
