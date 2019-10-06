#include <err.h>
#include "sdl_tools/sdl_tools.h"
#include "preprocessing/preprocessing.h"

int main(int argc, char** argv)
{
	if(argc != 2)
		errx(1, "Error, bad input : expected path to image");

	printf("W = %s", argv[1]);

	return 0;
}
