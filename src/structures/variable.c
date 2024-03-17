#include "variable.h"

#include <stdlib.h>
#include <string.h>

void free_variable_t(variable_t* var) {
    free(var->nom);
    free(var->valeur);
    free(var);
}

val_t* get_value(variable_t* var) {
    return var->valeur;
}

variable_t* new_variable(char* nom) {
    variable_t* var = malloc(sizeof(variable_t));
    var->nom = nom;
    return var;
}

variable_t* copy_variable(variable_t* var) {
    variable_t* new_var = malloc(sizeof(variable_t));
    new_var->nom = malloc(strlen(var->nom) + 1);
    strcpy(new_var->nom, var->nom);
    new_var->valeur = malloc(sizeof(val_t));
    copy_val(new_var->valeur, var->valeur);
    return new_var;
}