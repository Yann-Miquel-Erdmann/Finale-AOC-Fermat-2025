#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"
// #include "phrase.h"
#include "struct_liste.h"

void free_liste_t(liste_t* liste, bool free_chaine, bool free_liste) {
// printf("free liste %p\n", liste);
    for (int i = 0; i < liste->valeursLen; i++) {
        if (liste->valeurs[i] != NULL) {
            free_val_t(liste->valeurs[i], free_chaine, free_liste);
        }
    }
    free(liste->valeurs);
    free(liste);
}

liste_t* new_liste_t(void) {
    liste_t* liste = malloc(sizeof(liste_t));
    liste->valeurs = malloc(sizeof(val_t*) * DEFAULT_VALEURS_LIST_SIZE);
    liste->valeursLen = 0;
    liste->valeursSize = DEFAULT_VALEURS_LIST_SIZE;
    return liste;
}

liste_t* copy_liste(liste_t* liste) {
    liste_t* new_liste = malloc(sizeof(liste_t));
    new_liste->valeurs = malloc(sizeof(val_t*) * liste->valeursSize);
    new_liste->valeursLen = liste->valeursLen;
    new_liste->valeursSize = liste->valeursSize;
    for (int i = 0; i < liste->valeursLen; i++) {
        new_liste->valeurs[i] = new_val_t(UNDEFINED);
        copy_val(new_liste->valeurs[i], liste->valeurs[i], true, true);
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

void vider_liste(liste_t* liste) {
    for (int i = 0; i < liste->valeursLen; i++) {
        free_val_t(liste->valeurs[i], true, true);
    }
    liste->valeursLen = 0;
}

val_t* accession(liste_t* liste, int indice, phrase_t* p) {
    if (indice < 0 || indice >= liste->valeursLen) {
        custom_error("indice hors de la liste", p);
    }
    return liste->valeurs[indice];
}

void modification(liste_t* liste, int indice, val_t* valeur, phrase_t* p) {
    if (indice < 0 || indice >= liste->valeursLen) {
        custom_error("indice hors de la liste", p);
    }

    copy_val(liste->valeurs[indice], valeur, true, true);
}

void ajout(liste_t* liste, val_t* valeur) {
    if (liste->valeursLen ==
        liste->valeursSize) {
        doubleValeursSize(liste);
    }
    liste->valeurs[liste->valeursLen] = new_val_t(UNDEFINED);
    copy_val(liste->valeurs[liste->valeursLen], valeur, true, true);
    liste->valeursLen++;
}

void inserer(liste_t* liste, int indice, val_t* valeur, phrase_t* p) {
    if (indice < 0 || indice > liste->valeursLen) {
        custom_error("indice hors de la liste", p);
    }
    if (liste->valeursLen == liste->valeursSize) {
        doubleValeursSize(liste);
    }
    for (int i = liste->valeursLen; i > indice; i--) {
        liste->valeurs[i] = liste->valeurs[i - 1];
    }
    liste->valeurs[indice] = new_val_t(UNDEFINED);
    copy_val(liste->valeurs[indice], valeur, true, true);
    liste->valeursLen++;
}

void suppression(liste_t* liste, int indice, phrase_t* p) {
    if (indice < 0 || indice >= liste->valeursLen) {
        custom_error("indice hors de la liste", p);
    }
    free_val_t(liste->valeurs[indice], true, true);
    for (int i = indice; i < liste->valeursLen - 1; i++) {
        liste->valeurs[i] = liste->valeurs[i + 1];
    }
    liste->valeursLen--;
}
