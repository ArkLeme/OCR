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

	//Basic preprocessing
	SDL_Surface* GrayImage = GrayScale(InputImage);
	SDL_Surface* ContrastImage = Contrast(GrayImage);
	SDL_Surface* BinImage = Otsu(CotrastImage);

	//LRSA
	matrix mm = GetMatFromIm(BinImage);
	//4 = word, 10 = phrase
	Matrix *hw = Hrlsa(mm, 4);
	Matrix *hp = Hrlsa(mm, 10);
	Matrix *v = Vrlsa(mm, 10);
	Matrix *r = rlsa(mm, 10);

	//Save RLSA
	SaveMatAsIm(hw, "image_data/HWrlsa.bmp");
	SaveMatAsIm(hp, "image_data/HPlsa.bmp");
	SaveMatAsIm(v, "image_data/vrlsa.bmp");
	SaveMatAsIm(r, "image_data/rlsa.bmp");
	
	//Test comp_label
	//Matrix label = InitStringM(8, 8,
	//"1101110111010101111100010000000111110101000101011111000111110111");

	//Free RLSA
	FreeM(hp);
	FreeM(hv);
	FreeM(v);
	FreeM(r);
	FreeM(mm)

	FreeM(compLabel)

	SDL_FreeSurface(InputImage);
}
