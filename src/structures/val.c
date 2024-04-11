#include "val.h"

#include <stdio.h>
#include <stdlib.h>

#include "../constants.h"
#include "../custom_error.h"
#include "../eval_numbers.h"
#include "struct_liste.h"

val_t* new_val_t(char type) {
    val_t* val = malloc(sizeof(val_t));
    if (val == NULL) {
        custom_error("erreur d'allocation", NULL);
        return val;
    }

    val->liste = NULL;
    val->type = type;
    if (type == LISTE) {
        val->liste = new_liste_t();
    }

    val->chaine = NULL;
    return val;
}

void free_val_t(val_t* v) {
    if (v->chaine != NULL) {
        free_chaine_t(v->chaine);
    }
    free(v);
}

int get_int(val_t* v) {
    if (v->type != INT) {
        custom_error("le type de val_t ne correspond pas, un entier est attendu", NULL);
    }
    return *((int*)&(v->value));
}

float get_float(val_t* v) {
    if (v->type != FLOAT) {
        custom_error("le type de val_t ne correspond pas, un flottant est attendu", NULL);
    }
    return *((float*)&(v->value));
}

bool get_bool(val_t* v) {
    if (v->type != BOOL) {
        custom_error("le type de val_t ne correspond pas, un booléen est attendu", NULL);
    }
    return *((bool*)&(v->value));
}

liste_t* get_liste(val_t* v) {
    if (v->type != LISTE) {
        custom_error("le type de val_t ne correspond pas, une liste est attendue", NULL);
    }
    return v->liste;
}

chaine_t* get_char(val_t* v) {
    if (v->type != CHAINE_DE_CHAR) {
        custom_error("le type de val_t ne correspond pas, une chaîne de caractère est attendue", NULL);
    }
    return v->chaine;
}

int get_as_int(val_t* v) {
    switch (v->type) {
        case INT:
            return get_int(v);
            break;
        case FLOAT:
            return (int)get_float(v);
            break;
        case BOOL:
            if (get_bool(v)) {
                return 1;
            } else {
                return 0;
            }
            break;
        default:
            custom_error("le type de val_t n'est pas reconnu", NULL);
            return 0;
            break;
    }
}

float get_as_float(val_t* v) {
    switch (v->type) {
        case INT:
            return (float)get_int(v);
            break;
        case FLOAT:
            return get_float(v);
            break;
        case BOOL:
            if (get_bool(v)) {
                return 1.0;
            } else {
                return 0.0;
            }
            break;
        default:
            custom_error("le type de val_t n'est pas reconnu", NULL);
            return 0.0;
            break;
    }
}

bool get_as_bool(val_t* v) {
    switch (v->type) {
        case INT:
            return get_int(v) != 0;
            break;
        case FLOAT:
            return get_float(v) != 0.0;
            break;
        case BOOL:
            return get_bool(v);
            break;
        default:
            custom_error("le type de val_t n'est pas reconnu", NULL);
            return false;
            break;
    }
}

void set_int(val_t* v, int valeur) {
    v->type = INT;
    v->value = *((int*)&valeur);
}
void set_float(val_t* v, float valeur) {
    v->type = FLOAT;
    v->value = *((int*)&valeur);
}
void set_bool(val_t* v, bool valeur) {
    v->type = BOOL;
    v->value = *((int*)&valeur);
}

void set_liste(val_t* v, liste_t* l) {
    v->type = LISTE;
    v->liste = l;
}

void set_char(val_t* v, chaine_t* chaine) {
    v->type = CHAINE_DE_CHAR;
    v->chaine = chaine;
}

void set_undefined(val_t* v) {
    v->type = -1;
}

void copy_val(val_t* dest, val_t* src) {
    dest->type = src->type;
    dest->value = src->value;
    if (src->type == LISTE) {
        dest->liste = copy_liste(src->liste);
    }
}

void print_val(val_t* v, bool new_line) {
    switch (v->type) {
        case BOOL: {
            if (get_bool(v)) {
                printf("vrai");
            } else {
                printf("faux");
            }
            break;
        }

        case INT: {
            char* str = str_from_int(get_int(v));
            printf("%s", str);
            free(str);
            break;
        }

        case FLOAT: {
            char* str = str_from_float(get_float(v));
            printf("%s", str);
            free(str);
            break;
        }

        case LISTE: {
            printf("[");
            for (int i = 0; i < v->liste->valeursLen; i++) {
                if (i != 0) {
                    printf(", ");
                }
                print_val(v->liste->valeurs[i], false);
            }
            printf("]");
            break;
        }
        case CHAINE_DE_CHAR:
            printf("%s", v->chaine->chars);
            break;

        default:
            custom_error("le type de vat_t n'est pas reconnu", NULL);
            break;
    }

    if (new_line) {
        printf("\n");
    }
};
