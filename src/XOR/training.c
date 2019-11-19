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
	for(size_t i = 0; i < size-1; i++)
	{
		size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
		Matrix* tmp = a[i];
		a[j] = a[i];
		a[i] = tmp;
	}
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


void Training(neuNet *n)
{
	int batchSize = 10; //Arbritrary value, needs of tests
	GenerateExamples("neuralNetwork_data/names.data");
	Pool* pool = ReadExamples("neuralNetwork_data/examples.data");
	Pool** batches = CreateBatches(pool, batchSize);
	for(size_t b = 0; b< pool->size/batchSize; b++)
	{
		for(size_t m  = 0; m < batches[b]->size; m++)
		{	DisplayM(batches[b]->examples[m]);
		}
	}
	printf("OCR gabriel\n");
	for(size_t i = 0; i < pool->size/batchSize+1; i++)
		FreePool(*(batches+i));
	free(batches);
	FreePoolP(pool);
	//FreePool(pool);
}

//train network with output_data and given output wanted
void train(neuNet *Network,int steps,float learning_rate)
{
	int inp[4][2] = {{0,0},{1,1},{0,1},{1,0}};
	int res[4] = {0,0,1,1};
  	for (int i =0; i<steps; i++)
  	{
		int index = i %4;
		int j = inp[index][0];
		int k = inp[index][1];
		Matrix* input = InitM(2,1);
		PutM(input, 0,0,j);
		PutM(input,1,0,k);
		Matrix* out = InitM(1,1);
		PutM(out, 0,0,res[index]);
		forward_prop(Network, input);
		printf("%d xor %d = %f\t%d\n", j, k, GetM(Network->layers[2]->outputs,0,0), i);
		backprop(Network, 1, out, learning_rate);
		ClearNeuNet(Network);
		FreeM(out);
    }
}


