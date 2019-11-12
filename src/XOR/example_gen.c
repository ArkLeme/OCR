#include "../matrix/matrix.h"
#include <stdio.h>
#include <err.h>

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
Matrix** ReadExamples(char* path, char*results[])
{
	FILE*f = fopen(path, 'r');
	if(f == NULL)
		errx(1, "Example file cannot be opened");
	int exNb;
	fscanf(f, "%d", &exNb); //gets the total number of example in that file
	Matrix *examples[exNb] = malloc(sizeof(Matrix) * exNb);
	*results = malloc(sizeof(char) * exNb);
	//*results = (char*)malloc(sizeof(char) * exNb);

	char c;
	for(int i = 0; i < exNb; i++)
	{
		double*ch = malloc(sizeof(double) *784);
		c = (char) fgetc(f);
		fread(ch, sizeof(double), 784, f);
		Matrix *m = InitMWithValues(28, ch);
		examples[i] = m;
		*results[i] = c;
	}
	fclose(f);
	return &examples;
}

/*!
 * \author pierre-olivier.rey
 * \brief add all characters on the image situated at path to the example file
 * \param path Path of the example file, it is the string in the image.
 * \param example Path of the example file.
 */
void CreateNewExample(char* path, char* example)
{
	FILE f = fopen(example, 'a');
	if(f == NULL)
		errx(1, "Example file cannot be opened");
	List* matrix = first_segmentation(path);
	Matrix* m = matrix->mat;
	int i = 0;
	while(m != NULL)
	{
		char c = path[i];
		fputc(c, f);
		fwrite(m->matrix, sizeof(double), m->size, f);
		FreeM(m);
		matrix = RemoveFL(matrix);
		m = matrix->mat;
	}
	fclose(f);
}
