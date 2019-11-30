#include "segmentation.h"

float limit(Matrix *m, int begin, int end)
{
    //variable for loops
    int x;
    int y;

    float pixel;

    int c = 0; // 0 = start and 1 = end of an encounter with a caracter

    int draw = 0;// to trace first line of the caracter
    int end_draw = 0;// to trace last line of the caracter

    int white = 0;// if all this columns is white -> white = 1
    float white_count = 0; // nb of white columns
    float nb_white = 0;

    int posX1 = 0;
    int posX2 = 0;

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
		c = 0; //the end of caracter is here
                end_draw = 1; // must trace the last line
                break; // exit the loop
	    }
	}
        if(c && draw) // color the previous column of the caracter
        {
            draw = 0; // first line traced -> reset
	    if(x-1 > 0)
	    {
		posX1 = x-1;
		if(posX2 != 0)
		{
		    white_count += (posX1 - posX2);
		    nb_white += 1;
		}
	    }
        }
        if(!c && end_draw) // color the next column of the caracter
        {
            end_draw = 0;// last line traced -> reset
            posX2 = x;
	}
    }
    return (white_count / nb_white);
}
void lines_segmentation(List *listofparagraph)
{
    Matrix *m = listofparagraph->mat;

    Matrix *li = InitM(0,0);
    PosM* p1 = InitP(0,0,0,0);
    List *lp = InitL(li,p1);

    List *listoflines = lp;

    //variable for loop
    int x;
    int y;

    float pixel;
    
    int line = 0; // mark the presence of line, here it has not
    int black = 0; // mark the presence of black pixel
    int begin; // line of the beginning of black pixel's presence
    int end; // line of end of it

    int posX1 = 0;
    int posX2 = 0;

    int k = 0;
    int l = 0;
    int j = 0;
    int i = 0;

    for(y = 0; y < m->line; y++)// lines
    {
        for(x = 0; x < m->col; x++)// columns
        {
            pixel = GetM(m,y,x); // get pixel at x and y pos in matrix

            if(pixel) // if pixel is black
            {
		if(posX1 != 0 && x < posX1)
		    posX1 = x;
                black = 1; // black = true
                break; // exit the loop
            }
        }

        if(black && !line) // if line has black pixels
        {
            line = 1; // line = true
            begin = y; // conserve the index of the line
	    if(x - 1 > 0)
		posX1 = x -1;
        }
        if((!black && line) || (line && y == ( m->line -1) )) // if previous line had black pixels but this one is white
        {
            line = 0; // line = false
            end = y; // conserve the index of the end

            posX2 = m -> col;
	    k =0;
	    l = 0;
	    j = begin;
	    i = posX1;

	    Matrix *lineM = InitM(end-begin,posX2-posX1); //Create the Matrix of the char
	    while(i < posX2 && l < posX2-posX1)
	    {
		while(j < end && k < end-begin)
		{
		    double pix = GetM(m,j,i);
		    PutM(lineM,k,l,pix);
		    j+=1;
		    k+=1;
		}
		l+=1;
		i+=1;
		k = 0;
		j = begin;
	    }

	    PosM *pos = InitP(posX1,begin,posX2,end); //Pos of the matrix on the image
	    AppendL(listoflines,lineM,pos); // Add the Matrix to the list
	    listoflines = listoflines -> next; 
        }
        black = 0; // black = false
    }

    lp = RemoveFL(lp);
    listofparagraph-> child = lp;
}

void words_segmentation(List *listoflines)
{
    Matrix *m = listoflines->mat;

    Matrix *word = InitM(0,0);
    PosM* p2 = InitP(0,0,0,0);
    List *lp = InitL(word,p2);

    List *listofwords = lp;

    //variable for loops
    int x;
    int y;
    int begin = 0;
    int end = m->line;

    float pixel;

    int c = 0; // 0 = start and 1 = end of an encounter with a caracter
    
    int draw = 0;// to trace first line of the caracter
    int end_draw = 0;// to trace last line of the caracter

    int white = 0;// if all this columns is white -> white = 1
    int white_count = 0; // nb of white columns

    float limits = limit(m,begin,end) + 1;

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
		white_count = 0;
                break; // exit the loop
            }

            if(pixel == 0 && c && white && y == end - 1)
            {
		if(white_count > limits)
		{
		    c = 0; // the end of word is here
		    end_draw = 1; // must trace the last line
		    break; // exit the loop
		}
		white_count += 1;
		break;
            }
        }

        if(c && draw) // color the previous column of the word
        {
            draw = 0; // first line traced -> reset
	    if(x-1 > 0)
		posX1 = x-1;
        }
        if((!c && end_draw) || (c && x == m->col -1)) // color the next column of the word
        {
            end_draw = 0;// last line traced -> reset
	    white_count = 0;
            posX2 = x;
	    k =0;
	    l = 0;
	    j = begin;
	    i = posX1;

	    Matrix *wordM = InitM(end-begin,posX2-posX1); //Create the Matrix of the word
	    while(i < posX2 && l < posX2-posX1)
	    {
		while(j < end && k < end-begin)
		{
		    double pix = GetM(m,j,i);
		    PutM(wordM,k,l,pix);
		    j+=1;
		    k+=1;
		}
		l+=1;
		i+=1;
		k = 0;
		j = begin;
	    }

	    PosM *pos = InitP(posX1,begin,posX2,end); //Pos of the matrix on the image
	    AppendL(listofwords,wordM,pos); // Add the Matrix to the list
	    listofwords = listofwords -> next; 
        }
    }

    lp = RemoveFL(lp);
    listoflines -> child = lp;
}

