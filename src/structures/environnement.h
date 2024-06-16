#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H
#include "struct_liste.h"
#include "variable.h"

typedef struct environnement {
    variable_t** variable_list;
    int variableListLen;
    int variable_list_size;

    val_t** phraseValeurs;
    int phraseValeurs_len;
    int phraseValeurs_size;
} environnement_t;

void free_environnement(environnement_t* env);
environnement_t* copy_environnement(environnement_t* env);

environnement_t* new_environnement(void);

void doubleValeurListSize(environnement_t* env);
void linkValeur(environnement_t* env);

void doubleVariableListSize(environnement_t* env);
void addToVariableList(environnement_t* env, variable_t* var);

int getVariableId(environnement_t* env, char* nom);
variable_t* getVariable(environnement_t* env, int variableId);
val_t* getValeur(environnement_t* env, int indice);
#endif
