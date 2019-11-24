#include "../matrix/matrix.h"
#include "structNet.h"
#include "memory_handler.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "acti_fonction.h"




////////////////////// S I G M O I D E /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

double sigmoid(float x)
{	
	return (double) 1.0/(1.0 + exp(-x));
//	return log(1 + exp(x)); // relu soft plus
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



///////////////////////////////S O F T P R I M E //////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix* Softmax(Matrix *input)
{
	Matrix *output = InitM(input->line,input->col);
  	double sum = 0;
  	float value = 0;
	double softed_value = 0;
	double max;


	//Softmax fonction needs Sum of exp(z)k, zk is the k th values from input
	max = GetM(input,0,0);
	for(int j = 0; j<input->line; j++)
	{
		value = GetM(input,j,0);
		if(value>max)
			max = value;
		sum+=exp(value);

	}

	value = 0;
	

	//Output = appplying to each values the softmax fonction 
	for(int i = 0; i<input->col; i++)
	{
		for(int j = 0; j<input->line; j++)
		{
			value = GetM(input,j,i);
			softed_value = Soft(sum,value, max);
			PutM(output,j,i,softed_value);
			
		}
	}

	return output;

}

Matrix *softprime(Matrix *input)
{
  	Matrix *output = InitM(input->line,input->line);
  	double sum =0;
  	double value;
	double softed_value;
	double max = GetM(input,0,0);

	

  	//Softmax fonction needs Sum of exp(z)k, zk is the k th values from input)
  	
	for(int j=0; j< input->line; j++)
	{
		value = GetM(input,j,0);
		if(value>max)
			max = value;
		sum+= exp(value);
			
	}
 

	//Output = appplying to each values the soft fonction    
	for(int i=0; i < input->line; i++)
	{
		for(int j=0; j< input->line; j++)
		{
			if(i!=j)
			{
				value = GetM(input,j,0);
			
				softed_value = Soft_prime(sum, value, 0, max);
				PutM(output,i,j,softed_value);
			}
			else
			{	value = GetM(input,j,0);
				
				softed_value = Soft_prime(sum, value, 1,max);
				PutM(output,i,j,softed_value);
			}
		}
	}

       
        return Addition_soft(output);
	//return output;
}



Matrix* Addition_soft(Matrix* input)
{
	Matrix *output= InitM(input->line, 1);
	double result;

	for(int i=0; i <input->line; i++)
	{
		result=0;
		
		for(int j=0; j< input->col; j++)
		{
			
			//printf("%f  ", GetM(input,i,j));
			result+= GetM(input,i,j);
			
		}

		//printf("%f  \n",result);
		PutM(output,i,0,result);
		
	}

	FreeM(input);
	return output;
}

double Soft(double sum, double z, double shift)
{
   return exp(z-shift)/sum;
}

double Soft_prime(double sum, double z, int delta, double shift)
{

	return Soft(sum, z,shift)*(delta-Soft(sum,z,shift));
}
