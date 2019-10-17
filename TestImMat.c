#include <err.h>
#include "sdl_tools/sdl_tools.h"
#include "preprocessing/preprocessing.h"
#include "matrix/matrix.h"
#include "segmentation/rlsa.h"
#include "segmentation/matrix_image.h"
#include "segmentation/xy_cut.h"

void testBin(char* path);
void testM();

int main(int argc, char** argv)
{
	if(argc == 2)
		testBin(argv[1]);

	return 0;
}

void testBin(char* path)
{
	SDL_Surface* InputImage = LoadImage(path);

	SDL_Surface* GrayImage = GrayScale(InputImage);
	SDL_Surface* ContrastImage = Contrast(InputImage);
	SDL_Surface* BinImage = Otsu(GrayImage);

	Matrix m = GetMatFromIm(BinImage);
	XCut(m);
	YCut(m);
	SaveMatAsIm(m, "image_data/xy.bmp");
	FreeM(m);

	Matrix mm = GetMatFromIm(BinImage);
	Matrix h = Hrlsa(mm, 10);
	Matrix v = Vrlsa(mm, 10);
	Matrix r = rlsa(mm, 10);

	SaveMatAsIm(h, "image_data/hrlsa.bmp");
	SaveMatAsIm(v, "image_data/vrlsa.bmp");
	SaveMatAsIm(r, "image_data/rlsa.bmp");
	SaveMatAsIm(mm, "image_data/inout.bmp");

	SaveImage(GrayImage, "image_data/GrayImage.bmp");
	SaveImage(ContrastImage, "image_data/ContrastImage.bmp");
	SaveImage(BinImage, "image_data/BinImage.bmp");

	FreeM(h);
	FreeM(v);
	FreeM(r);
	FreeM(mm);

	SDL_FreeSurface(InputImage);
}
