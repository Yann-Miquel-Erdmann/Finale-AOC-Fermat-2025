#include "environnement.h"

#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"

void free_environnement(environnement_t* env) {
    for (int i = 0; i < env->variableListLen; i++) {
        if (env->variable_list[i] != NULL) {
            free_variable_t(env->variable_list[i]);
        }
    }
    free(env->variable_list);

    // printf("free phraseValeurs %d\n", env->phraseValeurs_len);
    for (int i = 0; i < env->phraseValeurs_len; i++) {
        // printf("phraseValeur %d\n", i);
        if (env->phraseValeurs[i] != NULL) {
            free_val_t(env->phraseValeurs[i], true, true);
        }
    }
    free(env->phraseValeurs);

    free(env);
}

environnement_t* new_environnement() {
    environnement_t* env = malloc(sizeof(environnement_t));

    env->variable_list = malloc(sizeof(variable_t*) * DEFAULT_VARIABLES_LIST_SIZE);
    env->variableListLen = 0;
    env->variable_list_size = DEFAULT_VARIABLES_LIST_SIZE;

    env->phraseValeurs = malloc(sizeof(val_t*) * DEFAULT_VARIABLES_LIST_SIZE);
    env->phraseValeurs_len = 0;
    env->phraseValeurs_size = DEFAULT_VARIABLES_LIST_SIZE;

    return env;
}

environnement_t* copy_environnement(environnement_t* env) {
    environnement_t* new_env = malloc(sizeof(environnement_t));
    new_env->variable_list = malloc(sizeof(variable_t*) * env->variable_list_size);
    new_env->variableListLen = env->variableListLen;
    new_env->variable_list_size = env->variable_list_size;
    for (int i = 0; i < env->variableListLen; i++) {
        new_env->variable_list[i] = copy_variable(env->variable_list[i]);
    }

    new_env->phraseValeurs = malloc(sizeof(val_t*) * env->phraseValeurs_size);
    new_env->phraseValeurs_len = env->phraseValeurs_len;
    new_env->phraseValeurs_size = env->phraseValeurs_size;
    for (int i = 0; i < env->phraseValeurs_len; i++) {
        new_env->phraseValeurs[i] = new_val_t(UNDEFINED);
        copy_val(new_env->phraseValeurs[i], env->phraseValeurs[i], true, true);
    }
    return new_env;
}

void doubleVariableListSize(environnement_t* env) {
    env->variable_list_size *= 2;
    env->variable_list = realloc(env->variable_list, sizeof(variable_t*) * env->variable_list_size);
    if (env->variable_list == NULL) {
        custom_error("manque de mémoire pour environnement variables_list size", NULL, NULL);
    }
}

void addToVariableList(environnement_t* env, variable_t* var) {
    if (env->variableListLen == env->variable_list_size) {
        doubleVariableListSize(env);
    }
    env->variable_list[env->variableListLen] = var;
    env->variableListLen++;
}

void doubleValeurListSize(environnement_t* env) {
    env->phraseValeurs_size *= 2;
    env->phraseValeurs = realloc(env->phraseValeurs, sizeof(val_t*) * env->phraseValeurs_size);
    if (env->phraseValeurs == NULL) {
        custom_error("manque de mémoire pour environnement phraseValeurs size", NULL, NULL);
    }
}

void linkValeur(environnement_t* env) {
    if (env->phraseValeurs_len == env->phraseValeurs_size) {
        doubleValeurListSize(env);
    }
    // printf("add elem %d\n", env->phraseValeurs_len);
    env->phraseValeurs[env->phraseValeurs_len] = new_val_t(UNDEFINED);
    env->phraseValeurs_len++;
}

int getVariableId(environnement_t* env, char* nom) {
    for (int i = 0; i < env->variableListLen; i++) {
        if (strcmp(env->variable_list[i]->nom, nom) == 0) {
            return i;
        }
    }
    return -1;
}

variable_t* getVariable(environnement_t* env, int variableId) {
    return env->variable_list[variableId];
}

val_t* getValeur(environnement_t* env, int indice) {
    return env->phraseValeurs[indice];
}
