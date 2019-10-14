#include "xy_cut.h"

//Fill a line with value 2
void FillLine(Matrix *m, int i, int start, int end)
{
	for(int j = start; j < end; j++)
	{
		PutM(m, i, j, 2);
	}
}

//Fill a coll with value 2
void FillCol(Matrix *m, int j, int start, int end)
{
	for(int i = start; i < end; i++)
	{
		PutM(m, i, j, 2);
	}
}

//Cut line on X axis
void XCut(Matrix *m)
{
	int last_line = 1; //Value of last line, 1 if there was a black pixel
	int line = 1; //Value of the actual line, 1 if there is a black pixel
	for(int i = 0; i < m -> line; i++)
	{
		//If the line was white and the last one was not,
		//we are below a line of the text
		if(line == 0 && last_line == 1)
		{
			FillLine(m, i - 1, 0, m -> col); //Fill last line
		}

		last_line = line; //We change last_line
		line = 0; //We reset line
		for(int j = 0; j < m -> col; j++)
		{
			if(GetM(m, i, j) == 1) //If there is a black pixel
			{
				line = 1; //We have a pixel on this line
				if(last_line == 0) //If last line was white
				{
					FillLine(m, i - 1, 0, m -> col); //Fill last line 
				}
				break;
			}
		}
	}
}

void YCut(Matrix *m)
{
	int last_col = 1; //1 if there was a black pixel on last col
	int col = 1; //1 if there is a blac pixel on this col
	for(int j = 0; j < m -> col; j++)
	{
		last_col = col; //Set last_col to col;
		col = 0; //reset col
		for(int i = 0; i < m -> line; i++)
		{
			if(GetM(m, i, j) == 1) //if there is a black pixel
			{
				col = 1; // change col
				if(last_col == 0) //if last line was white
				{
					FillCol(m, j, 0, m -> line);
				}
				break;
			}
		}
	}
}
