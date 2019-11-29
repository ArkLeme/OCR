#include "src/process_segmentation/get_list_segmented.h"
#include "src/UI/document.h"
#include "src/output_files/create_string.h"
#include "src/NeuNet/init_Network.h"

void Test(char *path);

int main(int argc, char **argv)
{
    if(argc == 2)
        Test(argv[1]);
}

void Test(char *path)
{
    int layersize[] = {28*28,20,16};
    //neuNet *network = init_network(layersize, 3);

    List *l = get_list_segmented(path);

    //char *c = get_string(path, network);

    //write_files("output.txt", l);

    //printf("%s", c);

    //free(c);

    DeleteL(l);
}
