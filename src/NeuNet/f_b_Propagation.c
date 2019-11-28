#include "../matrix/matrix.h"
#include "structNet.h"
#include "memory_handler.h"
#include "acti_fonction.h"
#include <err.h>
#include <stdio.h>
#include <math.h>
#include "cross_entropy.h"

////////////////////////////////////////////////////////////////////////////////
///////////////////// FORWARD PROPAGATION /////////////////////////////////////


/*!
 * \author jeanne.morin
 * \brief propagate value from the first layer to the last layer of the current network, using sigmoide as activation function for every layer
 * \param network is the network structure in which the values will be propagate.
 * \param input_data is the input given to the first layer of the current layer and that will be propagate in this network.
 *
 */


//Calulate values and outputs
void forward_prop_actiTest(neuNet* network, Matrix *input_data, char fct[])
{
        layer *current_layer;

	network->layers[0]->values = input_data;
	network->layers[0]->outputs = Acti(network->layers[0]->values,fct);
	
	//Propage the input values in every layers of the network
	for(int i = 1; i < network->nbLay; i++)
	  {
	    	input_data = network->layers[i-1] -> outputs;
	    	current_layer = network->layers[i];

	    	//Calculate the values and input Matrix of the current layer
	    	Matrix *multiplication_weights = MultM(current_layer->weights,input_data);
	    	current_layer->values = AddM(multiplication_weights,current_layer->biases);
	    	current_layer->outputs = Acti(current_layer->values,fct);

	    	FreeM(multiplication_weights);
	    	input_data = current_layer->outputs;
	  		
		   	current_layer->errors = NULL; //needed if it is only 
	  }
}

/*!
 * \author jeanne.morin
 * \brief propagate value from the first layer to the last layer of the current network, using softmax as activation fonction for the last Layer
 * \param network is the network structure in which the values will be propagate.
 * \param input_data is the input given to the first layer of the current layer and that will be propagate in this network.
 */
//Calulate values and outputs
void forward_prop(neuNet* network, Matrix *input_data)
{
    	layer *current_layer;
	int i =0;
	
	//Layer number 0
	network->layers[i]->values = input_data;
	network->layers[i]->outputs = Sig(network->layers[0]->values);
	
	i+=1;
	//Propage the input values in every layers of the network, startin from layer 1
	while(i<network->nbLay-1)
	//for(int i = 1; i < network->nbLay-1; i++)
	  {
	    	input_data = network->layers[i-1] -> outputs;
	    	current_layer = network->layers[i];

	    	//Calculate the values and input Matrix of the current layer
	    	Matrix *multiplication_weights = MultM(current_layer->weights,input_data);
	    	current_layer->values = AddM(multiplication_weights,current_layer->biases);
	    	current_layer->outputs = Sig(current_layer->values);

	    	FreeM(multiplication_weights);
	    	input_data = current_layer->outputs;
	  		
		current_layer->errors = NULL; //needed if it is only 
		i+=1;
	  }

		

		input_data = network->layers[i-1] -> outputs;
	    	current_layer = network->layers[i];

	    	//Calculate the values and input Matrix of the current layer
	    	Matrix *multiplication_weights = MultM(current_layer->weights,input_data);
	    	current_layer->values = AddM(multiplication_weights,current_layer->biases);
	    	current_layer->outputs = Softmax(current_layer->values);
		

	    	FreeM(multiplication_weights);
	    	input_data = current_layer->outputs;
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

	Matrix *sPrimeValues = (SigPrime(ll->values));

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
		Matrix *Sprime = SigPrime(cL->values);
		cL->errors = MultValM(Sprime, wXE);
		FreeM(transpose);
		FreeM(wXE);
		FreeM(Sprime);
		UpdateBW(network, i, learning_rate);
}

}

///////////////////////////////////////////////////////// B A T C OPA //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	


/*!
 * \author jeanne.morin
 * \brief update the wieghts and biases of the network
 * \param network is the current network the funtion will work in.
 * \param learning_rate is the learning rate used to calculate erros of a layer.
 * \param batchSize is the number of element in the batch used.
 */
void FinalUpdate_batch(neuNet *network, float learning_rate, int batchSize)
{
	layer *cl;
	double coef = -(learning_rate)/batchSize;
	for(int i=1; i<network->nbLay;i++)	
	{
		cl = network->layers[i];
		MultScalMP(cl->weight_batch,coef);
		Add_OptiM(cl->weights,cl->weight_batch); //update poids
		
		MultScalMP(cl->biases_batch,coef);
		Add_OptiM(cl->biases,cl->biases_batch);//update biases

	}
}


