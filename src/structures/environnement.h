#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H
#include "liste.h"
#include "variable.h"

typedef struct environnement {
    variable_t** variable_list;
    int variable_list_len;
    int variable_list_size;
    liste_t** liste_list;
    int liste_list_len;
    int liste_list_size;
} environnement_t;

void free_environnement(environnement_t* env);
environnement_t* copy_environnement(environnement_t* env);

environnement_t* new_environnement(void);

void doubleVariableListSize(environnement_t* env);
void addToVariableList(environnement_t* env, variable_t* var);

variable_t* getVariable(environnement_t* env, char* nom);



#endif
