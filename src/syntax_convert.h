#ifndef syntax_convert_h
#define syntax_convert_h

#include <stdio.h>
#include "stdlib.h"
#include "phrase.h"
#include "constants.h"
#include "string.h"

#include "expressions/expressions.h"
#include "instructions/instructions.h"
#include "function.h"

void tokenise(phrase_t* phrase, function_t* function, function_list_t* function_list);
char** cut_a_b (char*s, int a, int b);
char** split_word(char* str, char* separator);
float log_10_entier(int a);
void free_pointers(char** ptr);

#endif
