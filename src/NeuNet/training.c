#include "structNet.h"
#include "memory_handler.h"
#include "example_gen.h"
#include "../matrix/matrix.h"
#include "f_b_Propagation.h"
#include <stdlib.h>
#include <stdio.h>

void ShufflePool(Pool*p)
{
	for(size_t i = 0; i < p->size; i++)
	{
		size_t j = rand() % p->size;
		Matrix* tmp = p->examples[i];
		char temp = p->results[i];
		p->results[i] = p->results[j];
		p->results[j] = temp;
		p->examples[i] = p->examples[j];
		p->examples[j] = tmp;
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
	ShufflePool(p);
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
	Pool* lastBatch = InitPool(p->size - batchSize*(batchNb-1));	
	for(size_t j = 0; j < lastBatch->size; j++)
	{
		*(lastBatch->examples +j) = *(p->examples +i +j);
		lastBatch->results[j] = p->results[i+j];
	}
	*(batches + batchNb-1) = lastBatch;
	return batches; 
}


void Training(neuNet *n, int epoch, double learning_rate)
{
	int batchSize = 10; //Arbritrary value, needs of tests
//	if(!fopen("neuralNetwork_data/examples.data", "r")) //file does not exist
		GenerateExamples("neuralNetwork_data/names.data");
	Pool* pool = ReadExamples("neuralNetwork_data/examples.data");
	for(int i = 0; i < epoch; i++)
	{
		Pool** batches = CreateBatches(pool, batchSize);
		for(size_t b = 0; b < pool->size/batchSize +1; b++)
		{
			for(size_t m  = 0; m < batches[b]->size; m++)
			{	
				Matrix* mat = batches[b]->examples[m];
				mat->col = 1;
				mat->line = 784; //resizing matrix according to expected format
								// for neuNet input matrix
				forward_prop(n, mat);
				Matrix* expected_out = CreateExpected(batches[b]->results[m]);
				backprop_batch(n, 26, expected_out, learning_rate);
				ClearNeuNet(n);
				FreeM(expected_out);
				mat->col = 28;
				mat->line = 28; 
				printf("%c", (batches[b]->results[m]));
			}
			FinalUpdate_batch(n,learning_rate, epoch);
			printf(" %li\n", batches[b]->size);
		}
		for(size_t i = 0; i < pool->size/batchSize+1; i++)
			FreePoolP(*(batches+i));
		free(batches);
		printf("\nepoch %i finished\n", i);
	}
//	FreePoolP(pool);
	FreePool(pool);
}

