#include "../matrix/matrix.h"
#include "structNet.h"
#include "memory_handler.h"
#include "acti_fonction.h"
#include <err.h>
#include <stdio.h>
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
///////////////////// FORWARD PROPAGATION /////////////////////////////////////

//Calulate values and outputs
void layer_forward_propa(layer* Layer, Matrix *input_data)
{
      Matrix *multiplication_weights = MultM(Layer->weights,input_data);
      Layer->values = AddM(multiplication_weights,Layer->biases);
      Layer->outputs = Softmax(Layer->values);
//      DisplayM(Layer->outputs);
      FreeM(multiplication_weights);
}
	

Matrix* forward_prop(neuNet* network, Matrix* input_data)
{
	layer *current_layer;
	network->layers[0]->values = input_data;
	network->layers[0]->outputs = Softmax(network->layers[0]->values);  
  
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




///////////////////////////////////////////////////////////////////////////////
//////////////////////BACK PROPAGATION ///////////////////////////////////////

Matrix* Copy_Entire_Matrix(Matrix *m)
{
	Matrix *out = InitM(m->line, m->col);

	for(int i = 0; i < m->line; i++)
	{
		for(int j = 0; j < m->col; j++)
		{
			double value = GetM(m, i, j);
			PutM(out, i, j, value);
		}
	}

	return out;
}

void UpdateBW(neuNet * n, int curLay, float learning_rate)
{
	layer *cL = n->layers[curLay];	//current layer	
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

	Matrix *bXe = MultScalM(cL->errors, -learning_rate);        
	copy = Copy_Entire_Matrix(cL->biases);
	FreeM(cL->biases);
	cL->biases = AddM(copy, bXe);
	FreeM(bXe);
	FreeM(copy);
}


void backprop(neuNet *network, int len_output, Matrix *expOutputs, float learning_rate)
{
	layer *ll =network->layers[network->nbLay -1];

	//Check if len_output corresponds to the number of neurons of the last layer
	if(len_output != ll->nbNeurons)
	   errx(1,"Output are not of the correct length");

	//special case for last layer
	Matrix *neg = MultScalM(expOutputs, -1);
	Matrix* minus = AddM(ll->outputs, neg);
	FreeM(neg);

	Matrix *sPrimeValues = (softprime(ll->values));

	//updates errors martrix
	ll->errors = MultValM(minus, sPrimeValues);
	FreeM(minus);
	FreeM(sPrimeValues);
	UpdateBW(network, 2, learning_rate);
	//Not optimal but easier to understand
	for(int i = network->nbLay-2; i > 0; i--) 
	{	
		layer *cL = network->layers[i];	//current layer
		Matrix *transpose = TransM(network->layers[i+1] -> weights);
     	Matrix *wXE = MultM(transpose,network->layers[i+1] -> errors);
		Matrix *Sprime = softprime(cL->values);
		cL->errors = MultValM(Sprime, wXE);
		FreeM(transpose);
		FreeM(wXE);
		FreeM(Sprime);
		UpdateBW(network, i, learning_rate);
}

}

///////////////////////////////////////////////////////// B A T C H   P R O P A //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void batch_Propa(neuNet *network, Matrix *wanted_output, float learning_rate)
{
     //Matrix *save_acti = InitM(network->nbLay,Nbexemplees);
     //Matrix *save_errors = InitM(network->nbLay,Nbexemples);

     //TODO : SAVE LES VALEURS NECESSAIRES DANS UNE LISTE DE LISTE DE MATRICE ??
	 //NON je pense qu'il vaut mieux créer un nouveau champ dans la struct layer
}
	

void feedforward_batch(neuNet* network, Matrix* input_data, Matrix *save_acti, int step)
{
	layer *current_layer;
		
	network->layers[0]->values = input_data;
	network->layers[0]->outputs = Softmax(network->layers[0]->values);
	//	PutM(save_acti, 0,step, network->layer[0]->values);
	  
	//Propage the input values in every layers of the network
	for(int i = 1; i < network->nbLay; i++)
	  {
	    input_data = network->layers[i-1] -> outputs;
	    current_layer = network->layers[i];

	    //Calculate the values and input Matrix of the current layer
	    layer_forward_propa(current_layer,input_data);
	    
	    Matrix *multiplication_weights = MultM(current_layer->weights,input_data);
	    current_layer->values = AddM(multiplication_weights,current_layer->biases);
	    current_layer->outputs = Softmax(current_layer->values);


	    // PutM(save_acti,i,step,current_layer->outputs);
	    FreeM(multiplication_weights);
	    input_data = current_layer->outputs;
	    
	  }

	
}


void update_batch(neuNet * n, int nb_exemples, float learning_rate)
{
  for(int i =0; i<n->nbLay; i++)
    {
      //Sum Errors
      
    }
}


void backpropError_batch(neuNet *network, int step, Matrix *expOutputs, float learning_rate, Matrix* save_errors)
{
	layer *cl =network->layers[network->nbLay -1];

	//Check if len_output corresponds to the number of neurons of the last layer

	//special case for last layer
	Matrix *neg = MultScalM(expOutputs, -1);
	Matrix* minus = AddM(cl->outputs, neg);
	FreeM(neg);

	Matrix *sPrimeValues = (softprime(cl->values));

	//updates errors martrix
	cl->errors = MultValM(minus, sPrimeValues);
	FreeM(minus);
	FreeM(sPrimeValues);

	//PutM(save_errors,0,0,cl->errors);
	
	//Not optimal but easier to understand
	for(int i = network->nbLay-2; i > 0; i--) 
	{	
	    cl = network->layers[i];	//current layer
		Matrix *transpose = TransM(network->layers[i+1] -> weights);
		Matrix *wXE = MultM(transpose,network->layers[i+1] -> errors);
		Matrix *Sprime = softprime(cl->values);
		cl->errors = MultValM(Sprime, wXE);
		FreeM(transpose);
		FreeM(wXE);
		FreeM(Sprime);


		//	for(int j=0; j<cl->nbNeurons;j++)
		//{
		//  PutM(save_errors,i,step,cl->errors[j]
		//}
		
		
	}

}
