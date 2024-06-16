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
        custom_error("erreur d'allocation", NULL, NULL);
        return val;
    }
    val->type = type;

    val->to_free_list = false;
    val->to_free_chaine = false;

    val->liste = NULL;
    if (type == LISTE) {
        val->to_free_list = true;
        val->liste = new_liste_t();
    }

    val->chaine = NULL;
    return val;
}

void free_val_t(val_t* v, bool free_chaine, bool free_liste) {
    // printf("free_val_t %p\n", v);
    if ((v->to_free_chaine || free_chaine) && v->chaine != NULL) {
        free_chaine_t(v->chaine);
    }

    if (v->to_free_list  && v->liste != NULL) {
        free_liste_t(v->liste, free_chaine, free_liste);
        v->liste = NULL;
    }

    free(v);
}

void copy_val(val_t* dest, val_t* src, bool cp_chaine, bool cp_liste) {
    // printf("copy %p -> %p   %d %d\n", src, dest, cp_chaine, cp_liste);
    if (dest == NULL || src == NULL) {
        custom_error("copy_val: dest ou src est NULL", NULL, NULL);
    }
    dest->type = src->type;
    dest->value = src->value;

    if (dest->liste != NULL) {
        free_liste_t(dest->liste, true, true);
        dest->liste = NULL;
    }
    if (dest->chaine != NULL) {
        free_chaine_t(dest->chaine);
        dest->chaine = NULL;
    }
    dest->chaine = NULL;
    dest->liste = NULL;

    dest->to_free_chaine = false;
    dest->to_free_list = false;

    if (src->type == LISTE && cp_liste) {
        dest->liste = copy_liste(src->liste);
        // printf("hard copy %p %p\n", dest->liste, src->liste);
        dest->to_free_list = true;
    } else {
        dest->liste = src->liste;
    }

    if (src->type == CHAINE_DE_CHAR && cp_chaine) {
        if (src->chaine != NULL) {
            dest->chaine = copy_chaine(src->chaine);
            dest->to_free_chaine = true;
        }
    } else {
        dest->chaine = src->chaine;
    }
}
int get_int(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != INT) {
        custom_error("le type de val_t ne correspond pas, un entier est attendu", p, env);
    }
    return *((int*)&(v->value));
}

float get_float(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != FLOAT) {
        custom_error("le type de val_t ne correspond pas, un flottant est attendu", p, env);
    }
    return *((float*)&(v->value));
}

bool get_bool(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != BOOL) {
        custom_error("le type de val_t ne correspond pas, un booléen est attendu", p, env);
    }
    return *((bool*)&(v->value));
}

liste_t* get_liste(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != LISTE) {
        custom_error("le type de val_t ne correspond pas, une liste est attendue", p, env);
    }
    return v->liste;
}

chaine_t* get_char(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != CHAINE_DE_CHAR) {
        custom_error("le type de val_t ne correspond pas, une chaîne de caractère est attendue", p, env);
    }
    return v->chaine;
}

int get_as_int(val_t* v, phrase_t* p, environnement_t* env) {
    switch (v->type) {
        case INT:
            return get_int(v, p, env);
            break;
        case FLOAT:
            return (int)get_float(v, p, env);
            break;
        case BOOL:
            if (get_bool(v, p, env)) {
                return 1;
            } else {
                return 0;
            }
            break;
        default:
            custom_error("le type de val_t n'est pas reconnu dans get_as_int", p, env);
            return 0;
            break;
    }
}

float get_as_float(val_t* v, phrase_t* p, environnement_t* env) {
    switch (v->type) {
        case INT:
            return (float)get_int(v, p, env);
            break;
        case FLOAT:
            return get_float(v, p, env);
            break;
        case BOOL:
            if (get_bool(v, p, env)) {
                return 1.0;
            } else {
                return 0.0;
            }
            break;
        default:
            custom_error("le type de val_t n'est pas reconnu dans get_as_float", p, env);
            return 0.0;
            break;
    }
}

