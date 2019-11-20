#include "structNet.h"
#include "tools.h"
#include "example_gen.h"
#include "../matrix/matrix.h"
#include "f_b_Propagation.h"
#include <stdlib.h>
#include <stdio.h>

void ShuffleArray(Matrix**a, size_t size)
{
	//TODO Il faut aussi randomize de la même manière les caracteres
	//IN NEEDS TO DEBUG
	for(size_t i = 0; i < size-1; i++)
	{
		size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
		Matrix* tmp = a[i];
		a[j] = a[i];
		a[i] = tmp;
	}
}	

Matrix* CreateExpected(char c)
{
	Matrix* m = InitM(26, 1);
	PutM(m, (int)(c - 'a'), 1, 1);
	return m;
}

Pool** CreateBatches(Pool* p, size_t batchSize)
{
//	ShuffleArray(p->examples, p->size);
	size_t batchNb = p->size/batchSize +1;
	Pool** batches = malloc(sizeof(Pool*) * batchNb); 
	size_t i = 0;
	while(i < batchNb-1)
	{
		Pool*batch = InitPool(batchSize);
		for(size_t j = 0; j < batchSize; j++)
		{
			*(batch->examples + j) = *(p->examples + i*batchSize +j);
			batch->results[j] = p->results[i*batchSize +j];
		}
		*(batches +i) = batch;
		i++;
	}
	i = batchSize*(batchNb-1);
	printf("%ld\n", i);
	Pool* lastBatch = InitPool(p->size - batchSize*(batchNb-1));	
	for(size_t j = 0; j < lastBatch->size; j++)
	{
		*(lastBatch->examples +j) = *(p->examples +i +j);
	}
	*(batches + batchNb-1) = lastBatch;	
	return batches; 
	
}


void Training(neuNet *n, int epoch, double learning_rate)
{
	int batchSize = 10; //Arbritrary value, needs of tests
	if(!fopen("neuralNetwork_data/examples.data", "r")) //file does not exist
		GenerateExamples("neuralNetwork_data/names.data");
	Pool* pool = ReadExamples("neuralNetwork_data/examples.data");
	for(int i = 0; i < epoch; i++)
	{
		Pool** batches = CreateBatches(pool, batchSize);
		for(size_t b = 0; b < pool->size/batchSize; b++)
		{
			for(size_t m  = 0; m < batches[b]->size; m++)
			{	
				Matrix* mat = batches[b]->examples[m];
				//DisplayM(mat);
				mat->col = 1;
				mat->line = 784; //resizing matrix according to expected format
								// for neuNet input matrix
				forward_prop(n, mat);
				Matrix* expected_out = CreateExpected(batches[b]->results[m]);
				backprop(n, 26, expected_out, learning_rate);
				/////UPDATE PONDEREE DES BIAIS/POIDS
				ClearNeuNet(n);
				FreeM(expected_out);
			}
		}
		printf("OCR gabriel\n");
		for(size_t i = 0; i < pool->size/batchSize+1; i++)
			FreePoolP(*(batches+i));
		free(batches);
		printf("epoch %d finished\n", i);
	}
//	FreePoolP(pool);
	FreePool(pool);
}

