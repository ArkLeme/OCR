#include <stdio.h>
#include <stdlib.h>
#include "../matrix/matrix.h"

/**
 * \file resize_char.c
 * \brief Resize char with bilinear interpolation algorithm
 * \author Alexandre.L
 */ 

double entire_part(double elt)
{
	int i = 0;
	while(!(i <= elt && i + 1 > elt))
	{
		i++;
	}
	return i;
}

/**
 * \fn resize_char(Matrix *m)
 * \brief Resize char with bilinear interpolation algorithm
 * \param Matrix *m : Matrix to resize.
 */

Matrix* resize_char(Matrix *m)
{
	int width;
	int height;
	if (m->line > m->col)
	{
		height = 28;
		width = (int) (m->col * (height/(double)m->line));
	}
	else
	{
		width = 28;
		height = (int) (m->line * (width/(double)m->col));
	}

	Matrix *resize_m = InitM(height,width);

	double x, y, x1, y1, x2, y2;
	double area1, area2, area3, area4;
	double delta1, delta2, delta3, delta4;

	for(int i = 0; i < height; i ++)
	{
		for (int j = 0; j < width; j ++)
		{
			x = j * m->col/width;
			y = i * m->line/height;

			x1 = entire_part(x);
			y1 = entire_part(y);

			if(x1 == m->col-1) x2 = m->col-1;
			else x2 = x1 +1;
			if(y1 == m->line-1) y2 = m->line -1;
			else y2 = y1 +1;

			area1 = (x-x1) * (y-y1);
			area2 = ((x1+1)-x) * (y-y1);
			area3 = (x-x1) * ((y1+1)-y);
			area4 = ((x1+1)-x) * ((y1+1)-y);

			area1 = area1 < 0 ? -area1 : area1;
			area2 = area2 < 0 ? -area2 : area2;
			area3 = area3 < 0 ? -area3 : area3;
			area4 = area4 < 0 ? -area4 : area4;

			delta1 = GetM(m,y1,x1) * area4;
			delta2 = GetM(m,y2,x2) * area1;
			delta3 = GetM(m,y1,x2) * area2;
			delta4 = GetM(m,y2,x1) * area3;

			double value = delta1+delta2+delta3+delta4 > 0.5;
			PutM(resize_m,i,j,value);

		}
	}
	Matrix *output = InitM(28,28);
	for (int i = 0; i < height ; i++)
	{
		for (int j = 0; j < width ; j++)
		{
			PutM(output,i,j,GetM(resize_m,i,j)!=0);
		}
	}
	return output;
}

