#include <err.h>
#include "src/sdl_tools/sdl_tools.h"
#include "src/preprocessing/preprocessing.h"
#include "src/matrix/matrix.h"
#include "src/segmentation/segmentation_image.h"
#include "src/segmentation/segmentation.h"
#include "src/matrix/matrix_image.h"
#include "src/process_segmentation/process_segm.h"
#include "src/string/string_operation.h"


static void SaveMat(List *l,  int i, char *n)
{
    char *sint = Itoa(i);
    char *p = Concatene("image_data/rlsa/", n);
    char *s = Concatene(p, sint);
    char *sf = Concatene(s, ".bmp");

    SaveMatAsIm(((Matrix*) (l->mat)),sf);

    free(s);
    free(sint);
    free(sf);
    free(p);
}


int main(int argc, char** argv)
{
	if(argc != 2)
	    errx(1, "Error, bad input : expected path to image");


	SDL_Surface* InputImage = LoadImage(argv[1]);
	SDL_Surface* Bin_for_img = Binarization(InputImage,128);
	//SDL_Surface* Bin_for_mat = Binarization(InputImage,128);

	//Segmentation on image
	image_lines_segmentation(Bin_for_img);

	/*// Init list of lines
	Matrix *line = InitM(0,0);
	PosM* p1 = InitP(0,0,0,0);
	List *listoflines = InitL(line,p1);
	
	// Init list of words
	Matrix *word = InitM(0,0);
	PosM* p2 = InitP(0,0,0,0);
	List *listofwords = InitL(word,p2);

	Matrix *img_m = GetMatFromIm(Bin_for_mat);
	    
	//Segmentation of each lines of IMAGE put in a list of Matrix
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
	

	//Free all Matrix and SDL_Surface
	FreeM(img_m);
	DeleteL(listoflines);
	DeleteL(listofwords);*/

	SaveImage(Bin_for_img,"image_data/segm.bmp");

	SDL_FreeSurface(InputImage);
    
	List *lg = paragraph_segm(argv[1]);
    List *lp = lg;

    
    int p = 0;
    int l = 0;
    int w = 0;
    int c = 0;
    

    while(lp != NULL)
    {
        lines_segmentation(lp);
        List *ll = lp->child;
        SaveMat(lp, p, "para");
        p++;

        while(ll != NULL)
        {
            words_segmentation(ll);
            List *lw = ll->child;
            SaveMat(ll, l, "line");
            l++;

            while(lw != NULL)
            {
                char_segm(lw);
                List *lc = lw->child;
                SaveMat(lw, w, "word");
                w++;

                while(lc != NULL)
                {
                    SaveMat(lc, c, "char");
                    c++;

                    lc = lc->next;
                    //lc = NULL;
                }

                lw = lw->next;
                //lw = NULL;
            }

            ll = ll->next;
            //ll = NULL;
        }

        lp = lp->next;
        //lp = NULL;
    }

	return 0;
}
