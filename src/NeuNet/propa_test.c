#include "../matrix/matrix.h"
#include "structNet.h"
#include "memory_handler.h"
#include "acti_fonction.h"
#include <err.h>
#include <stdio.h>
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
///////////////////// FORWARD PROPAGATION /////////////////////////////////////


/**
 * \fn void forward_prop_actiTest(neuNet* network, Matrix *input_data, char fct)
 * \author jeanne.morin
 * \brief propagate value from the first layer to the last layer of the current network, using sigmoide as activation function for every layer
 * \param network : the network structure in which the values will be propagate.
 * \param input_data : the input given to the first layer of the current layer and that will be propagate in this network.
 * \param fct : activation function choosen. t for Tanh, s for Sigmoid and r for ReLU
 *
 */
//Calulate values and outputs
void forward_prop_actiTest(neuNet* network, Matrix *input_data, char fct)
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



///////////////////////////////////////////////////////// B A T C H  P R O P A //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \fn void backprop_batch_actiTest(neuNet *network, Matrix *expOutputs, char acti_fct)
 * \author jeanne.morin pierre-olivier.rey
 * \brief propagate the erros back from the last layer to the first layer without updating wieghts and biases.
 * \param network : the current network where the function will bakc propagate the errors.
 * \param expOutputs : the matrix expected as output of the network for the exemple given in input to the network.
 * \param acti_fct : activation function chosen. t for Tanh, s for Sigmoid and r for ReLU
 */
void backprop_batch_actiTest(neuNet *network, Matrix *expOutputs, char acti_fct)
{
	layer *ll =network->layers[network->nbLay -1]; //last layer
	layer *pl = network->layers[network->nbLay -2]; //precedant layer

	//dError
	Matrix *neg = MultScalM(expOutputs, -1);
	Matrix* minus = AddM(ll->outputs, neg);
	FreeM(neg);
	Matrix *sPrimeValues = (ActiPrime(ll->values, acti_fct));
	//updates errors martrix
	ll->errors = MultValM(sPrimeValues,minus);
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

