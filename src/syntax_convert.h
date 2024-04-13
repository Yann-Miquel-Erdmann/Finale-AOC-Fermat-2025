#ifndef syntax_convert_h
#define syntax_convert_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "expressions/expressions.h"
#include "instructions/instructions.h"
#include "structures/function.h"
#include "structures/phrase.h"

void tokenise(phrase_t* phrase, function_t* function, function_list_t* function_list, function_list_t* func_call_list);   
void link_function_to_call(function_list_t* func_list, function_list_t* func_call_list);
void isolate_func_envs(function_list_t* func_list);
char** cut_a_b(char* s, int a, int b);
char** split_word(char* str, char* separator);
int log_10_entier(int a);
int puiss10(int a);
void free_pointers(char** ptr);

#endif
