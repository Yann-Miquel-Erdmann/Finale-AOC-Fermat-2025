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
    struct maillon* tete;
    struct maillon* queue;
    int taille;
} liste_t;

typedef struct maillon {
    T val;
    struct maillon* suiv;
    struct maillon* prec;
    liste_t* mere;
} maillon_t;

/* Crée une liste vide */
liste_t* liste_vide();

/* Libère toute la mémoire allouée à l */
void free_liste(liste_t* l);

/* Affiche la liste de l'avant à l'arrière */
void print_liste(liste_t* l);

/* Renvoie vrai si le maillon m est un maillon sentinelle */
bool est_sentinelle(maillon_t* m);

/* ajoute un maillon avec la valeur val à l'avant de la liste l */
void ajoute_avant_v1(liste_t* l, T val);

/* ajoute un maillon avec la valeur val à l'arrière de la liste l */
void ajoute_arriere_v1(liste_t* l, T val);

/* renvoie la valeur du maillon m à condition qu'il ne soit pas nul ou un maillon sentinelle */
T valeur_maillon(maillon_t* m);

/* renvoie un pointeur vers le premier maillon de l*/
maillon_t* premier_maillon(liste_t* l);

/* renvoie un pointeur vers le dernier maillon de l*/
maillon_t* dernier_maillon(liste_t* l);

/* renvoie un pointeur vers le maillon après m */
maillon_t* maillon_suivant(maillon_t* m);

/* renvoie un pointeur vers le maillon avant m */
maillon_t* maillon_precedent(maillon_t* m);

// renvoie le maillon à l'indice "indice" de la liste l
maillon_t* maillon_n(liste_t* l, int indice);

/* insère un maillon avec la valeur val après le maillon m */
void inserer_maillon(maillon_t* m, T val);

/* modifie la valeur du maillon m */
void modifier_maillon(maillon_t* m, T valeur);

/* supprime le maillon m de la liste*/
void supprimer_maillon(maillon_t* m);

/* ajoute un maillon avec la valeur val à l'avant de la liste l */
void ajoute_avant(liste_t* l, T val);

/* ajoute un maillon avec la valeur val à l'arrière de la liste l */
void ajoute_arriere(liste_t* l, T val);

/* renvoie la taille de la liste l */
unsigned int taille(liste_t* l);

val_t* accession(liste_t* l, int indice);
void modification(liste_t* l, int indice, val_t* v);
void ajout(liste_t* l, val_t* v);
void inserer(liste_t* l, int indice, val_t* v);
void suppression(liste_t* l, int indice);

#endif