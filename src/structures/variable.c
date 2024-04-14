#include "variable.h"

#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "struct_liste.h"

void free_variable_t(variable_t* var) {
    free(var->nom);
    free_val_t(var->valeur, true, true);
    free(var);
}

val_t* get_value(variable_t* var) {
    return var->valeur;
}

variable_t* new_variable(char* nom, val_t* val) {
    variable_t* var = malloc(sizeof(variable_t));
    var->valeur = val;
    var->nom = nom;
    return var;
}

variable_t* copy_variable(variable_t* var) {
    variable_t* new_var = malloc(sizeof(variable_t));
    new_var->nom = malloc(strlen(var->nom) + 1);
    strcpy(new_var->nom, var->nom);
    new_var->valeur = new_val_t(UNDEFINED);
    copy_val(new_var->valeur, var->valeur, true, true);
    return new_var;
}