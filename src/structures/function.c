#include "function.h"

#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"
#include "environnement.h"
#include "phrase.h"
#include "../safe_alloc.h"

void free_function_t(function_t* func) {
    if (func->ast == NULL) {
        return;
    }
    // free_phrase(func->ast);
    if (func->nom != NULL) {
        free(func->nom);
    }

    free_environnement(func->env);

    free(func);
}

function_t* new_function(char* nom, phrase_t* ast) {
    function_t* func = safe_alloc(NULL, sizeof(function_t));
    func->nom = nom;
    func->ast = ast;
    func->env = new_environnement();
    return func;
}

function_t* copy_function(function_t* func) {
    function_t* new_func = safe_alloc(NULL, sizeof(function_t));
    new_func->nom = safe_alloc(NULL, (int)strlen(func->nom) + 1);
    new_func->function_arg_count = func->function_arg_count;
    strcpy(new_func->nom, func->nom);
    new_func->env = copy_environnement(func->env);
    new_func->ast = copy_phrase(func->ast, NULL, new_func->env);
    new_func->ast->parentPhrase = NULL;
    return new_func;
}

function_list_t* new_function_list(void) {
    function_list_t* func_list = safe_alloc(NULL, sizeof(function_list_t));
    func_list->function_list = safe_alloc(NULL, sizeof(function_t*) * DEFAULT_FUNCTION_LIST_SIZE);
    func_list->function_list_len = 0;
    func_list->function_list_size = DEFAULT_FUNCTION_LIST_SIZE;
    return func_list;
}

void doubleFunctionListSize(function_list_t* func_list) {
    func_list->function_list_size *= 2;
    func_list->function_list = safe_alloc(func_list->function_list, sizeof(function_t*) * func_list->function_list_size);
}

void addToFunctionList(function_list_t* func_list, function_t* func) {
    if (func_list->function_list_len == func_list->function_list_size) {
        doubleFunctionListSize(func_list);
    }
    func_list->function_list[func_list->function_list_len] = func;
    func_list->function_list_len++;
}

void free_function_list(function_list_t* func_list) {
    for (int i = 0; i < func_list->function_list_len; i++) {
        if (func_list->function_list[i] != NULL) {
            free_function_t(func_list->function_list[i]);
        }
    }
    free(func_list->function_list);
    free(func_list);
}

function_t* getFunction(function_list_t* func_list, char* nom) {
    int last_occ = -1;
    for (int i = 0; i < func_list->function_list_len; i++) {
        if (strcmp(func_list->function_list[i]->nom, nom) == 0) {
            last_occ = i;
        }
    }
    if (last_occ == -1) return NULL;
    return func_list->function_list[last_occ];
}
