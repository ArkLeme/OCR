#include "../matrix/matrix.h"
#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include "../process_segmentation/process_segm.h"
#include <string.h>
#include "example_gen.h"
#include "../string/string_operation.h"
#include "structNet.h"
#include "memory_handler.h"
#include "parcours.h"

/*!
 * \author pierre-olivier.rey 
 * \brief Get the total number of examples that will be read later. 
 * \return The number of examples.
 * Read the number in the first line of the file at the path "neuralNetwork_data/size.data". The file must exist. 
 */
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
 * \brief Read examples from specified file
 * \param path Path of the file containing examples
 * \return A Pool containing all examples that have been read.
 * File is of this format:
 * c\n
 * Matrix of the char c\n
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
		pool->results[i] = fgetc(f);
		fgetc(f);
		fread(ch, sizeof(double), 784, f);
		fgetc(f);	
		Matrix *m = InitMWithValues(28, 28, ch);
		pool->examples[i] = m;
//		printf("%c\n", pool->results[i]);
//		DisplayM(m);
	}
	fclose(f);
	printf("ok generation\n");
	return pool;
}

/*!
 * \author pierre-olivier.rey
 * \brief Write all examples contained in the name file at path. 
 * \param path Path of the name file, where data about exmaples is stored.
 * Generate examples.data and size.data in the folder neuralNetwork_data.
 * examples.data contains matrixes ans associated characters that will be used to train the network.
 * size.data contains at his first line the number of example that have been written.
 * the name file at path is a file with this following format:
 * imagePath
 * text contained in this image, with no point and caps.
 * ...
 */
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
//		printf("%s\n%s", filename, text);
		sum += GenExample(filename, text, fe);
	}
	free(filename);
	free(text);
	fclose(f);
	fclose(fe);
	char *itoa = Itoa(sum);
	remove("neuralNetwork_data/size.data");
	f = fopen("neuralNetwork_data/size.data", "w");
	fprintf(f, "%s\n", itoa);
	fclose(f);
	free(itoa);

}

/*!
 * \author pierre-olivier.rey
 * \brief Write all characters of the image at ImagePath in the f file. 
 * \param ImagePath Path of the example image.
 * \param example Path of the example file : where will the examples be writter.
 * \return the number of examples written
 */
int GenExample(char* ImagePath, char* text, FILE*f)
{
	List* l = Parcours(ImagePath);
	List*save  = l;
	int nbChar = 0;
	int i = 0;
	while(l)
	{
		if(text[i] == ' ') 
			i++; //to 'remove' space in the string, à optimiser
		if(text[i] > 'a' && text[i] < 'z') //letter 
		{
			fputc(text[i], f);
			fputc('\n', f);
			Matrix* m  = l->mat;
			fwrite(m->matrix, sizeof(double), m->size, f);
			fputc('\n', f);
			nbChar++;
		}
		l = l->next; //next element in l
		i++;
	}
	DeleteL(save);
	return nbChar;
}
