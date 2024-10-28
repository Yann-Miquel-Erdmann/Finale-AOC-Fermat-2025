#include "struct_liste.h"

#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"
// #include "phrase.h"
#include "../eval_numbers.h"
#include "../safe_alloc.h"

void free_liste_t(liste_t* liste, bool free_chaine, bool free_liste) {
    // printf("free liste %p\n", liste);
    for (int i = 0; i < liste->valeursLen; i++) {
        // if (liste->valeurs[i] != NULL) {
        // printf("%d. ", i);
        free_val_t(liste->valeurs[i], free_chaine, free_liste);
        // }
    }
    free(liste->valeurs);
    free(liste);
}

liste_t* new_liste_t(void) {
    liste_t* liste = safe_alloc(NULL, sizeof(liste_t));
    liste->valeurs = safe_alloc(NULL, sizeof(val_t*) * DEFAULT_VALEURS_LIST_SIZE);
    liste->valeursLen = 0;
    liste->valeursSize = DEFAULT_VALEURS_LIST_SIZE;
    return liste;
}

liste_t* copy_liste(liste_t* liste) {
    liste_t* new_liste = safe_alloc(NULL, sizeof(liste_t));
    new_liste->valeurs = safe_alloc(NULL, sizeof(val_t*) * liste->valeursSize);
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
    liste->valeurs = safe_alloc(liste->valeurs, sizeof(val_t*) * liste->valeursSize);
}

int taille_liste(liste_t* liste) {
    return liste->valeursLen;
}

void vider_liste(liste_t* liste) {
    for (int i = 0; i < liste->valeursLen; i++) {
        free_val_t(liste->valeurs[i], true, true);
    }
    liste->valeursLen = 0;
}

val_t* accession(liste_t* liste, int indice, phrase_t* p, environnement_t* env) {
    // if (indice < 0 || indice >= liste->valeursLen) {
    //     custom_error("indice hors de la liste", p, env);
    // }
    return liste->valeurs[indice];
}

void modification(liste_t* liste, int indice, val_t* valeur, phrase_t* p, environnement_t* env) {
    if (indice < 0 || indice >= liste->valeursLen) {
        custom_error("indice hors de la liste", p, env);
    }

    copy_val(liste->valeurs[indice], valeur, true, true);
}

void ajout(liste_t* liste, val_t* valeur, phrase_t* p, environnement_t* env) {
    if (liste->valeursLen == liste->valeursSize) {
        doubleValeursSize(liste);
    }
    liste->valeurs[liste->valeursLen] = new_val_t(UNDEFINED);

    copy_val(liste->valeurs[liste->valeursLen], valeur, true, true);
    liste->valeursLen++;
}

void inserer(liste_t* liste, int indice, val_t* valeur, phrase_t* p, environnement_t* env) {
    if (indice < 0 || indice > liste->valeursLen) {
        custom_error("indice hors de la liste", p, env);
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

void suppression(liste_t* liste, int indice, phrase_t* p, environnement_t* env) {
    if (indice < 0 || indice >= liste->valeursLen) {
        custom_error("indice hors de la liste", p, env);
    }
    free_val_t(liste->valeurs[indice], true, true);
    for (int i = indice; i < liste->valeursLen - 1; i++) {
        liste->valeurs[i] = liste->valeurs[i + 1];
    }
    liste->valeursLen--;
}

bool is_equal_list(liste_t* l1, liste_t* l2, phrase_t* p, environnement_t* env) {
    if (l1->valeursLen != l2->valeursLen) {
        return false;
    }
    for (int i = 0; i < l1->valeursLen; i++) {
        if (!is_equal(l1->valeurs[i], l2->valeurs[i], p, env)) {
            return false;
        }
    }
    return true;
}

bool is_greater_list(liste_t* l1, liste_t* l2, phrase_t* p, environnement_t* env) {
    if (l1->valeursLen == 0 && l2->valeursLen == 0) {
        return true;
    }
    if (l1->valeursLen == 0 || l2->valeursLen == 0) {
        return l2->valeursLen == 0;
    }
    int mini;
    if (l2->valeursLen < l1->valeursLen) {
        mini = l2->valeursLen;
    } else {
        mini = l1->valeursLen;
    }

    for (int i = 0; i < mini; i++) {
        if (is_strict_greater(l1->valeurs[i], l2->valeurs[i], p, env)) {
            return true;
        } else if (!is_greater(l1->valeurs[i], l2->valeurs[i], p, env)) {
            return false;
        }
    }
    if (l2->valeursLen > l1->valeursLen) {
        return false;
    }
    return true;
}

bool is_strict_greater_list(liste_t* l1, liste_t* l2, phrase_t* p, environnement_t* env) {
    if (l1->valeursLen == 0 && l2->valeursLen == 0) {
        return false;
    }
    if (l1->valeursLen == 0 || l2->valeursLen == 0) {
        return l2->valeursLen == 0;
    }
    int mini;
    if (l2->valeursLen < l1->valeursLen) {
        mini = l2->valeursLen;
    } else {
        mini = l1->valeursLen;
    }

    for (int i = 0; i < mini; i++) {
        if (is_strict_greater(l1->valeurs[i], l2->valeurs[i], p, env)) {
            return true;
        } else if (!is_greater(l1->valeurs[i], l2->valeurs[i], p, env)) {
            return false;
        }
    }
    if (l2->valeursLen < l1->valeursLen) {
        return true;
    }
    return false;
}

chaine_t* list_to_chaine(liste_t* l) {
    chaine_t* c = safe_alloc(NULL, sizeof(chaine_t));
    char* str;
    for (int i = 0; i < l->valeursLen; i++) {
        switch (l->valeurs[i]->type) {
            case INT:
                str = str_from_int(l->valeurs[i]->value.entier);
                ajouter_chaine(c, str);
                free(str);
                break;
            case FLOAT:
                str = str_from_float(l->valeurs[i]->value.flottant);
                ajouter_chaine(c, str);
                free(str);
                break;
            case POINTEUR:
                ajouter_chaine(c, "ptr");
                break;
            case CHAINE_DE_CHAR:

                ajouter_char(c, '"');
                concat_chaines(c, l->valeurs[i]->value.chaine);
                ajouter_char(c, '"');
                break;
            case LISTE:
                ajouter_char(c, '[');
                chaine_t* c2 = list_to_chaine(l->valeurs[i]->value.liste);
                concat_chaines(c, c2);
                free_chaine_t(c2);
                ajouter_char(c, ']');
                break;
            case BOOL:
                if (l->valeurs[i]->value.booleen) {
                    ajouter_chaine(c, "vrai");
                } else {
                    ajouter_chaine(c, "faux");
                }
                break;
            case UNDEFINED:
                ajouter_chaine(c, "rien");
        }
        if (i != l->valeursLen - 1) {
            ajouter_chaine(c, ", ");
        }
    }
    return c;
}
