#include "create_string.h"
#include "../string/string_operation.h"
#include <stdio.h>
#include <stdlib.h>
#include "../matrix/matrix_image.h"

char *test = "elementumvariuscondimentum";
int i;

char *char_string(List *list_chr)
{
    char *c = malloc(sizeof(char) * 2);

    *c = *(test + i);
    *(c+1) = 0;

    if(i > 0) i--;

    printf("%i", i);
    printf("%s", c);
    return c;
}

char* word_string(List *list_word)
{
    List *first_char = list_word->child;
    SaveMatAsIm((Matrix*) (list_word->mat), "word1.bmp");

    char *word = char_string(first_char);
    first_char = first_char->next;

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

void write_files(char* path, List *l)
{
    FILE *fp;
    i = LengthStr(test);

    fp = fopen(path, "w");

    char *string = word_string(l);

    fprintf(fp, "%s", string);

    free(string);

    fclose(fp);
}
