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

void tokenise(phrase_t* phrase, function_t* function, function_list_t* function_list, function_list_t* func_call_list, int* uniqueId, phrase_t* parent_loop, bool inLoopSuivant, phrase_t* inLoopSuivantPointer);
void link_function_to_call(function_list_t* func_list, function_list_t* func_call_list, environnement_t* env);
void isolate_func_envs(function_list_t* func_list);
void removeConstants(phrase_t* phrase);
phrase_t* recLastArg(phrase_t* phrase);
phrase_t* recLastInner(phrase_t* phrase);

char** split_word(char* str, char* separator);

int puiss10(int a);

#endif
