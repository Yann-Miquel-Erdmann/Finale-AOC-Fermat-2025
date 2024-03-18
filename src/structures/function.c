#include "function.h"

#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"
#include "phrase.h"
#include "environnement.h"

void free_function_t(function_t* func) {
    if (func->ast == NULL){
        return;
    }

    free_phrase(func->ast);
    if (func->nom != NULL){
        free(func->nom);
    }

    free_environnement(func->env);

    free(func);
}

function_t* new_function(char* nom, phrase_t* ast) {
    function_t* func = malloc(sizeof(function_t));
    func->nom = nom;
    func->ast = ast;
    func->env = new_environnement();
    return func;
}

function_t* copy_function(function_t* func) {
    function_t* new_func = malloc(sizeof(function_t));
    new_func->nom = malloc(strlen(func->nom) + 1);
    strcpy(new_func->nom, func->nom);
    new_func->env = copy_environnement(func->env);
    new_func->ast = copy_phrase(func->ast, new_func->env);
    return new_func;

}


function_list_t* new_function_list(void) {
    function_list_t* func_list = malloc(sizeof(function_list_t));
    func_list->function_list = malloc(sizeof(function_t*) * DEFAULT_FUNCTION_LIST_SIZE);
    func_list->function_list_len = 0;
    func_list->function_list_size = DEFAULT_FUNCTION_LIST_SIZE;
    return func_list;
}
void doubleFunctionListSize(function_list_t* func_list) {
    func_list->function_list_size *= 2;
    func_list->function_list = realloc(func_list->function_list, sizeof(function_t*) * func_list->function_list_size);
    if (func_list->function_list == NULL) {
        custom_error("manque de mémoire pour function list size", NULL);
    }
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
    for (int i = 0; i < func_list->function_list_len; i++) {
        if (strcmp(func_list->function_list[i]->nom, nom) == 0) {
            return func_list->function_list[i];
        }
    }
    return NULL;
}