/*!
 * \author jeanne.morin pierre-olivier.rey
 * \brief propagate the erros back from the last layer to the first layer without updating wieghts and biases.
 * \param network is the current network where the function will bakc propagate the errors.
 * \param expOutputs is the matrix expected as output of the network for the exemple given in input to the network.
 */

void backprop_batch(neuNet *network, Matrix *expOutputs)
{
	layer *ll =network->layers[network->nbLay -1]; //last layer
	layer *pl = network->layers[network->nbLay -2]; //precedant layer
	
	//dError
	Matrix *neg = MultScalM(expOutputs, -1);
	Matrix* minus = AddM(ll->outputs, neg);
	FreeM(neg);
	Matrix *sPrimeValues = (softprime(ll->values));
	//updates errors martrix
	ll->errors = MultM(sPrimeValues,minus);
	FreeM(sPrimeValues);
	FreeM(minus);

	//cross entropy OK
	/*Matrix *ln = LogM(ll->outputs);
	Add_OptiM(ln,expOutputs);
	DisplayM(ln);
	Matrix *neg = MultScalM(ln, -1);
	FreeM(ln);
	ll->errors = neg;
	FreeM(neg);*/

		
	//Update Sum of Errors and Erros*Output(layer-1)
	Matrix* transpose_out = TransM(pl->outputs);
	//printf("col = %i",pl->outputs->col);
	//printf("line = %i", pl->outputs->line);
	
	//DisplayM(transpose_out);
	Matrix *update = MultM(ll->errors,transpose_out);
	Add_OptiM(ll->weight_batch, update);
	Add_OptiM(ll->biases_batch,ll->errors);
	FreeM(update);
	FreeM(transpose_out);
	
	for(int i = network->nbLay-2; i > 0; i--) 
	{	
    	layer *cl = network->layers[i];   //current layer
		pl = network->layers[i-1];
		Matrix *transpose = TransM(network->layers[i+1] -> weights);
		Matrix *wXE = MultM(transpose,network->layers[i+1] -> errors);
		Matrix *Sprime = SigPrime(cl->values);
		cl->errors = MultValM(Sprime, wXE);
		FreeM(transpose);
		FreeM(wXE);
		FreeM(Sprime);

		Matrix* transpose_bis = TransM(pl->outputs);
		Matrix *update = MultM(cl->errors,transpose_bis);
		Add_OptiM(cl->weight_batch,update);
		Add_OptiM(cl->biases_batch,cl->errors);
		
		FreeM(update);
		FreeM(transpose_bis);
	}
}


void backprop_batch_actiTest(neuNet *network, Matrix *expOutputs, char acti_fct)
{
	layer *ll =network->layers[network->nbLay -1]; //last layer
	layer *pl = network->layers[network->nbLay -2]; //precedant layer
	
	//dError
	Matrix *neg = MultScalM(expOutputs, -1);
	Matrix* minus = AddM(ll->outputs, neg);
	FreeM(neg);
	Matrix *sPrimeValues = (actiPrime(ll->values, acti_fct));
	//updates errors martrix
	ll->errors = MultM(sPrimeValues,minus);
	FreeM(sPrimeValues);
	FreeM(minus);
		
	//Update Sum of Errors and Erros*Output(layer-1)
	Matrix* transpose_out = TransM(pl->outputs);
		
	//DisplayM(transpose_out);
	Matrix *update = MultM(ll->errors,transpose_out);
	Add_OptiM(ll->weight_batch, update);
	Add_OptiM(ll->biases_batch,ll->errors);
	FreeM(update);
	FreeM(transpose_out);
	
	for(int i = network->nbLay-2; i > 0; i--) 
	{	
    	layer *cl = network->layers[i];   //current layer
		pl = network->layers[i-1];
		Matrix *transpose = TransM(network->layers[i+1] -> weights);
		Matrix *wXE = MultM(transpose,network->layers[i+1] -> errors);
		Matrix *Sprime = ActiPrime(cl->values, acti_fct);
		cl->errors = MultValM(Sprime, wXE);
		FreeM(transpose);
		FreeM(wXE);
		FreeM(Sprime);

		Matrix* transpose_bis = TransM(pl->outputs);
		Matrix *update = MultM(cl->errors,transpose_bis);
		Add_OptiM(cl->weight_batch,update);
		Add_OptiM(cl->biases_batch,cl->errors);
		
		FreeM(update);
		FreeM(transpose_bis);
	}
}
