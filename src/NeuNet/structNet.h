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

	Matrix *weight_batch; /*<Compute errors and outputs of the layer, for all exemple of a batch; size: nbNeurons*layers[currentLayer-1]->nbNeurons*/
	Matrix *biases_batch; /*<Sum errors of the layer for each exemple of the batch; size: nbNeurons*1*/
	
	int nbNeurons; /*!<Numbers of neurons in this layer. */ 
}layer;

/*!
 * \struct neuNet structNet.h
 * \brief Structure of the neural network.
 * Main strucutre of the neural network.
 */
typedef struct neuNet{
	int nbLay; /*!<Number of layers*/
	layer *layers[3]; /*!<List of structs layer, consists of layers of this neuNet. Currently at 3, it should use an FAM to represent any kind of neural network.*/
} neuNet;
/*!
 * \struct Pool structNet.h
 * \brief Structure to handle examples to train the network.
 * Contains 2 matrix that are containes examples used to train the network.
 * matrix at examples[i] correspond to the char at results[i].
 */
typedef struct Pool{
	size_t size; /*!<Number of example this pool contains */
	Matrix** examples; /*!<Array of pointers to matrix of char. Has size element.*/
	char* results; /*!<Array of char.*/
} Pool;
#endif
