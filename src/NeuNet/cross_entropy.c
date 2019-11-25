#include "../matrix/matrix.h"
#include "structNet.h"
#include "memory_handler.h"
#include "acti_fonction.h"
#include <err.h>
#include <stdio.h>
#include <math.h>



Matrix *LogM(Matrix* input)
{
  double value;
	Matrix *output = InitM(input->line,input->col);
  for(int i = 0; i< input->col; i++)
    {
      for(int j=0; j<input->line; j++)
	{
	  value = GetM(input,j,i);
	  value = log(value);
	  
	  PutM(output,j,i,value);
	}
    }

  return output;
}
