#ifndef  STRUCTNET_H
#define  STRUCTNET_H
#include "../matrix/matrix.h"
typedef struct layer{
	Matrix *biases; //biases of this layer (size: 1*nbNeurons)
	Matrix *values; //values of this layer (size: 1*nbNeurons)
	Matrix *outputs; //outputs of this layer (size: 1*nbNeurons)
					// equal to sigmoid(values)
	Matrix *weights; // weights going into this layer
					// size: nbNeurons*layers[currentLayer-1].nbNeurons
	Matrix *errors; //size : 1*n	
	Matrix* test;
	int nbNeurons; //numbers of neurons in this layer 
} layer;

typedef struct neuNet{
	int nbLay; //number of layers
	layer *layers[3]; //list of structs layer, constists of layers of this neuNet
} neuNet;

#endif
