#include "src/process_segmentation/get_list_segmented.h"
#include "src/UI/document.h"
#include "src/output_files/create_string.h"

Docs docs = {NULL, NULL, NULL};

void Test(char *path);

int main(int argc, char **argv)
{
    if(argc == 2)
        Test(argv[1]);
}

void Test(char *path)
{

    char *c = generate_string(l);

    //write_files("output.txt", l);

    printf(c);

    free(c);

}
