#include <err.h>
#include "sdl_tools/sdl_tools.h"
#include "preprocessing/preprocessing.h"
#include "matrix/matrix.h"
#include "segmentation/segmentation_image.h"
#include "segmentation/segmentation.h"
#include "matrix/matrix_image.h"

int main(int argc, char** argv)
{
	if(argc != 2)
	    errx(1, "Error, bad input : expected path to image");


	SDL_Surface* InputImage = LoadImage(argv[1]);
	SDL_Surface* Bin_for_img = Binarization(InputImage,128);
	SDL_Surface* Bin_for_mat = Binarization(InputImage,128);

	//Segmentation on image
	image_lines_segmentation(Bin_for_img);

	Matrix *m = InitM(0,0);
	PosM* p1 = InitP(0,0,0,0);
	List *listofchar = InitL(m,p1);

	Matrix *img_m = GetMatFromIm(Bin_for_mat);
	    
	//Segmentation put in list of matrix
	lines_segmentation(img_m,listofchar);

	listofchar = RemoveFL(listofchar);

	//First char of the list and the image
	Matrix* first = listofchar ->  mat;
	//Second char of the list and the image
	Matrix* second = listofchar -> next -> mat;

	char path[] = "image_data/char_1.bmp";
	char path1[] = "image_data/char_2.bmp";
	
	SaveMatAsIm( first,path);
	SaveMatAsIm(second,path1);
	
	SaveImage(Bin_for_img,"image_data/segm.bmp");

	//Free all Matrix and SDL_Surface
	SDL_FreeSurface(InputImage);
	SDL_FreeSurface(Bin_for_mat);
	FreeM(img_m);
	DeleteL(listofchar);

	return 0;
}