bool get_as_bool(val_t* v, phrase_t* p, environnement_t* env) {
    switch (v->type) {
        case INT:
            return get_int(v, p, env) != 0;
            break;
        case FLOAT:
            return get_float(v, p, env) != 0.0;
            break;
        case BOOL:
            return get_bool(v, p, env);
            break;
        case CHAINE_DE_CHAR:
            return get_char(v, p, env)->chars_len != 0;
            break;
        case LISTE:
            return get_liste(v, p, env)->valeursLen != 0;
            break;
        case UNDEFINED:
            return false;
            break;
        default:
            custom_error("le type de val_t n'est pas reconnu dans get_as_bool", p, env);
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
    v->type = UNDEFINED;
}

char* str_type(val_t* v) {
    char* type = malloc(30 * sizeof(char));
    switch (v->type) {
        case INT:
            strcpy(type, "int");
            break;
        case FLOAT:
            strcpy(type, "float");
            break;
        case BOOL:
            strcpy(type, "bool");
            break;
        case LISTE:
            strcpy(type, "liste");
            break;
        case CHAINE_DE_CHAR:
            strcpy(type, "chaîne de caractère");
            break;
        case UNDEFINED:
            strcpy(type, "rien");
            break;
        default:
            strcpy(type, "undefined");
            break;
    }
    return type;
}

bool is_equal(val_t* v1, val_t* v2, phrase_t* p, environnement_t* env) {
    switch (v1->type << 4 | v2->type) {
        case INT << 4 | INT:
        case BOOL << 4 | INT:
        case INT << 4 | BOOL:
            return get_as_int(v1, p, env) == get_as_int(v2, p, env);
            break;

        case FLOAT << 4 | FLOAT:
        case FLOAT << 4 | INT:
        case INT << 4 | FLOAT:
        case FLOAT << 4 | BOOL:
        case BOOL << 4 | FLOAT:
            return get_as_float(v1, p, env) == get_as_float(v2, p, env);
            break;

        case BOOL << 4 | BOOL:
            return get_bool(v1, p, env) == get_bool(v2, p, env);
            break;

        case CHAINE_DE_CHAR << 4 | CHAINE_DE_CHAR:
            return strcmp(get_char(v1, p, env)->chars, get_char(v2, p, env)->chars) == 0;
            break;

        case LISTE << 4 | LISTE:
            return is_equal_list(get_liste(v1, p, env), get_liste(v2, p, env), p, env);
            break;

        case UNDEFINED << 4 | INT:
        case UNDEFINED << 4 | FLOAT:
        case UNDEFINED << 4 | BOOL:
        case UNDEFINED << 4 | CHAINE_DE_CHAR:
        case UNDEFINED << 4 | LISTE:
        case INT << 4 | UNDEFINED:
        case FLOAT << 4 | UNDEFINED:
        case BOOL << 4 | UNDEFINED:
        case CHAINE_DE_CHAR << 4 | UNDEFINED:
        case LISTE << 4 | UNDEFINED:
            return false;
            break;

        case UNDEFINED << 4 | UNDEFINED:
            return true;
            break;

        default: {
            char* error = malloc(100 * sizeof(char));
            sprintf(error, "Impossible de comparer l'égalité d'un élément de type %s et d'un élément de type %s.", str_type(v1), str_type(v2));
            custom_error(error, p, env);
            return false;
            break;
        }
    }
}

bool is_greater(val_t* v1, val_t* v2, phrase_t* p, environnement_t* env) {
    switch (v1->type << 4 | v2->type) {
        case INT << 4 | INT:
        case BOOL << 4 | INT:
        case INT << 4 | BOOL:
            return get_as_int(v1, p, env) >= get_as_int(v2, p, env);
            break;

        case FLOAT << 4 | FLOAT:
        case FLOAT << 4 | INT:
        case INT << 4 | FLOAT:
        case FLOAT << 4 | BOOL:
        case BOOL << 4 | FLOAT:
            return get_as_float(v1, p, env) >= get_as_float(v2, p, env);
            break;

        case CHAINE_DE_CHAR << 4 | CHAINE_DE_CHAR:
            return strcmp(get_char(v1, p, env)->chars, get_char(v2, p, env)->chars) >= 0;
            break;

        case LISTE << 4 | LISTE:
            return is_greater_list(get_liste(v1, p, env), get_liste(v2, p, env), p, env);
            break;

        case UNDEFINED << 4 | INT:
        case UNDEFINED << 4 | FLOAT:
        case UNDEFINED << 4 | BOOL:
        case UNDEFINED << 4 | CHAINE_DE_CHAR:
        case UNDEFINED << 4 | LISTE:
            return false;
            break;

        case INT << 4 | UNDEFINED:
        case FLOAT << 4 | UNDEFINED:
        case BOOL << 4 | UNDEFINED:
        case CHAINE_DE_CHAR << 4 | UNDEFINED:
        case LISTE << 4 | UNDEFINED:
        case UNDEFINED << 4 | UNDEFINED:
            return true;
            break;

        default: {
            char* error = malloc(100 * sizeof(char));
            sprintf(error, "Impossible de comparer un élément de type %s et un élément de type %s.", str_type(v1), str_type(v2));
            custom_error(error, p, env);
            return false;
            break;
        }
    }
}

bool is_strict_greater(val_t* v1, val_t* v2, phrase_t* p, environnement_t* env) {
    switch (v1->type << 4 | v2->type) {
        case INT << 4 | INT:
        case BOOL << 4 | INT:
        case INT << 4 | BOOL:
            return get_as_int(v1, p, env) > get_as_int(v2, p, env);
            break;

        case FLOAT << 4 | FLOAT:
        case FLOAT << 4 | INT:
        case INT << 4 | FLOAT:
        case FLOAT << 4 | BOOL:
        case BOOL << 4 | FLOAT:
            return get_as_float(v1, p, env) > get_as_float(v2, p, env);
            break;

        case CHAINE_DE_CHAR << 4 | CHAINE_DE_CHAR:
            return strcmp(get_char(v1, p, env)->chars, get_char(v2, p, env)->chars) > 0;
            break;

        case LISTE << 4 | LISTE:
            return is_strict_greater_list(get_liste(v1, p, env), get_liste(v2, p, env), p, env);
            break;

        case UNDEFINED << 4 | INT:
        case UNDEFINED << 4 | FLOAT:
        case UNDEFINED << 4 | BOOL:
        case UNDEFINED << 4 | CHAINE_DE_CHAR:
        case UNDEFINED << 4 | LISTE:
        case UNDEFINED << 4 | UNDEFINED:
            return false;
            break;

        case INT << 4 | UNDEFINED:
        case FLOAT << 4 | UNDEFINED:
        case BOOL << 4 | UNDEFINED:
        case CHAINE_DE_CHAR << 4 | UNDEFINED:
        case LISTE << 4 | UNDEFINED:
            return true;
            break;

        default: {
            char* error = malloc(100 * sizeof(char));
            sprintf(error, "Impossible de comparer un élément de type %s et un élément de type %s.", str_type(v1), str_type(v2));
            custom_error(error, p, env);
            return false;
            break;
        }
    }
}

void taille(phrase_t* phrase, environnement_t* env) {
    if (getValeur(env, phrase->args[0]->uniqueId)->type == LISTE) {
        set_int(getValeur(env, phrase->uniqueId), taille_liste(getValeur(env, phrase->args[0]->uniqueId)->liste));
    } else if (getValeur(env, phrase->args[0]->uniqueId)->type == CHAINE_DE_CHAR) {
        set_int(getValeur(env, phrase->uniqueId), getValeur(env, phrase->args[0]->uniqueId)->chaine->chars_len);
    } else {
        custom_error("taille ne peut être appliqué qu'à une liste ou une chaîne de caractères", phrase, env);
    }
}

void print_val(val_t* v, bool new_line, phrase_t* p, environnement_t* env) {
    switch (v->type) {
        case BOOL: {
            if (get_bool(v, p, env)) {
                printf("vrai");
            } else {
                printf("faux");
            }
            break;
        }

        case INT: {
            char* str = str_from_int(get_int(v, p, env));
            printf("%s", str);
            free(str);
            break;
        }

        case FLOAT: {
            char* str = str_from_float(get_float(v, p, env));
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
                if (v->liste->valeurs[i]->type == CHAINE_DE_CHAR) {
                    printf("\"");
                    print_val(v->liste->valeurs[i], false, p, env);
                    printf("\"");
                } else {
                    print_val(v->liste->valeurs[i], false, p, env);
                }
            }
            printf("]");
            break;
        }

        case CHAINE_DE_CHAR:
            for (int i = 0; i < v->chaine->chars_len; i++) {
                if (i < v->chaine->chars_len - 1 && v->chaine->chars[i] == '\\' && v->chaine->chars[i + 1] == 'n') {
                    printf("\n");
                    i++;
                } else {
                    printf("%c", v->chaine->chars[i]);
                }
            }
            break;

        case UNDEFINED:
            printf("Rien");
            break;

        default:
            custom_error("le type de val_t n'est pas reconnu dans print_val", p, env);
            break;
    }

    if (new_line) {
        printf("\n");
    }
};
