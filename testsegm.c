#include <err.h>
#include "src/sdl_tools/sdl_tools.h"
#include "src/preprocessing/preprocessing.h"
#include "src/matrix/matrix.h"
#include "src/segmentation/rlsa.h"
#include "src/matrix/matrix_image.h"
#include "src/comp_labeling/comp_labeling.h"
#include "src/string/string_operation.h"
#include "src/segmentation_combine/separate_matrix.h"

void testBin(char* path);

int main(int argc, char** argv)
{
	if(argc == 2)
		testBin(argv[1]);
	return 0;
}

void testBin(char* path)
{
	SDL_Surface* InputImage = LoadImage(path);

	//Lenna preproc
	SDL_Surface* Lena = LoadImage("image_data/png/lena.png");
	SDL_Surface* GLena = GrayScale(Lena);
	SDL_Surface* CLena = Contrast(GLena);
	SDL_Surface* BLena = Otsu(CLena);

	SaveImage(GLena, "image_data/preproc/GrayLena.bmp");
	SaveImage(CLena, "image_data/preproc/ContrastLena.bmp");
	SaveImage(BLena, "image_data/preproc/BinLena.bmp");

	SDL_FreeSurface(Lena);

	//Basic preprocessing
	SDL_Surface* GrayImage = GrayScale(InputImage);
	SDL_Surface* ContrastImage = Contrast(GrayImage);
	SDL_Surface* BinImage = Otsu(ContrastImage);

	//LRSA
	Matrix *mm = GetMatFromIm(BinImage);
	SwapColor(mm);
	
	//4 = word, 10 = phrase
	Matrix *hw = Hrlsa(mm, 4);
	Matrix *hp = Hrlsa(mm, 12);
	Matrix *v = Vrlsa(mm, 80);
	Matrix *r = rlsa(mm, 80);
	Matrix *rv = Vrlsa(r, 15);
	Matrix *rr = Hrlsa(rv, 15);

	SaveMatAsIm(v, "image_data/rlsa/VHrlsa.bmp");

	//Save RLSA
	int mlw = 0;
	int mlp = 0;
	int mlr = 0;

	Matrix * twopassp = CompLabeling(hp, &mlp);
	SaveMatAsImRand(twopassp, "image_data/rlsa/HPrlsa.bmp", mlp);

	Matrix * twopassw = CompLabeling(rr, &mlw);
	SaveMatAsImRand(twopassw, "image_data/rlsa/RRrlsa.bmp", mlw);

	Matrix * twopassr = CompLabeling(r, &mlr);
	SaveMatAsImRand(twopassr, "image_data/rlsa/rlsa.bmp", mlr);
	
	FreeM(twopassw);
	FreeM(twopassp);
	FreeM(twopassr);

	//Test comp_label
	//Matrix *label = InitStringM(8, 8,
	//"1101110111010101111100010000000111110101000101011111000111110111");

	//Comp labeling Word
	int ml = 0;
	Matrix* twopass = CompLabeling(mm, &ml);
	SaveMatAsImRand(twopass, "image_data/label/twopass.bmp", ml);
	int nbl = NumberLabel(twopass, ml); //Get number of optimal label
	int* lbL = LabelReduceList(twopass, nbl, ml); //Get list of optimal label;
	ReduceLabel(twopass, lbL, nbl); //Give the optimal matrix
	PosM** pos = FindPosMat(twopass, nbl); //List of poas
	List* l = ListOfMat(twopass, pos, nbl); //List of pos and mat
	SaveMatsAsIm(l, 5, "image_data/label/char"); //Save some

	DeleteL(l);//Delete list
	FreeM(twopass);
	free(pos);

	//Free RLSA
	FreeM(hw);
	FreeM(hp);
	FreeM(v);
	FreeM(r);
	FreeM(rv);
	FreeM(rr);
	FreeM(mm);

	//FreeM(compLabel);

	SaveImage(GrayImage, "image_data/preproc/GrayImage.bmp");
	SaveImage(ContrastImage, "image_data/preproc/ContrastImage.bmp");
	SaveImage(BinImage, "image_data/preproc/BinImage.bmp");
	SDL_FreeSurface(InputImage);
}
