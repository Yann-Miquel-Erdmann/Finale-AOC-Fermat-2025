#include <stdlib.h>

#include "variable.h"

void free_variable_t(variable_t* var){
    free(var->nom);
    free(var->valeur);
    free(var);
}

val_t* get_value(variable_t* var){
    return var->valeur;
}

variable_t* new_variable(char* nom){
    variable_t * var = malloc(sizeof(variable_t));
    var->nom = nom;
    return var;
}