#ifndef MEMORY_HANDLER_H
#define MEMORY_HANDLER_H
#include "structNet.h"
#include "../matrix/matrix.h"


void ClearNeuNet(neuNet*n);
void freeNeuNet(neuNet* n);

Pool* InitPool(size_t size);
void FreePool(Pool*p);
void FreePoolP(Pool*p);

#endif
