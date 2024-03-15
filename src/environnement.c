#include "environnement.h"

#include <stdlib.h>
#include <string.h>

#include "constants.h"

void free_environnement(environnement_t* env) {
    for (int i = 0; i < env->variable_list_len; i++) {
        if (env->variable_list[i] != NULL) {
            free_variable_t(env->variable_list[i]);
        }
    }
}

environnement_t* new_envrionnement(void) {
    environnement_t* env = malloc(sizeof(environnement_t));
    env->variable_list = malloc(sizeof(variable_t*) * DEFAULT_VARIABLES_LIST_LEN);
    env->variable_list_len = 0;
    env->variable_list_size = DEFAULT_VARIABLES_LIST_LEN;
    return env;
}

void doubleVariableListSize(environnement_t* env) {
    env->variable_list_size *= 2;
    env->variable_list = realloc(env->variable_list, sizeof(variable_t*) * env->variable_list_size);
}

void addToVariableList(environnement_t* env, variable_t* var) {
    if (env->variable_list_len == env->variable_list_size) {
        doubleVariableListSize(env);
    }
    env->variable_list[env->variable_list_len] = var;
    env->variable_list_len++;
}

variable_t* getVariable(environnement_t* env, char* nom) {
    for (int i = 0; i < env->variable_list_len; i++) {
        if (strcmp(env->variable_list[i]->nom, nom) == 0) {
            return env->variable_list[i];
        }
    }
    return NULL;
}