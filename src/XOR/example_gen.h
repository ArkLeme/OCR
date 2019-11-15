#ifndef EXAMPLE_GEN_H
#define EXAMPLE_GEN_H

#include "../matrix/matrix.h"

Matrix* ReadExamples(char* path, char* results);
void GenerateExamples(char* path);
void GenExample(char*path, char* text);

#endif
