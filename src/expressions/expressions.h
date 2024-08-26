#ifndef expressions_h
#define expressions_h

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"
#include "../eval_numbers.h"
#include "../structures/environnement.h"
#include "../structures/phrase.h"
#include "../syntax_convert.h"

bool test_expr_entier(phrase_t* phrase, environnement_t* env);
bool test_expr_flottant(phrase_t* phrase, environnement_t* env);
bool test_expr_booleen(phrase_t* phrase, environnement_t* env);
bool test_expr_chaine(phrase_t* phrase, environnement_t* env);
bool test_expr_list(phrase_t* phrase, function_t* func);
bool test_expr_access_var(phrase_t* phrase, function_t* func);
bool test_expr_access_list(phrase_t* phrase, function_t* func);
bool test_expr_func_call(phrase_t* phrase, function_list_t* func_list, environnement_t* env);
bool test_expr_func_call_args(phrase_t* phrase, function_list_t* func_list, environnement_t* env);
void get_input(val_t* dest);

#endif
