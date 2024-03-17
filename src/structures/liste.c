#include "liste.h"

#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"

void free_liste_t(liste_t* liste) {
    for (int i = 0; i < liste->valeursSize; i++) {
        if (liste->valeurs[i] != NULL) {
            free_val_t(liste->valeurs[i]);
        }
    }
    free(liste->valeurs);
    free(liste);
}

liste_t* new_liste_t(char* nom) {
    liste_t* liste = malloc(sizeof(liste_t));
    liste->nom = nom;
    liste->valeurs = malloc(sizeof(val_t*) * DEFAULT_VALEURS_LIST_SIZE);
    liste->valeursLen = 0;
    liste->valeursSize = DEFAULT_VALEURS_LIST_SIZE;
    return liste;
}

liste_t* copy_liste(liste_t* liste) {
    liste_t* new_liste = malloc(sizeof(liste_t));
    new_liste->nom = malloc(strlen(liste->nom) + 1);
    strcpy(new_liste->nom, liste->nom);
    new_liste->valeurs = malloc(sizeof(val_t*) * liste->valeursSize);
    new_liste->valeursLen = liste->valeursLen;
    new_liste->valeursSize = liste->valeursSize;
    for (int i = 0; i < liste->valeursLen; i++) {
        copy_val(new_liste->valeurs[i], liste->valeurs[i]);
    }
    return new_liste;
}

void doubleValeursSize(liste_t* liste) {
    liste->valeursSize *= 2;
    liste->valeurs = realloc(liste->valeurs, sizeof(val_t*) * liste->valeursSize);
    if (liste->valeurs == NULL) {
        custom_error("manque de mémoire pour liste valeurs size", NULL);
    }
}

int taille(liste_t* liste) {
    return liste->valeursLen;
}

val_t* accession(liste_t* liste, int indice) {
    if (indice < 0 || indice >= liste->valeursLen) {
        custom_error("indice hors de la liste", NULL);
    }
    return liste->valeurs[indice];
}

void modification(liste_t* liste, int indice, val_t* valeur) {
    if (indice < 0 || indice >= liste->valeursLen) {
        custom_error("indice hors de la liste", NULL);
    }
    liste->valeurs[indice] = valeur;
}

void ajout(liste_t* liste, val_t* valeur) {
    if (liste->valeursLen == liste->valeursSize) {
        doubleValeursSize(liste);
    }
    liste->valeurs[liste->valeursLen] = valeur;
    liste->valeursLen++;
}

void inserer(liste_t* liste, int indice, val_t* valeur) {
    if (indice < 0 || indice > liste->valeursLen) {
        custom_error("indice hors de la liste", NULL);
    }
    if (liste->valeursLen == liste->valeursSize) {
        doubleValeursSize(liste);
    }
    for (int i = liste->valeursLen; i > indice; i--) {
        liste->valeurs[i] = liste->valeurs[i - 1];
    }
    liste->valeurs[indice] = valeur;
    liste->valeursLen++;
}

void suppression(liste_t* liste, int indice) {
    if (indice < 0 || indice >= liste->valeursLen) {
        custom_error("indice hors de la liste", NULL);
    }
    free_val_t(liste->valeurs[indice]);
    for (int i = indice; i < liste->valeursLen - 1; i++) {
        liste->valeurs[i] = liste->valeurs[i + 1];
    }
    liste->valeursLen--;
}
