#ifndef syntax_convert_h
#define syntax_convert_h

#include <stdio.h>
#include "stdlib.h"
#include "phrase.h"
#include "constants.h"
#include "string.h"

#include "expressions/expressions.h"

void reduce_var_and_num(phrase_t* phrase);
void tokenise(phrase_t* phrase);
char** cut_a_b (char*s, int a, int b);
char** split_word(char* str, char* separator);
float log_10_entier(int a);

#endif
