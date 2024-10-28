#include "environnement.h"

#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"
#include "../safe_alloc.h"

void free_environnement(environnement_t* env) {
    for (int i = 0; i < env->variable_list_len; i++) {
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

environnement_t* new_environnement(void) {
    environnement_t* env = safe_alloc(NULL, sizeof(environnement_t));

    env->variable_list = safe_alloc(NULL, sizeof(variable_t*) * DEFAULT_VARIABLES_LIST_SIZE);
    env->variable_list_len = 0;
    env->variable_list_size = DEFAULT_VARIABLES_LIST_SIZE;

    env->phraseValeurs = safe_alloc(NULL, sizeof(val_t*) * DEFAULT_VARIABLES_LIST_SIZE);
    env->phraseValeurs_len = 0;
    env->phraseValeurs_size = DEFAULT_VARIABLES_LIST_SIZE;

    return env;
}

environnement_t* copy_environnement(environnement_t* env) {
    environnement_t* new_env = safe_alloc(NULL, sizeof(environnement_t));
    new_env->variable_list = safe_alloc(NULL, sizeof(variable_t*) * env->variable_list_size);
    new_env->variable_list_len = env->variable_list_len;
    new_env->variable_list_size = env->variable_list_size;
    for (int i = 0; i < env->variable_list_len; i++) {
        new_env->variable_list[i] = copy_variable(env->variable_list[i]);
    }

    new_env->phraseValeurs = safe_alloc(NULL, sizeof(val_t*) * env->phraseValeurs_size);
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
    env->variable_list = safe_alloc(env->variable_list, sizeof(variable_t*) * env->variable_list_size);
}

void addToVariableList(environnement_t* env, variable_t* var) {
    if (env->variable_list_len == env->variable_list_size) {
        doubleVariableListSize(env);
    }
    env->variable_list[env->variable_list_len] = var;
    env->variable_list_len++;
}

void doubleValeurListSize(environnement_t* env) {
    env->phraseValeurs_size *= 2;
    env->phraseValeurs = safe_alloc(env->phraseValeurs, sizeof(val_t*) * env->phraseValeurs_size);
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
    for (int i = 0; i < env->variable_list_len; i++) {
        if (strcmp(env->variable_list[i]->nom, nom) == 0) {
            return i;
        }
    }
    return -1;
}
