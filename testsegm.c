#include "src/process_segmentation/get_list_segmented.h"

void testBin(char* path);

int main(int argc, char** argv)
{
	if(argc == 2)
		testBin(argv[1]);
	return 0;
}

void testBin(char* path)
{
    List *l = get_list_segmented(path);
    DeleteL(l);
}

