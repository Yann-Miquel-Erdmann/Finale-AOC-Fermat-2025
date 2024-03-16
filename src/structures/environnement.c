#include "environnement.h"

#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"

void free_environnement(environnement_t* env) {
    for (int i = 0; i < env->variable_list_len; i++) {
        if (env->variable_list[i] != NULL) {
            free_variable_t(env->variable_list[i]);
        }
    }
    free(env->variable_list);
    for (int i = 0; i < env->liste_list_len; i++) {
        if (env->liste_list[i] != NULL) {
            free_liste_t(env->liste_list[i]);
        }
    }
    free(env->liste_list);
    free(env);
}

environnement_t* new_envrionnement(void) {
    environnement_t* env = malloc(sizeof(environnement_t));

    env->variable_list = malloc(sizeof(variable_t*) * DEFAULT_VARIABLES_LIST_SIZE);
    env->variable_list_len = 0;
    env->variable_list_size = DEFAULT_VARIABLES_LIST_SIZE;

    env->liste_list = malloc(sizeof(liste_t*) * DEFAULT_LISTES_LIST_SIZE);
    env->liste_list_len = 0;
    env->liste_list_size = DEFAULT_LISTES_LIST_SIZE;
    return env;
}

void doubleVariableListSize(environnement_t* env) {
    env->variable_list_size *= 2;
    env->variable_list = realloc(env->variable_list, sizeof(variable_t*) * env->variable_list_size);
    if (env->variable_list == NULL) {
        custom_error("manque de mémoire pour environnement variables_list size", NULL);
    }
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

void doubleListeListSize(environnement_t* env) {
    env->liste_list_size *= 2;
    env->liste_list = realloc(env->liste_list, sizeof(liste_t*) * env->liste_list_size);
    if (env->liste_list == NULL) {
        custom_error("manque de mémoire pour environemnt liste_list size", NULL);
    }
}

void addToListeList(environnement_t* env, liste_t* liste) {
    if (env->liste_list_len == env->liste_list_size) {
        doubleListeListSize(env);
    }
    env->liste_list[env->liste_list_len] = liste;
    env->liste_list_len++;
}

liste_t* getListe(environnement_t* env, char* nom) {
    for (int i = 0; i < env->liste_list_len; i++) {
        if (strcmp(env->liste_list[i]->nom, nom) == 0) {
            return env->liste_list[i];
        }
    }
    return NULL;
}
