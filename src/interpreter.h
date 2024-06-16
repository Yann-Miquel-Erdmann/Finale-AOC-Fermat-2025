#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "structures/function.h"

void interpreter(function_t* function ,function_list_t* functions, val_t* result ,int layer);
#endif