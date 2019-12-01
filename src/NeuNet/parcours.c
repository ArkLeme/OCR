#include "../matrix/matrix.h"
#include "../process_segmentation/process_segm.h"
#include "../segmentation/segmentation.h"
#include <stddef.h>
List* Parcours(char* path)
{
    List* lg = paragraph_segm(path);
    List * lp = lg;
	List*p = NULL;

    while(lp != NULL)
    {
        lines_segmentation(lp);
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
					p = AppendL(p, normalize_dimension(lc->mat), NULL);

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
	return p;
}


