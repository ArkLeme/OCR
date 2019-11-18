#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

void ClearNeuNet(neuNet *n)
{
	layer* cL = n->layers[0];
	FreeM(cL->values);
  	FreeM(cL->outputs);
	for(int i = 1; i < n->nbLay; i++)
	{
		layer* cL = n->layers[i];
  		FreeM(cL->values);
  		FreeM(cL->outputs);
  		FreeM(cL->errors);
	}
}


void freeNeuNet(neuNet *n)
{
	//free first layer
	layer* fL = n->layers[0];
	FreeM(fL->biases);
	FreeM(fL->weights);
	free(fL);
	for(int i = 1; i < n->nbLay; i ++)
		Freelayer(n->layers[i]);
	free(n);
}

void Freelayer(layer *cL)
{
  	FreeM(cL->biases);
  	FreeM(cL->weights);
	free(cL);
}

void SaveNeuNet(neuNet *n)
{
	FILE *p;
	p = fopen("network", "w");
	if(p == NULL)
	{
		//errx("File can't be created");
	}
	fprintf(p, "%i\n", n->nbLay);	
	for(int i = 0;i < n->nbLay; i++)
	{
		fprintf(p, "%i\n", n->layers[i]->nbNeurons);
	}
	for(int i = 0; i < n->nbLay; i++)
	{
		layer* cL = n->layers[i];
		for(int j = 0; j < cL->weights->size; j++)
		{
			fprintf(p,"%f\n", GetPosM(cL->weights, j));
		}
	}
	fclose(p);
}

void LoadNeuNet()
{
	FILE *p = fopen("network", "r");
	if(p == NULL)
	{
		//errx("File can't be created");
	}
	
		
}

double sigmoid(float x)
{	
	return (double) 1.0/(1.0 + exp(-x));
	//return log(1 + exp(x)); // relu soft plus
	//return (exp(2*x) - 1)/(exp(2*x) + 1);
}

double sigPrime(float x)
{
	return sigmoid(x)*(1-sigmoid(x));
	//return 1/(1+exp(-x)); //relu prime
	//return 1- ( sigmoid( x)* sigmoid( x));
}

Matrix* Sig(Matrix *m)
{
	Matrix* m2 = InitM(m->line, m->col);
	for(int i = 0; i < m->line; i++)
	{
		for( int j = 0; j < m->col; j++)
			PutM(m2, i, j, sigmoid(GetM(m,i, j)));
	}
	return m2;
}

Matrix* SigPrime(Matrix *m)
{
	Matrix* m2 = InitM(m->line, m->col);
	for(int i = 0; i < m->line; i++)
	{
		for( int j = 0; j < m->col; j++)
			PutM(m2, i, j, sigPrime(GetM(m,i, j)));
	}
	return m2;
}

//Fonction softmax for layer
Matrix *softmax(Matrix *input)
{
  	Matrix *output = InitM(input->line,input->col);
  	double sum = 0;
  	float value = 0;


  	//Softmax fonction needs Sum of exp(z)k, zk is the k th values from input
  	for(int i=0; i <input->line; i++)
	{
		for(int j=0; j< input->col; j++)
		{
			value = GetM(input,i,j);
			sum+= exp(value);
		}
	}
     

   	//Output = appplying to each values the softmax fonction    
	for(int i=0; i < input->line; i++)
	{
		for(int j=0; j< input->col; j++)
		{
			value = Soft(sum, GetM(input,i,j));
			PutM(output,i,j,value);
		}
	}

       
       return output;
}

Matrix *softprime(Matrix *input)
{
  	Matrix *output = InitM(input->line,input->col);
  	double sum =0;
  	double value;
	double value2;

  	//Softmax fonction needs Sum of exp(z)k, zk is the k th values from input)
  	for(int i=0; i <input->line; i++)
	{
		for(int j=0; j< input->col; j++)
		{
			value = GetM(input,i,j);
			sum+= exp(value);
		}
	}
     

	value2 = Soft(sum, GetM(input,input->line-1,input->col-1));
   	//Output = appplying to each values the softmax fonction    
	for(int i=0; i < input->line; i++)
	{
		for(int j=0; j< input->col; j++)
		{
			if((i+1)*(j+1) == (input->col)*(input->line))
			{
				value = Soft_prime(sum, GetM(input,i,j));
				PutM(output,i,j,value);
			}
			else
			{	value = Soft(sum, GetM(input,i,j));
				PutM(output,i,j,0);
			}
		}
	}

       
       return output;
}
double Soft(double sum, float z)
{
   return exp(z)/sum;
}

double Soft_prime(double sum, float z)
{

	return Soft(sum, z)*(1-Soft(sum,z));
}

Pool* InitPool(size_t size)
{
	Pool *p = malloc(sizeof(Pool));
	p->size = size;
	p->examples = malloc(sizeof(Matrix*) * size);
	//*p->examples = malloc(sizeof(Matrix) * size);
	p->results = malloc(sizeof(char) * size);
	return p;
}

void FreePool(Pool*p)
{
	for(size_t i = 0; i < p->size; i++)
	{
		DisplayM(*(p->examples+i));
		FreeM(*(p->examples+i));
	}
	//free(*(p->examples));
	free(p->examples);
	free(p->results);
	free(p);
}

