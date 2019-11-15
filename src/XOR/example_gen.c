#include "../matrix/matrix.h"
#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include "../process_segmentation/process_segm.h"
#include <string.h>
#include "example_gen.h"
/*!
 * \author pierre-olivier.rey
 * \brief Read examples from specidief file
 * \param path Path of the file containing examples
 * \param results Pointer to an array of char
 *
 * File is of this format:
 * c
 * Matrix of the char c
 * ...
 */
Matrix* ReadExamples(char* path, char*results)
{
	FILE*f = fopen(path, "r");
	if(f == NULL)
		errx(1, "Example file cannot be opened");
	int exNb;
	fscanf(f, "%d", &exNb); //gets the total number of example in that file
	Matrix *examples = (Matrix*) malloc(sizeof(Matrix) * exNb);
	results = malloc(sizeof(char) * exNb);
	//*results = (char*)malloc(sizeof(char) * exNb);

	char c;
	for(int i = 0; i < exNb; i++)
	{
		double*ch = malloc(sizeof(double) *784);
		c = (char) fgetc(f);
		fread(ch, sizeof(double), 784, f);
		Matrix *m = InitMWithValues(28, ch);
		examples[i] = *m;
		results[i] = c;
	}
	fclose(f);
	return examples;
}

void GenerateExamples(char* path)
{
	FILE *f = fopen(path, "r");
	if(f == NULL)
		errx(1, "Name file cannot be read");
	char *filename = malloc(sizeof(char) * 35);
	char *text = malloc(sizeof(char) * 10000);
	while(fscanf(f, "%s\n", filename) != EOF)
	{
		fgets(text, 10000, f);
		printf("filename : %s\n", filename);
		printf("text : %s\n", text);
		GenExample(filename, text);
		free(filename);
		free(text);
	}
	fclose(f);
}

/*!
 * \author pierre-olivier.rey
 * \brief add all characters on the image situated at path to the example file
 * \param ImagePath Path of the example image, it is the string in the image.
 * \param example Path of the example file.
 */
void GenExample(char* ImagePath, char* text)
{
	remove("neuralNetwork_data/example.txt");
	FILE* f = fopen("neuralNetwork_data/example.txt", "a");
	if(f == NULL)
		errx(1, "Example file cannot be opened");
	List* l = first_segmentation(ImagePath);
	Matrix* m;
	int i = 0;
	while(l != NULL)
	{
		if(text[i] == ' ') i++; //to 'remove' space in the string, à optimiser
		m = l->mat;
		fputc(text[i], f);
		fputc('\n', f);
		fwrite(m->matrix, sizeof(double), m->size, f);
		fputc('\n',f);
		//DISPLAY FOR TESTING
		printf("%c\n",text[i]);
		DisplayM(m);
		getchar();
		////
		l = RemoveFL(l); //next element in l
		i++;
	}
	fclose(f);
}
