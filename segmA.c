#include <err.h>
#include "src/sdl_tools/sdl_tools.h"
#include "src/preprocessing/preprocessing.h"
#include "src/matrix/matrix.h"
#include "src/segmentation/segmentation_image.h"
#include "src/segmentation/segmentation.h"
#include "src/matrix/matrix_image.h"

int main(int argc, char** argv)
{
	if(argc != 2)
	    errx(1, "Error, bad input : expected path to image");


	SDL_Surface* InputImage = LoadImage(argv[1]);
	SDL_Surface* Bin_for_img = Binarization(InputImage,128);
	SDL_Surface* Bin_for_mat = Binarization(InputImage,128);

	//Segmentation on image
	image_lines_segmentation(Bin_for_img);

	// Init list of lines
	Matrix *line = InitM(0,0);
	PosM* p1 = InitP(0,0,0,0);
	List *listoflines = InitL(line,p1);
	
	// Init list of words
	Matrix *word = InitM(0,0);
	PosM* p2 = InitP(0,0,0,0);
	List *listofwords = InitL(word,p2);

	Matrix *img_m = GetMatFromIm(Bin_for_mat);
	    
	//Segmentation of lines put in list of Matrix
	lines_segmentation(img_m,listoflines);
	// Remove the "null" matrix
	listoflines = RemoveFL(listoflines);

	List *next = listoflines;
	//Fill the list of words from each lines of the Paragraph
	while(next != NULL)
	{
	    words_segmentation(next->mat,listofwords);
	    next = next -> next;
	}
	//Remove the "null" matrix
	listofwords = RemoveFL(listofwords);

	//First char of the list and the image
	Matrix* firstline = listoflines ->  mat;
	//Second char of the list and the image
	Matrix* firstword = listofwords -> mat;

	char path[] = "image_data/first_line.bmp";
	char path1[] = "image_data/first_word.bmp";

	SaveMatAsIm(firstline,path);
	SaveMatAsIm(firstword,path1);
	
	SaveImage(Bin_for_img,"image_data/segm.bmp");

	//Free all Matrix and SDL_Surface
	SDL_FreeSurface(InputImage);
	SDL_FreeSurface(Bin_for_mat);
	FreeM(img_m);
	DeleteL(listoflines);
	DeleteL(listofwords);

	return 0;
}
