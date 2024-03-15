#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H
#include "variable.h"

typedef struct environnement {
    variable_t** variable_list;
    int variable_list_len;
    int variable_list_size;
} environnement_t;
void free_environnement(environnement_t* env);

environnement_t* new_envrionnement(void);

void doubleVariableListSize(environnement_t* env);
void addToVariableList(environnement_t* env, variable_t* var);

variable_t* getVariable(environnement_t* env, char* nom);

#endif
