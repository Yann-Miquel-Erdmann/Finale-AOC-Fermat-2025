#ifndef syntax_analyser_h
#define syntax_analyser_h

#include <stdbool.h>
#include <stdlib.h>
#include "structures/phrase.h"

bool analyse(phrase_t* phrase, char* syntax, char** arg_list, int* list_len, char* separator);
void free_l(char** l, int len);

#endif
