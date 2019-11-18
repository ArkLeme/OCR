/*!
 * \file structNet.h
 * \brief Structures to represent a neural network.
 * \author jeanne.morin pierre-olivier.rey
 *
 * Layer and neuNet structures to represent a neural network.
 */
#ifndef  STRUCTNET_H
#define  STRUCTNET_H
#include "../matrix/matrix.h"
#include <stdlib.h>
/*!
 * \struct layer structNet.h
 * \brief Structure for a neural Network Layer
 *
 * Layer is used to represent a layer of a neural Network.
 * It can represent any type of layer (input, hidden or output).
 * All matrixes contain "double".
 */
typedef struct layer{
	Matrix *biases; /*!<Biases of this layer ; size: nbNeurons*1*/
	Matrix *values; /*!<Values of this layer ; size: nbNeurons*1*/
	Matrix *outputs; /*!<Outputs of this layer: equal to sigmoid(values) ; size: nbNeurons*1*/
	Matrix *weights; /*!Weights going into this layer ; size: nbNeurons*layers[currentLayer-1]->nbNeurons*/
	Matrix *errors; /*!<Used in backpropagation algorithm ; size : nbNeurons*1*/
	int nbNeurons; /*!<Numbers of neurons in this layer. */ 
} layer;

/*!
 * \struct neuNet structNet.h
 * \brief Structure of the neural network.
 * Main strucutre of the neural network.
 */
typedef struct neuNet{
	int nbLay; /*!<Number of layers*/
	layer *layers[3]; /*!<List of structs layer, consists of layers of this neuNet. Currently at 3, it should use an FAM to represent any kind of neural network.*/
} neuNet;

typedef struct Pool{
	size_t size;
	Matrix** examples;
	char* results;
} Pool;
#endif
