#include "../matrix/matrix.h"
#include "structNet.h"
#include "tools.h"
#include <err.h>
#include <stdio.h>
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
///////////////////// FORWARD PROPAGATION /////////////////////////////////////

//Calulate values and outputs
void layer_forward_propa(layer* Layer, Matrix *input_data)
{
      Matrix *multiplication_weights = MultM(Layer->weights,input_data); //ATTENTION VALEUR INVERSE
      //FreeM(Layer->values);
      Layer->values = AddM(multiplication_weights,Layer->biases);
	  //FreeM(Layer->outputs);
      Layer->outputs = Sig(Layer->values);

      FreeM(multiplication_weights);
      
}
	

Matrix* forward_prop(neuNet* network, Matrix* input_data)
{
	layer *current_layer;
	//DisplayM(network->layers[0]->values);
	//FreeM(network->layers[0]->values);
	//FreeM(network->layers[0]->outputs);
	network->layers[0]->values = input_data;
	network->layers[0]->outputs = Sig(network->layers[0]->values);  
  
  //Propage the input values in every layers of the network
  for(int i = 1; i < network->nbLay; i++)
    {
      input_data = network->layers[i-1] -> outputs;
      current_layer = network->layers[i];


      //Calculate the values and input Matrix of the current layer
      layer_forward_propa(current_layer,input_data);
      input_data = current_layer->outputs;
    }  

  return input_data;
  
}



//Fonction softmax for layer
/*Matrix softmax(layer Layer, Matrix input)
{
  Layer.output = InitM(1,input.col);
  int sum =0;

  //Softmax fonction needs Sum of exp(z)k, zk is the k th values from input)
  for(int sum_index = 0;  sum_index < input.col; sum_index++)
	 {
	    sum+= exp(GetM(input, 1, sum_index);
	 }
     

   //Output = appplying to each values the softmax fonction 
   for(int j = 0; j < input.col; j++)
     {    
       PutM(Layer.output, 1,j , exp(GetM(input, 1, j)) / sum );
     }
       
       
       return Layer.output;
       }*/



///////////////////////////////////////////////////////////////////////////////
//////////////////////BACK PROPAGATION ///////////////////////////////////////


Matrix* Copy_Entire_Matrix(Matrix *m)
{
	Matrix *out = InitM(m->line, m->col);

	for(int i = 0; i < m->line; i++)
	{
		for(int j = 0; j < m->col; j++)
		{
			int value = GetM(m, i, j);
			PutM(out, i, j, value);
		}
	}

	return out;
}

void UpdateBW(neuNet * n, int curLay, float learning_rate)
{
	layer *cL = n->layers[curLay];	//current layer	
		//layer *nL =n->layers[curLay+1];	//next layer


        Matrix *transpose = TransM(n->layers[curLay-1]->outputs);
		Matrix *eXo = MultM(cL->errors,transpose);
		Matrix *delta = MultScalM(eXo, -learning_rate);
		Matrix *copy = Copy_Entire_Matrix(cL->weights);
		FreeM(cL->weights);
		cL->weights = AddM(copy, delta);
		FreeM(eXo);
		FreeM(transpose);
		FreeM(delta);
		FreeM(copy);


		//Current Layer.bias -= learning_rate * output_error
		Matrix *bXe = MultScalM(cL->errors, -learning_rate);        
		copy = Copy_Entire_Matrix(cL->biases);
		FreeM(cL->biases);
		cL->biases = AddM(copy, bXe);
		FreeM(bXe);
		FreeM(copy);
}


void backprop(neuNet *network, int len_output, Matrix *expOutputs, float learning_rate)
{
	//Last layer case
        layer *ll =network->layers[network->nbLay -1];


	//Check if len_output corresponds to the number of neurons of the last layer
	if(len_output != ll->nbNeurons)
	   errx(1,"Output are not of the correct length");



	//special case for last layer
	Matrix *neg = MultScalM(expOutputs, -1);
	Matrix* minus = AddM(ll->outputs, neg);
	FreeM(neg);

	Matrix *sPrimeValues = (SigPrime(ll->values));

	//FreeM(ll->errors);
	//updates errors martrix
	ll->errors = MultValM(minus, sPrimeValues);
	FreeM(minus);
	FreeM(sPrimeValues);
	UpdateBW(network, 2, learning_rate);
	//Not optimal but easier to understand
	for(int i = network->nbLay-2; i > 0; i--) //gradient descent de l'avant dernier layer au deuxieme (a l'envers)
	{	
			layer *cL = network->layers[i];	//current layer	
		//layer *nL =network->layers[i+1];	//next layer
		Matrix *transpose = TransM(network->layers[i+1] -> weights);
     	Matrix *wXE = MultM(transpose,network->layers[i+1] -> errors); //si i+1 matrice pas multiple
		Matrix *Sprime = SigPrime(cL->values);
		//FreeM(cL->errors);
		cL->errors = MultValM(Sprime, wXE);
		FreeM(transpose);
		FreeM(wXE);
		FreeM(Sprime);
		UpdateBW(network, i, learning_rate);
	}

	
}
