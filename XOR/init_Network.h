#ifndef INIT_NETWORK_H
#define INIT_NETWORK_H
#include "structNet.h"

neuNet* init_network(int layers_size[], size_t nbLayers);
layer *init_layer(int nbNeurones,int nbNeurones_prec);
void InitBW(Matrix *m1);
int random_int(int max_value);
void Init_biases_weigths(layer *Layer, layer *prec_layer);

#endif
