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

Matrix* Acti(Matrix *m, char fct)
{
	Matrix* m2 = InitM(m->line, m->col);
	if(fct == "s")
	  {
	    for(int i = 0; i < m->line; i++)
	      {
		for( int j = 0; j < m->col; j++)
		  {PutM(m2, i, j, sigmoid(GetM(m,i, j)));}
	      }
	  }
	else if(fct == "t")
	  {
	    for(int i = 0; i < m->line; i++)
	      {
		for( int j = 0; j < m->col; j++)
		  {PutM(m2, i, j, tan(GetM(m,i, j)));}
	      }
	  }
	else if(fct == "r")
	  {
	    for(int i = 0; i < m->line; i++)
	      {
		for( int j = 0; j < m->col; j++)
		  {PutM(m2, i, j, reLU(GetM(m,i, j)));}
	      }
	  }

	return m2;
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


/*!
 * \author jeanne.morin
 * \brief Calcul softmax for each component of the matrix input.
 * \param  input, the matrix use by softmax.
 * \return Matrix(input->line,input->col).
 */
Matrix* Softmax(Matrix *input)
{
	Matrix *output = InitM(input->line,input->col);
  	double sum = 0;
  	double value = 0;
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
			softed_value = Soft(sum,value, 0);
			PutM(output,j,i,softed_value);
			
		}
	}

	sum=0;

	return output;

}


/*!
 * \author jeanne.morin
 * \brief calculate softmax derivative of  given matrix
 * \param input, Matrix that will be use as parameter for softmax derivative
 * \return Matrix(input->line,input->line), softmax derivative
 */
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

       
        //return Addition_soft(output);
	return output;
}


/*!
 * \author jeanne.morin
 * \brief apply Softmax function to a single value
 * \param sum summarizes exponential function of every component of a vector.
 * \param z element softmax will be applied to.
 * \param shift the maximum value of the component from a vector.
 * \return double Softmax applied to z.
 */
double Soft(double sum, double z, double shift)
{
   return exp(z-shift)/sum;

}

/*!
 * \author jeanne.morin
 * \brief apply Softmax derivate function to a single value
 * \param sum summarizes exponential function of every component of the vector.
 * \param z element softmax derivate will be applied to.
 * \param shift the maximum value of the component from the vector.
 * \param delta 1 or 0 depanding on the derivate case this element represents.
 * \return double Softmax derivates applied to z.
 */

double Soft_prime(double sum, double z, int delta, double shift)
{

	return Soft(sum, z,shift)*(delta-Soft(sum,z,shift));
}


//////////////////////////////////////////////////// T A N G E A N T E  E X P O N E N T I E L L E //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


double tan(double x)
{	
        return (double) sinh(x)/cosh(x);
        //return log(1 + exp(x)); // relu soft plus
	//return (exp(2*x) - 1)/(exp(2*x) + 1);
}

double tanPrime(double x)
{
        return 1/cosh(x)*cosh(x);
	//return 1/(1+exp(-x)); //relu prime
	//return 1- ( sigmoid( x)* sigmoid( x));
}

////////////////////////////////////////////////////////////// R E L U ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double ReLU(double x)
{
        if(x<0)
	  {
	    x =0;
	  }	
    
        return (double) x;
        
}

double ReLU_prime(double x)
{
	if(x<0)
	  return 0;

	return 1;
}



 
