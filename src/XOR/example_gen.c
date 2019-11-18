#include "../matrix/matrix.h"
#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include "../process_segmentation/process_segm.h"
#include <string.h>
#include "example_gen.h"
#include "../../testsegm.h"
#include "../string/string_operation.h"
#include "structNet.h"
#include "tools.h"

size_t GetSize()
{
	FILE*f = fopen("neuralNetwork_data/size.data", "r");
	if(f == NULL)
		errx(1, "Size file cannot be opened");
	size_t size;
	fscanf(f, "%ld\n", &size); //gets the total number of example in that file
	fclose(f);
	return size;
}
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
Pool* ReadExamples(char* path)
{
	Pool* pool = InitPool(GetSize());
	FILE*f = fopen(path, "r");
	if(f == NULL)
		errx(1, "Example file cannot be opened");
	for(size_t i = 0; i < pool->size; i++)
	{
		double*ch = malloc(784 * sizeof(double));
		fscanf(f, "%c\n", &pool->results[i]);
		fread(ch, sizeof(double), 784, f);
		
		Matrix *m = InitMWithValues(28, ch);
		pool->examples[i] = m;
		free(ch);
	}
	fclose(f);
	return pool;
}

void GenerateExamples(char* path)
{
	FILE *f = fopen(path, "r");
	if(f == NULL)
		errx(1, "Name file cannot be read");
	remove("neuralNetwork_data/examples.data");
	FILE* fe = fopen("neuralNetwork_data/examples.data", "w");
	if(fe == NULL)
		errx(1, "Example file cannot be opened");
	char *filename = malloc(sizeof(char) * 35);
	char *text = malloc(sizeof(char) * 10000);
	unsigned long int sum = 0;

	while(fscanf(f, "%s\n", filename) != EOF)
	{
		fgets(text, 10000, f);
		sum += GenExample(filename, text, fe);
		free(filename);
		free(text);
	}
	fclose(f);
	fclose(fe);
	char *itoa = Itoa(sum);
	f = fopen("neuralNetwork_data/size.data", "w");
	fprintf(f, "%s\n", itoa);
	fclose(f);
	free(itoa);

}

/*!
 * \author pierre-olivier.rey
 * \brief add all characters on the image situated at path to the example file
 * \param ImagePath Path of the example image, it is the string in the image.
 * \param example Path of the example file.
 */
int GenExample(char* ImagePath, char* text, FILE*f)
{
	List* l = first_segmentation(ImagePath);
	int nbChar = 0;
	int i = 0;
	while(l)
	{
		if(text[i] == ' ') i++; //to 'remove' space in the string, à optimiser
		fputc(text[i], f);
		fputc('\n', f);
		Matrix* m  = l->mat;
		fwrite(m->matrix, sizeof(double), m->size, f);
		//fputc('\n', f);
/*		
		//DISPLAY FOR TESTING
		printf("%c\n",text[i]);
		DisplayM(m);
		getchar();
*/		
		l = RemoveFL(l); //next element in l
		i++;
		nbChar++;
	}
	return nbChar;
}
