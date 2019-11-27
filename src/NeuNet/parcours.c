#include "../matrix/matrix.h"
#include "../process_segmentation/process_segm.h"
#include "../segmentation/segmentation.h"
#include <stddef.h>
void Parcours(char* path)
{
    List* lg = paragraph_segm(path);
    List * lp = lg;
	List*p = NULL;

    while(lp != NULL)
    {
        line_segm(lp);
        List *ll = lp->child;

        while(ll != NULL)
        {
            words_segmentation(ll);
            List *lw = ll->child;

            while(lw != NULL)
            {
                char_segm(lw);
                List *lc = lw->child;

                while(lc != NULL)
                {

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

    //write_files("test.txt", lg);
    DeleteL(lg);
}


