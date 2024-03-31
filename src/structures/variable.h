#if !defined(VARIABLE_H)
#define VARIABLE_H
#include "val.h"
typedef struct variable{
    char* nom;
    val_t* valeur;
} variable_t;

void free_variable_t(variable_t* var);
variable_t* new_variable(char* nom, val_t* val);

variable_t* copy_variable(variable_t* var);

#endif // VARIABLE_H