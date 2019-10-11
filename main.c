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
	Matrix m1 = InitM(3, 2);
	Matrix m2 = InitM(3, 2);

	for(int i = 1; i < 7; i++)
	{
		PutPosM(m1, i-1, 1);
		PutPosM(m2, i-1, rand() % 2);
	}

	Matrix t = TransM(m1);
	Matrix a = AndM(m1, m2);

	DisplayM(m1);
	DisplayM(m2);

	FreeM(m1);
	FreeM(m2);

	DisplayM(t);
	FreeM(t);

	DisplayM(a);
	FreeM(a);

	printf("test : %i\n", 1 == 1);
}
