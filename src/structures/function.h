#ifndef FUNCTION_H
#define FUNCTION_H

#include "phrase.h"
#include "environnement.h"

// def de la structure phrase pour le cross referencing
typedef struct phrase phrase_t;

typedef struct function{
    char* nom;
    phrase_t* ast;
    environnement_t* env;
    int function_arg_count;
} function_t;

void free_function_t(function_t* f);
function_t* new_function(char* nom, phrase_t* ast);

function_t* copy_function(function_t* f);

typedef struct function_list{
    function_t** function_list;
    int function_list_size;
    int function_list_len;
} function_list_t;
void free_function_list(function_list_t* function_list);

function_list_t* new_function_list(void);

void doubleFunctionListSize(function_list_t* func_list) ;
void addToFunctionList(function_list_t* function_list, function_t* function);

function_t* getFunction(function_list_t* function_list, char* nom);

#endif // FUNCTION_H

