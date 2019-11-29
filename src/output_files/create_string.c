#include "create_string.h"
#include "../string/string_operation.h"
#include <stdio.h>
#include <stdlib.h>
#include "../matrix/matrix_image.h"
#include "../NeuNet/structNet.h"
#include "../NeuNet/neuNet.h"

/**
 * \file create_string.c
 * \brief This files contains all the function to get the string from the list
 * of matrix.
 * \author William.G
 */

char *test = "Lorem ipsum dolor sit met\n"\
              "consectetur adipiscing elit.\n"\
              "Morbi rhoncus libero et\n"\
              "\n"\
              "Finibus hendrerit. Nunc\n"\
              "bibendum dignissim justo, id\n"\
              "sodales magna eleifend quis.\n"\
              "\n"\
              "Curabitur vel dui molestie,\n"\
              "pulvinar nisi ut, tempor magna.\n"\
              "Phasellus ut felis id augue\n"\
              "elementum varius condimentum\n"\
              "\n"\
              "nec\n"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnopqrstuvwxyz"\
             "abcdefghijklmnoprstuvwxyz";
char *start;
char *end;

/**
 * \fn char *char_string(List *single_chr)
 * \brief Create a char from a list of char
 *
 * \param single_char : List of character
 *
 * \return pointer to the char
 */
char *char_string(List *single_chr, neuNet *network)
{
    char *c = malloc(sizeof(char) * 2);

    Matrix *m = ((Matrix*) (single_chr->mat));
    Matrix *norm = normalize_dimension(m);

    char n = Calculate(norm ,network);

    *c = n;
    *(c+1) = 0;
	FreeM(norm);
    if(start < end) start++;

    return c;
}

/**
 * \fn char* word_string(List *single_word)
 * \brief Create a word from a list of word, it call the char_string function
 * for every char in the word.
 *
 * \param single_word : lsit of word
 *
 * \return pointer to the word
 */
char* word_string(List *single_word, neuNet *network)
{
    List *first_char = single_word->child;

    char *word = empty_string();

    while(first_char != NULL)
    {
        char *chr = char_string(first_char, network);

        char *w = Concatene(word, chr);

        free(chr);
        free(word);

        word = w;

        first_char = first_char->next;
    }

    return word;
}

/**
 * \fn char* line_string(List *single_line)
 * \brief Create a line from a list of line, it call the word function and
 * add space between every word but not the last.
 *
 * \param single_line : List of line
 *
 * \return pointer to the line
 */
char* line_string(List *single_line, neuNet *network)
{
    List *first_word = single_line->child;

    char *line = empty_string();

    while(first_word->next != NULL)
    {
        char *word = word_string(first_word, network);
        char *l = Concatene(line, word);
        char *l_space = Concatene(l, " ");

        free(l);
        free(word);
        free(line);

        line = l_space;

        start++;
        first_word = first_word->next;
    }

    char *last_word = word_string(first_word, network);
    char *no_space = Concatene(line, last_word);

    free(last_word);
    free(line);

    return no_space;
}

/**
 * \fn char* para_string(List* single_para)
 * \brief Create a paragraph from a list of paragraph, it call the line_string
 * and add '\n' to every end of line.
 *
 * \param single_para : List of paragraph
 *
 * \return pointer to the paragraph
 */
char* para_string(List* single_para, neuNet *network)
{
    List *first_line = single_para->child;

    char* para = empty_string();

    while(first_line != NULL)
    {
        char *line = line_string(first_line, network);
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

/**
 * \fn char* text_string(List* list_para)
 * \brief Create the text from the initial list of paragraph, it call
 * para_string and add '\n' at theend of every paragraph
 *
 * \param list_para : List of paragraph
 *
 * \return pointer to the text
 */
char* text_string(List* list_para, neuNet *network)
{
    List *first_para = list_para;

    char *text = empty_string();

    while(first_para != NULL)
    {
        char *para = para_string(first_para, network);
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

/**
 * \fn void write_files(char* path, List *l)
 * \brief Create a string from the list of paragraph.
 *
 * \param path : path to save the file
 * \param l : list of paragraph
 */
void write_files(char* path, List *l)
{
    FILE *fp;
    start = test;

    end = test + LengthStr(test) - 1;

    fp = fopen(path, "w");

    char *string = text_string(l, NULL);

    fprintf(fp, "%s", string);

    free(string);

    fclose(fp);
}

char* generate_string(List *l, neuNet *network)
{
    start = test;

    end = test + LengthStr(test) - 1;

    char *s = text_string(l, network);

    return s;

}
