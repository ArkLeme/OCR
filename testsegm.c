#include <err.h>
#include "src/sdl_tools/sdl_tools.h"
#include "src/preprocessing/preprocessing.h"
#include "src/segmentation/rlsa.h"
#include "src/matrix/matrix_image.h"
#include "src/comp_labeling/comp_labeling.h"
#include "src/string/string_operation.h"
#include "src/process_segmentation/separate_matrix.h"
#include "src/process_segmentation/process_segm.h"
#include "src/output_files/create_string.h"

void testBin(char* path);
void SaveMat(List *l, int i, char *p);

int main(int argc, char** argv)
{
	if(argc == 2)
		testBin(argv[1]);
	return 0;
}

void testBin(char* path)
{
    List* lg = paragraph_segm(path);
    List * lp = lg;

    int p = 0;
    int l = 0;
    int w = 0;
    int c = 0;

    while(lp != NULL)
    {
        line_segm(lp);
        List *ll = lp->child;
        SaveMat(lp, p, "para");
        p++;

        while(ll != NULL)
        {
            word_segm(ll);
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

        //write_files("test.txt", lp->child);
        lp = lp->next;
        //lp = NULL;
    }

    DeleteL(lg);
}

void SaveMat(List *l,  int i, char *n)
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
