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
        exit(1);
    }

    val->type = type;

    val->to_free = false;

    if (type == LISTE) {
        val->to_free = true;
        val->value.liste = new_liste_t();
    }

    return val;
}

void free_val_t(val_t* v, bool free_chaine, bool free_liste) {
    // printf("free_val_t %p\n", v);
    if (v->to_free && v->type == CHAINE_DE_CHAR) {
        free_chaine_t(v->value.chaine);
    }

    if (v->to_free && v->type == LISTE) {
        free_liste_t(v->value.liste, free_chaine, free_liste);
    }

    free(v);
}

void copy_val(val_t* dest, val_t* src, bool cp_chaine, bool cp_liste) {
    // printf("copy %p -> %p   %d %d\n", src, dest, cp_chaine, cp_liste);
    if (dest == NULL || src == NULL) {
        custom_error("copy_val: dest ou src est NULL", NULL, NULL);
        exit(1);
    }

    if (dest->to_free && dest->type == LISTE) {
        free_liste_t(dest->value.liste, true, true);
    }
    if (dest->to_free && dest->type == CHAINE_DE_CHAR) {
        free_chaine_t(dest->value.chaine);
    }

    dest->type = src->type;
    dest->to_free = false;
    switch (src->type) {
        case INT:
            dest->value.entier = src->value.entier;
            break;
        case FLOAT:
            dest->value.flottant = src->value.flottant;
            break;
        case BOOL:
            dest->value.booleen = src->value.booleen;
            break;
        case LISTE:
            dest->value.entier = src->value.entier;
            if (cp_liste) {
                dest->value.liste = copy_liste(src->value.liste);
                dest->to_free = true;
            } else {
                dest->value.liste = src->value.liste;
            }
            break;
        case CHAINE_DE_CHAR:
            if (cp_chaine) {
                dest->value.chaine = copy_chaine(src->value.chaine);
                dest->to_free = true;
            } else {
                dest->value.chaine = src->value.chaine;
            }
            break;

        case UNDEFINED:
            break;

        default:
            print_val(src, true, NULL, NULL);
            custom_error("type de val_t non reconnu dans copy_val", NULL, NULL);
            exit(1);
            break;
    }
}

int get_int(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != INT) {
        custom_error("le type de val_t ne correspond pas, un entier est attendu", p, env);
    }
    return v->value.entier;
}

float get_float(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != FLOAT) {
        custom_error("le type de val_t ne correspond pas, un flottant est attendu", p, env);
    }
    return v->value.flottant;
}

bool get_bool(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != BOOL) {
        custom_error("le type de val_t ne correspond pas, un booléen est attendu", p, env);
    }
    return v->value.booleen;
}

liste_t* get_liste(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != LISTE) {
        custom_error("le type de val_t ne correspond pas, une liste est attendue", p, env);
    }
    return v->value.liste;
}

chaine_t* get_char(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->type != CHAINE_DE_CHAR) {
        custom_error("le type de val_t ne correspond pas, une chaîne de caractère est attendue", p, env);
    }
    return v->value.chaine;
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
    v->value.entier = valeur;
}
void set_float(val_t* v, float valeur) {
    v->type = FLOAT;
    v->value.flottant = valeur;
}
void set_bool(val_t* v, bool valeur) {
    v->type = BOOL;
    v->value.booleen = valeur;
}

void set_liste(val_t* v, liste_t* l) {
    v->type = LISTE;
    v->value.liste = l;
}

void set_char(val_t* v, chaine_t* chaine) {
    v->type = CHAINE_DE_CHAR;
    v->value.chaine = chaine;
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
    if (env->phraseValeurs[phrase->args[0]->uniqueId]->type == LISTE) {
        set_int(env->phraseValeurs[phrase->uniqueId], taille_liste(env->phraseValeurs[phrase->args[0]->uniqueId]->value.liste));
    } else if (env->phraseValeurs[phrase->args[0]->uniqueId]->type == CHAINE_DE_CHAR) {
        set_int(env->phraseValeurs[phrase->uniqueId], env->phraseValeurs[phrase->args[0]->uniqueId]->value.chaine->chars_len);
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
            for (int i = 0; i < v->value.liste->valeursLen; i++) {
                if (i != 0) {
                    printf(", ");
                }
                if (v->value.liste->valeurs[i]->type == CHAINE_DE_CHAR) {
                    printf("\"");
                    print_val(v->value.liste->valeurs[i], false, p, env);
                    printf("\"");
                } else {
                    print_val(v->value.liste->valeurs[i], false, p, env);
                }
            }
            printf("]");
            break;
        }

        case CHAINE_DE_CHAR:
            for (int i = 0; i < v->value.chaine->chars_len; i++) {
                if (i < v->value.chaine->chars_len - 1 && v->value.chaine->chars[i] == '\\' && v->value.chaine->chars[i + 1] == 'n') {
                    printf("\n");
                    i++;
                } else {
                    printf("%c", v->value.chaine->chars[i]);
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
