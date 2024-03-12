#include <stdlib.h>

#include "variable.h"

void free_variable_t(variable_t* var){
    free(var->nom);
    free(var->valeur);
}

val_t* get_value(variable_t* var){
    return var->valeur;
}