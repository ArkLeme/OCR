#include <err.h>
#include "sdl_tools/sdl_tools.h"
#include "preprocessing/preprocessing.h"
#include "matrix/matrix.h"
#include "segmentation/rlsa.h"
#include "matrix/matrix_image.h"
#include "segmentation/xy_cut.h"
#include "segmentation/comp_labeling/comp_labeling.h"

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

	//Basic pretraitement
	SDL_Surface* GrayImage = GrayScale(InputImage);
	SDL_Surface* ContrastImage = Contrast(GrayImage);
	SDL_Surface* BinImage = Otsu(ContrastImage);

	//XY cut
	Matrix m = GetMatFromIm(BinImage);
	XCut(m);
	YCut(m);
	SaveMatAsIm(m, "image_data/xy.bmp");
	FreeM(m);

	//LRSA
	Matrix mm = GetMatFromIm(BinImage);
	//4 = word 10 = phrase
	Matrix h = Hrlsa(mm, 4);
	Matrix v = Vrlsa(mm, 10);
	Matrix r = rlsa(mm, 10);

	//Save LRSA
	SaveMatAsIm(h, "image_data/hrlsa.bmp");
	SaveMatAsIm(v, "image_data/vrlsa.bmp");
	SaveMatAsIm(r, "image_data/rlsa.bmp");
	SaveMatAsIm(mm, "image_data/inout.bmp");

	//Test comp_label
	//Matrix label = InitStringM(8, 8, "1101110111010101111100010000000111110101000101011111000111110111");

	int maxLabel;
	Matrix compLabel = CompLabeling(mm, &maxLabel);

	SaveMatAsImRand(compLabel, "image_data/labelTest.bmp", maxLabel);

	//Free LRSA
	FreeM(h);
	FreeM(v);
	FreeM(r);
	FreeM(mm);

	FreeM(compLabel);

	//Save pretraitement
	SaveImage(GrayImage, "image_data/GrayImage.bmp");
	SaveImage(ContrastImage, "image_data/ContrastImage.bmp");
	SaveImage(BinImage, "image_data/BinImage.bmp");

	SDL_FreeSurface(InputImage);
}
