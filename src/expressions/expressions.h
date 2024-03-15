#ifndef expressions_h
#define expressions_h

#include "../syntax_convert.h"
#include "assert.h"
#include "../eval_numbers.h"
#include "../custom_error.h"
#include <stdio.h>
#include <stdio.h>
#include "stdlib.h"
#include "../phrase.h"
#include "../constants.h"
#include <string.h>
#include "../syntax_convert.h"
#include "../environnement.h"

bool test_expr_entier(phrase_t* phrase);
bool test_expr_flottant(phrase_t* phrase);
bool test_expr_booleen(phrase_t* phrase);
bool test_expr_chaine(phrase_t* phrase);
bool test_expr_access_var(phrase_t* phrase,  function_t* function);
bool test_expr_access_list(phrase_t* phrase, function_t* function);
bool test_expr_taille_list(phrase_t* phrase, function_t* function);
bool test_expr_func_call(phrase_t* phrase, function_list_t* function_list);
bool test_expr_func_call_args(phrase_t* phrase, function_list_t* function_list);

#endif
