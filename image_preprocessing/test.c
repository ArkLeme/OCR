#include <stdlib.h>
#include <SDL/SDL.h>
#include <err.h>
#include <SDL/SDL_image.h>

void load_image(char*  filename);

int main(int argc, char **argv)
{
	if(argc == 0)
		errx(1,"Error : no argument given");

	load_image(argv[1]);

	printf("Seems good enough\n");

	return 0;
}

void load_image(char* filename)
{
	SDL_Surface *image = IMG_Load(filename);
	printf("Height = %i and weight = %i\n", image->w, image->h);
}
