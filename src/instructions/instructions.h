#ifndef instructions_h
#define instructions_h

#include "../syntax_convert.h"
#include <assert.h>
#include "../eval_numbers.h"
#include "../custom_error.h"
#include <stdio.h>
#include <stdlib.h>
#include "../phrase.h"
#include "../constants.h"
#include <string.h>
#include "../syntax_convert.h"
#include "../function.h"

bool test_inst_var_init(phrase_t* phrase, function_t* function);
bool test_inst_create_var(phrase_t* phrase, function_t* function);
bool test_inst_modif_var(phrase_t* phrase, function_t* function);
bool test_inst_create_list(phrase_t* phrase, function_t* function);
bool test_inst_modif_list(phrase_t* phrase, function_t* function);
bool test_inst_add_list(phrase_t* phrase, function_t* function);
bool test_inst_suppr_list(phrase_t* phrase, function_t* function);
bool test_inst_def_func(phrase_t* phrase, function_list_t* function_list);
bool test_inst_exec_func(phrase_t* phrase, function_list_t* function_list);
bool test_inst_def_func_args(phrase_t* phrase, function_list_t* function_list);
bool test_inst_exec_func_args(phrase_t* phrase, function_list_t* function_list);

#endif
