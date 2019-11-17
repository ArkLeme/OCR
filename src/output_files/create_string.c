#include "create_string.h"
#include "../string/string_operation.h"
#include <stdio.h>
#include <stdlib.h>
#include "../matrix/matrix_image.h"

char *test = "Lorem ipsum dolor sit met\n"\
              "consectetur adipiscing elit\n"\
              "Morbi rhoncus libero et\n"\
              "\n"\
              "Finibus hendrerit Nunc\n"\
              "bibendum dignissim justo id\n"\
              "sodales magna eleifend quis\n"\
              "\n"\
              "Curabitur vel dui molestie\n"\
              "pulvinar nisi ut tempor magna\n"\
              "Phasellus ut felis id augue\n"\
              "elementum varius condimentum\n"\
              "\n"\
              "nec\n"\
              "abcdefghijklmnopqrstuvwxyz"\
              "abcdefghijklmnoprstuvwxyz";
char *start;
char *end;

char *char_string(List *single_chr)
{
    char *c = malloc(sizeof(char) * 2);
    *c = *start;
    *(c + 1) = 0;

    if(start < end) start++;

    return c;
}

char* word_string(List *single_word)
{
    List *first_char = single_word->child;

    char *word = empty_string();

    while(first_char != NULL)
    {
        char *chr = char_string(first_char);

        char *w = Concatene(word, chr);

        free(chr);
        free(word);

        word = w;

        first_char = first_char->next;
    }

    return word;
}

char* line_string(List *single_line)
{
    List *first_word = single_line->child;

    char *line = empty_string();

    while(first_word->next != NULL)
    {
        char *word = word_string(first_word);
        char *l = Concatene(line, word);
        char *l_space = Concatene(l, " ");

        free(l);
        free(word);
        free(line);

        line = l_space;

        start++;
        first_word = first_word->next;
    }

    char *last_word = word_string(first_word);
    char *no_space = Concatene(line, last_word);

    free(last_word);
    free(line);

    return no_space;
}

char* para_string(List* single_para)
{
    List *first_line = single_para->child;

    char* para = empty_string();

    while(first_line != NULL)
    {
        char *line = line_string(first_line);
        char *p = Concatene(para, line);
        char *l_n = Concatene(p, "\n");

        free(p);
        free(line);
        free(para);

        para = l_n;

        start++;
        first_line = first_line->next;
    }

    return para;
}

char* text_string(List* list_para)
{
    List *first_para = list_para;

    char *text = empty_string();

    while(first_para != NULL)
    {
        char *para = para_string(first_para);
        char *t = Concatene(text, para);
        char *t_n = Concatene(t, "\n");

        free(t);
        free(para);
        free(text);

        start++;
        text = t_n;
        first_para = first_para->next;
    }

    return text;
}

void write_files(char* path, List *l)
{
    FILE *fp;
    start = test;

    SaveMatsAsIm(l, 10, "line.bmp");

    end = test + LengthStr(test) - 1;

    fp = fopen(path, "w");

    char *string = text_string(l);
    char *s = Concatene(string, "0");

    fprintf(fp, "%s", s);

    free(string);
    free(s);

    fclose(fp);
}
