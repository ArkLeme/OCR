#include "segmentation.h"

void lines_segmentation(Matrix *m, List *listofchar)
{   
    //variable for loop
    int x;
    int y;

    //int pos = 0; //position of the pixel
    
    int pixel;
    
    int line = 0; // mark the presence of line, here it has not
    int black = 0; // mark the presence of black pixel
    int begin; // line of the beginning of black pixel's presence
    int end; // line of end of it


    for(y = 0; y < m->line; y++)// lines
    {
        for(x = 0; x < m->col; x++)// columns
        {
            pixel = GetM(m,y,x); // get pixel at x and y pos in matrix

            if(pixel) // if pixel is black
            {
                black = 1; // black = true
                break; // exit the loop
            }
        }

        if(black && !line) // if line has black pixels
        {
            line = 1; // line = true
            begin = y; // conserve the index of the line
        }
        if(!black && line) // if previous line had black pixels but now it is white
        {
            line = 0; // make back line = false
            end = y; // conserve the index of the end

            // trace the char_segmentation
            char_segmentation(m, begin, end,listofchar);
        }

        black = 0; // black = false
    }
}

void char_segmentation(Matrix *m, int begin, int end,List *listofchar)
{
    //variable for loops
    int x;
    int y;

    float pixel;

    int c = 0; // 0 = start and 1 = end of an encounter with a caracter
    
    int draw = 0;// to trace first line of the caracter
    int end_draw = 0;// to trace last line of the caracter

    int white = 0;// if all this columns is white -> white = 1

    int posX1 = 0;
    int posX2 = 0;
    
    int k = 0;
    int l = 0;
    int j = 0;
    int i = 0;

    for(x = 0; x < m->col; x++) // columns
    {
        white = 1; //reset

        for(y = begin; y < end; y++) // lines
        {
            pixel = GetM(m,y,x);

            if(pixel && !c) // encounter with a caracter
            {
                c = 1; // a caracter is here
                draw = 1; // trace first line
                break; // exit the loop
            }

            if(pixel) // if the caracter is not finished yet
            {
                white = 0;
                break; // exit the loop
            }

            if(pixel == 0 && c && white && y == end - 1)
            {
                c = 0; // the end of caracter is here
                end_draw = 1; // must trace the last line
                break; // exit the loop
            }
        }

        if(c && draw) // color the previous column of the caracter
        {
            draw = 0; // first line traced -> reset
	    if(x-1 > 0)
		posX1 = x-1;
        }
        if(!c && end_draw) // color the next column of the caracter
        {
            end_draw = 0;// last line traced -> reset
            posX2 = x;
	    k =0;
	    l = 0;
	    j = begin;
	    i = posX1;

	    Matrix *charM = InitM(end-begin,posX2-posX1);
	    while(i < posX2 && l < posX2-posX1)
	    {
		while(j < end && k < end-begin)
		{
		    double pix = GetM(m,j,i);
		    PutM(charM,k,l,pix);
		    j+=1;
		    k+=1;
		}
		l+=1;
		i+=1;
		k = 0;
		j = begin;
	    }
	    PosM *pos = InitP(posX1,begin,posX2,end);
	    AppendL(listofchar,charM,pos);
	    listofchar = listofchar -> next;
        }
	
    }
}

/*void charCenterinM(Matrix *charM)
{
    int i = 0;
    int j = 0;
    for(int k = 0; k < charM-> col; k ++)
    {
    }
}


void widthchar(Matrix *charM)
{
    int test = 0;
    int width = 0;
    int width_max = 0;
    for(int i = 0; i < charM -> line ; i++)
    {
	for(int j =0; j< charM -> col;j++)
	{
	    if(test)
	    {
		width +=1
	    if(GetM(charM,j,i) == 1) 
	    {
		width+=1;
		test =1;
	    }
	}
	width_max=max(width,width_max);
    }
    return width_max;
}

int max(int a, int b)
{
    if(b >= a) return b;
    else return a;
}*/
