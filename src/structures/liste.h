#ifndef liste_h
#define liste_h
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "val.h"

/* Implémentation par liste à sentinelle
La liste contient toujours deux maillons, un
à la tête et un à la queue, appelés les
sentinelles. Ces maillons sont invisibles du
point de vue de l'utilisateur. */

#define T val_t*

/* Structure de données abstraite: Liste chaînée */
typedef struct liste {
    val_t** valeurs;
    int valeursLen;
    int valeursSize;
} liste_t;

void free_liste_t(liste_t* l);

liste_t* new_liste_t();

liste_t* copy_liste(liste_t* l);

void doubleValeursSize(liste_t* l);

int taille(liste_t* l);

val_t* accession(liste_t* l, int indice);
void modification(liste_t* l, int indice, val_t* v);
void ajout(liste_t* l, val_t* v);
void inserer(liste_t* l, int indice, val_t* v);
void suppression(liste_t* l, int indice);

#endif
