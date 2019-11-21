#ifndef EXAMPLE_GEN_H
#define EXAMPLE_GEN_H

#include "../matrix/matrix.h"
#include "structNet.h"
#include <stdio.h>

Pool* ReadExamples(char* path);
void GenerateExamples(char* path);
int GenExample(char*path, char* text, FILE*f);

#endif
