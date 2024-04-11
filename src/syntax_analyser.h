#ifndef syntax_analyser_h
#define syntax_analyser_h

#include <stdbool.h>
#include <stdlib.h>
#include "structures/phrase.h"

char** analyse(phrase_t* phrase, char* syntax, int* list_len, char* separator);
void free_l(char** l, int len);

#endif
