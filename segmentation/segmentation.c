#include "segmentation.h"

void lines_segmentation(SDL_Surface* img)
{
    int w = img -> w; // width of img
    int h = img -> h; // height of img
    
    //variable for loop
    int x;
    int y;

    int pos = 0; //position of the pixel

    unsigned char r , g , b; // char = unsigned number from 0 to 255 included
    
    Uint32 pixel;
    
    int line = 0; // line = 1 if there is a line_segmentation

    int black = 0; // presence of black pixel

    int begin; // line of the beginning of black pixel's presence
    int end; // line of end of it

    for(y = 0; y < h; y++) // lines
    {
        for(x = 0; x < w; x++) // columns
        {
            pixel = GetPixel(img,x,y); 

            // get colors of pixel
            SDL_GetRGB(pixel, img->format, &r, &g, &b);

            if(!r && !g && !b) // if pixel is black
            {
                black = 1; // black = true
                break; // exit the loop
            }
        }

        if(black && !line) // if line has black pixels
        {
            line = 1; // line = true
            begin = y; // conserve the index of the line

            for(x = 0; x < w; x++)
            {
		pixel = GetPixel(img,x,y); 
                pos = y - 1; // previous line
                if(pos >= 0) // verify if the height of previous line is positive
                {
                    pixel = SDL_MapRGB(img->format, 255, 0, 0); //change color of previous line
                    PutPixel(img,x,pos,pixel);
                }
            }
        }
        if(!black && line) // if previous line had black pixels but now it is white
        {
            line = 0; // make back line = false
            end = y; // conserve the index of the end

            for(x = 0; x < w; x++)
            {
		pixel = GetPixel(img,x,y); 
                pos = y + 1; // next line
                if(pos < h) // verify if next line can be reached
                {
                    pixel = SDL_MapRGB(img->format, 255, 0, 0);
                    PutPixel(img,x,pos,pixel);
                }
            }
            // trace the char_segmentation
            char_segmentation(img, begin, end);
        }

        black = 0; // black = false
    }
}

void char_segmentation(SDL_Surface* img, int begin, int end)
{
    int w = img -> w;// the limits of columns = width of img

    //variable for loops
    int x;
    int y;

    unsigned char r , g , b; // unsigned char = number from 0 to 255 included
    
    Uint32 pixel;

    int c = 0; // 0 = start and 1 = end of an encounter with a caracter
    
    int draw = 0;// to trace first line of the caracter
    int end_draw = 0;// to trace last line of the caracter

    int white = 0;// if all this columns is white -> white = 1

    for(x = 0; x < w; x++) // columns
    {
        white = 1; //reset

        for(y = begin; y < end; y++) // lines
        {
            pixel = GetPixel(img,x,y);
	    SDL_GetRGB(pixel, img->format, &r, &g, &b);   // get colors of pixel

            if(!r && !g && !b && !c) // encounter with a caracter
            {
                c = 1; // a caracter is here
                draw = 1; // trace first line
                break; // exit the loop
            }

            if(!r && !b && !g) // if the caracter is not finished yet
            {
                white = 0;
                break; // exit the loop
            }

            if(r == 255 && b == 255 && g == 255 && c && white && y == end - 1)
            {
                c = 0; // the end of caracter is here
                end_draw = 1; // must trace the last line
                break; // exit the loop
            }
        }

        if(c && draw) // color the previous column of the caracter
        {
            draw = 0; // first line traced -> reset
            for(y = begin; y < end; y++)
            {
                if(x - 1 > 0) //previous column
                {
                    pixel = SDL_MapRGB(img->format, 0, 0, 255); //change color of pixel
		    PutPixel(img,x-1,y,pixel); // put pixel
		}
            }
        }
        if(!c && end_draw) // color the next column of the caracter
        {
            end_draw = 0;// last line traced -> reset
            
	    for(y = begin; y < end; y++)
            {
                pixel = SDL_MapRGB(img->format, 0, 0, 255); //change color of pixel
                PutPixel(img,x,y,pixel); // put pixel
		
            }
        }
    }
}
