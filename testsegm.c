#include <err.h>
#include "src/sdl_tools/sdl_tools.h"
#include "src/preprocessing/preprocessing.h"
#include "src/segmentation/rlsa.h"
#include "src/matrix/matrix_image.h"
#include "src/comp_labeling/comp_labeling.h"
#include "src/string/string_operation.h"
#include "src/process_segmentation/separate_matrix.h"
#include "src/process_segmentation/process_segm.h"

void testBin(char* path);

int main(int argc, char** argv)
{
	if(argc == 2)
		testBin(argv[1]);
	return 0;
}

void testBin(char* path)
{
    List* ll = paragraph_segm(path);
    List* l = ll;
    unsigned long avgh = 0, avgw = 0, size = 0;
    int mh = 0, mw = 0;
    while(l)
    {
        size++;
        Matrix *m = l->mat;
        if(mw < m->col)
            mw = m->col;
        if(mh < m->line)
            mh = m->line;
        avgw += m->col;
        avgh += m->line;
        l = l->next;
    }

    printf("w = %li, h = %li, mw = %i, mh = %i\n", avgw/size, avgh/size, mw, mh);
    DeleteL(ll);
}
