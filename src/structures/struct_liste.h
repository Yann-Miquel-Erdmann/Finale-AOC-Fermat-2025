#ifndef struct_liste_h
#define struct_liste_h

#include <assert.h>

#include "val.h"

typedef struct phrase phrase_t;

// Structure de liste
typedef struct liste {
    val_t** valeurs;
    int valeursLen;
    int valeursSize;
} liste_t;

void free_liste_t(liste_t* l, bool free_chaine, bool free_liste);

liste_t* new_liste_t(void);

liste_t* copy_liste(liste_t* l);

void doubleValeursSize(liste_t* l);

int taille(liste_t* l);

void vider_liste(liste_t* l);

bool is_equal_list(liste_t* l1, liste_t* l2, phrase_t* p);

val_t* accession(liste_t* l, int indice, phrase_t* p);
void modification(liste_t* l, int indice, val_t* v, phrase_t* p);
void ajout(liste_t* l, val_t* v);
void inserer(liste_t* l, int indice, val_t* v, phrase_t* p);
void suppression(liste_t* l, int indice, phrase_t* p);

#endif
