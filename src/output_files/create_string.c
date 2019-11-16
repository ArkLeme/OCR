#include "create_string.h"
#include "../string/string_operation.h"
#include <stdio.h>
#include <stdlib.h>
#include "../matrix/matrix_image.h"

char *test = "elementum varius condimentum";
int i;

char *char_string(List *list_chr)
{
    char *c = malloc(sizeof(char) * 2);
    *c = *(test + i);
    *(c + 1) = 0;

    if(i > 0) i--;

    return c;
}

char* word_string(List *list_word)
{
    List *first_char = list_word->child;

    char *word = empty_string();

    while(first_char != NULL)
    {
        char *chr = char_string(first_char);

        char *w = Concatene(chr, word);

        free(chr);
        free(word);

        word = w;

        first_char = first_char->next;
    }

    return word;
}

char* line_string(List *list_line)
{
    List *first_word = list_line->child;

    SaveMatAsIm((Matrix*) (first_word->mat), "word.bmp");
    SaveMatAsIm((Matrix*) (list_line->mat), "line.bmp");

    char *line = empty_string();

    while(first_word != NULL)
    {
        char *word = word_string(first_word);
        char *l = Concatene(word, line);
        //char *l_space = Concatene(l, " ");

        //free(l);
        free(word);
        free(line);

        line = l;

        first_word = first_word->next;
    }

    return line;
}

void write_files(char* path, List *l)
{
    FILE *fp;
    i = LengthStr(test) - 1;

    fp = fopen(path, "w");

    char *string = line_string(l);

    fprintf(fp, "%s", string);

    free(string);

    fclose(fp);
}
