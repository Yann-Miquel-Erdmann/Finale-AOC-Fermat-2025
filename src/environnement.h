#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H
#include "variable.h"
#include "liste.h"

typedef struct environnement {
    variable_t** variable_list;
    int variable_list_len;
    int variable_list_size;
    liste_t** liste_list;
    int liste_list_len;
    int liste_list_size;
} environnement_t;

void free_environnement(environnement_t* env);

environnement_t* new_envrionnement(void);

void doubleVariableListSize(environnement_t* env);
void addToVariableList(environnement_t* env, variable_t* var);

variable_t* getVariable(environnement_t* env, char* nom);

void doubleListeListSize(environnement_t* env);
void addToListeList(environnement_t* env, liste_t* liste);

liste_t* getListe(environnement_t* env, char* nom);


#endif
