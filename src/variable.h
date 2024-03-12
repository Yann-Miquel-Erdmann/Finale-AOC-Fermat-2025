#if !defined(VARIABLE_H)
#define VARIABLE_H
#include "val.h"
typedef struct variable{
    char* nom;
    int nom_size;
    int nom_len;
    val_t* valeur;
} variable_t;

void free_variable_t(variable_t* var);

#endif // VARIABLE_H
