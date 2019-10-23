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
      
      *(Layer->values) = *AddM(multiplication_weights,Layer->biases);
      *(Layer->outputs) = *Sig(Layer->values);

      FreeM(multiplication_weights);
      
}
	

Matrix* forward_prop(neuNet* network, Matrix* input_data)
{
	layer *current_layer;
	//DisplayM(network->layers[0]->values);
	
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
	FreeM(ll->errors);

	//updates errors martrix
	ll->errors = MultM(minus, sPrimeValues);
	FreeM(minus);
	FreeM(sPrimeValues);

	//Not optimal but easier to understand
	for(int i = network->nbLay-2; i > 0; i--) //gradient descent de l'avant dernier layer au deuxieme (a l'envers)
	{
	        
	        layer *cL = network->layers[i];	//current layer	
		layer *nL =network->layers[i+1];	//next layer


		Matrix *transpose = TransM(network->layers[i+1] -> weights);
     		Matrix *input_error = MultM(transpose,network->layers[i+1] -> errors); //si i+1 matrice pas multiple
	
        	transpose = TransM(network->layers[i-1]->outputs);
		Matrix *weights_error = MultM(network->layers[i+1]->errors,transpose);

        	//Current Layer.weights -=learning_rate * weights_error
		Matrix *weights_x_lrate = MultScalM(weights_error, -learning_rate);
        

		Matrix *copy = Copy_Entire_Matrix(cL->weights);
		//Update weights after erros calculs
		network->layers[i]->weights = AddM(copy,weights_x_lrate); //Matrice pas de la même taille dnc fonctionne pas


		//Current Layer.bias -= learning_rate * output_error
		Matrix *bias_x_lrate = MultScalM(network->layers[i+1]->errors, -learning_rate);
        
		copy = Copy_Entire_Matrix(cL->biases);
		//Updates biases after errors calcul 	
		network->layers[i]->biases = AddM(copy,bias_x_lrate);

		Matrix *sPrimeValues = SigPrime(cL->values);
		FreeM(cL->errors);

		//Matrice errors du current layer = wXe x sPrimeValues
		cL->errors = MultM(weights_error, sPrimeValues);
		

		FreeM(input_error);
		FreeM(weights_error);
		FreeM(weights_x_lrate);
		FreeM(transpose);
        
		FreeM(bias_x_lrate);
		FreeM(copy);
	}

	
}

/*
		//Crée une copie de la matrice weights de current lyaer		
		Matrix *trans = TransM(cL->weights);  

		//Multiplie l'erreur du layer suivant avec le poids du curent layer
		Matrix *wXe = MultM(nL -> errors, trans); //ATTENTION VALEUR INVERSE

		//Applique la dérivée de Sigmoide à values du current layer
		Matrix *sPrimeValues = SigPrime(cL->values);
		FreeM(cL->errors);

		//Matrice errors du current layer = wXe x sPrimeValues
		cL->errors = MultValM(wXe, sPrimeValues);
		FreeM(trans);
		FreeM(wXe);
		FreeM(sPrimeValues);	 
	}
	for(int i = 1; i < n->nbLay; i++) //Weights and bias correction
	{
	   	layer *cL = n->layers[i]; //current layer
		layer *pL = n->layers[i-1]; //previous layer

		Matrix *trans = TransM(pL->outputs);
		Matrix *eXo = MultM(trans,cL->errors); //ATTENTION VALEUR INVERSE faut vérifier les formules, il faut peut etre transposer

		Matrix *neg = MultScalM(eXo, -learningRate);
		Matrix *final = AddM(cL->weights, neg);
		FreeM(cL->weights);
	 	cL->weights = final;

		FreeM(trans);
		FreeM(eXo);
		FreeM(neg);
		FreeM(final);
//		cL->biases = AddM(cL.biases, MultScalM(cL.errors, -learningRate)); ancienne version mais memmory leaks
		neg = MultScalM(cL->errors, -learningRate);
		final = AddM(cL->biases, neg);
		FreeM(cL->biases);
		cL->biases = final;
		FreeM(final);
	}


}*/




