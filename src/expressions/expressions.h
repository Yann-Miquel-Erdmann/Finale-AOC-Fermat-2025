#ifndef expressions_h
#define expressions_h

#include "syntax_convert.h"
#include "assert.h"
#include "eval_numbers.h"
#include "custom_error.h"
#include <stdio.h>
#include <stdio.h>
#include "stdlib.h"
#include "phrase.h"
#include "constants.h"
#include "string.h"
#include "syntax_convert.h"

void test_expr_entier(phrase_t* phrase);
void test_expr_flottant(phrase_t* phrase);
void test_expr_booleen(phrase_t* phrase);

#endif
