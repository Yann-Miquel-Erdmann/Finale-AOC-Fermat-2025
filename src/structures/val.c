#include "val.h"

#include <stdio.h>
#include <stdlib.h>

#include "../constants.h"
#include "../custom_error.h"
#include "../eval_numbers.h"
#include "../pointeur.h"
#include "../safe_alloc.h"
#include "struct_liste.h"

val_t* new_val_t(char type) {
    val_t* val = safe_alloc(NULL, sizeof(val_t));

    val->type = type;

    if (type == LISTE) {
        val->value.liste = new_liste_t();
    } else if (type == CHAINE_DE_CHAR) {
        val->value.chaine = new_chaine_t("");
    }

    val->ferme = false;
    val->ouvert = false;
    val->references = 1;
    return val;
}

void free_val_t(val_t* v, bool free_chaine, bool free_liste) {
    // if (decr_ref) {
    v->references--;

    if (v->references != 0) {
        return;
    }

    if (v->type == CHAINE_DE_CHAR) {
        free_chaine_t(v->value.chaine);
    } else if (v->type == LISTE) {
        free_liste_t(v->value.liste, free_chaine, free_liste);
    } else if (v->type == POINTEUR) {
        free_val_t(v->value.ptr, free_chaine, free_liste);
    }

    v->type = -1;
    free(v);
}

void __attribute__((hot)) copy_val(val_t* dest, val_t* src, bool cp_chaine, bool cp_liste) {
    if (dest->type == LISTE) {
        free_liste_t(dest->value.liste, true, true);
    } else if (dest->type == CHAINE_DE_CHAR) {
        free_chaine_t(dest->value.chaine);
    } else

        if (dest->type == POINTEUR) {
        dest->value.ptr->references--;
    }

    dest->type = src->type;
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
            if (cp_liste) {
                dest->value.liste = copy_liste(src->value.liste);
            } else {
                dest->value.liste = src->value.liste;
                dest->type = LISTE;
            }
            break;

            //
            //     if (cp_liste) {
            //         dest->value.liste = copy_liste(src->value.liste);
            //         dest->type = LISTE;
            //     } else {
            //         dest->value.liste = src->value.liste;
            //     }
            //     break;

        case CHAINE_DE_CHAR:
            if (cp_chaine) {
                dest->value.chaine = copy_chaine(src->value.chaine);
            } else {
                dest->value.chaine = src->value.chaine;
                dest->type = CHAINE_DE_CHAR;
            }
            break;

        case POINTEUR:
            dest->value.ptr = src->value.ptr;
            src->value.ptr->references++;
            break;

        case UNDEFINED:
            break;

            /*default:
                print_val(src, true, NULL, NULL);
                custom_error("type de val_t non reconnu dans copy_val", NULL, NULL);
                break;
             */
    }
}

int get_as_int(val_t* v, phrase_t* p, environnement_t* env) {
    switch (v->type) {
        case INT:
            return v->value.entier;
            break;
        case FLOAT:
            return (int)v->value.flottant;
            break;
        case BOOL:
            if (v->value.booleen) {
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
            return (float)v->value.entier;
            break;
        case FLOAT:
            return v->value.flottant;
            break;
        case BOOL:
            if (v->value.booleen) {
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
            return v->value.entier != 0;
            break;
        case FLOAT:
            return v->value.flottant != 0.0;
            break;
        case BOOL:
            return v->value.booleen;
            break;
        case CHAINE_DE_CHAR:
            return v->value.chaine->chars_len != 0;
            break;
        case LISTE:
            return v->value.liste->valeursLen != 0;
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
    if (v->type == POINTEUR) {
        v->value.ptr->references--;
    }
    v->type = INT;
    v->value.entier = valeur;
}
void set_float(val_t* v, float valeur) {
    if (v->type == POINTEUR) {
        v->value.ptr->references--;
    }
    v->type = FLOAT;
    v->value.flottant = valeur;
}
void set_bool(val_t* v, bool valeur) {
    if (v->type == POINTEUR) {
        v->value.ptr->references--;
    }
    v->type = BOOL;
    v->value.booleen = valeur;
}

void set_liste(val_t* v, liste_t* l) {
    if (v->type == POINTEUR) {
        v->value.ptr->references--;
    }
    v->type = LISTE;
    v->value.liste = l;
}

void set_char(val_t* v, chaine_t* chaine) {
    if (v->type == POINTEUR) {
        v->value.ptr->references--;
    }
    v->type = CHAINE_DE_CHAR;  // pas super, on pourrait avoir un pointeur sur une chaîne de caractères
    v->value.chaine = chaine;
}

void set_undefined(val_t* v) {
    if (v->type == POINTEUR) {
        v->value.ptr->references--;
    }
    v->type = UNDEFINED;
}

void set_pointer(val_t* ptr, val_t* dest, phrase_t* p, environnement_t* env) {
    if (ptr->type == POINTEUR) {
        ptr->value.ptr->references--;
    }
    // printf("ptr %p , dest  %p\n", ptr, dest);
    ptr->type = POINTEUR;
    ptr->value.ptr = dest;
    dest->references++;

    if (ptr->references > 1) {  // s'assure qu'il n'y ait pas de boucle de pointeurs
        if (boucle_pointeur(ptr, p, env)) {
            custom_error("Il y a une boucle de pointeurs.", p, env);
        }
    }
}

char* str_type(val_t* v) {
    char* type = safe_alloc(NULL, 30 * sizeof(char));

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
        case POINTEUR:
            strcpy(type, "pointeur");
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
            return v1->value.entier == v2->value.entier;
        case BOOL << 4 | INT:
            return v1->value.booleen == v2->value.entier;
        case INT << 4 | BOOL:
            return v1->value.entier == v2->value.booleen;
            break;

        case FLOAT << 4 | FLOAT:
            return v1->value.flottant == v2->value.flottant;
        case FLOAT << 4 | INT:
            return v1->value.flottant == v2->value.entier;
        case INT << 4 | FLOAT:
            return v1->value.entier == v2->value.flottant;
        case FLOAT << 4 | BOOL:
            return v1->value.flottant == v2->value.booleen;
        case BOOL << 4 | FLOAT:
            return v1->value.booleen == v2->value.flottant;
            break;

        case BOOL << 4 | BOOL:
            return v1->value.booleen == v2->value.booleen;
            break;

        case CHAINE_DE_CHAR << 4 | CHAINE_DE_CHAR:

            return strcmp(v1->value.chaine->chars, v2->value.chaine->chars) == 0;
            break;

        case LISTE << 4 | LISTE:

            return is_equal_list(v1->value.liste, v2->value.liste, p, env);
            break;

        case UNDEFINED << 4 | INT:
        case UNDEFINED << 4 | FLOAT:
        case UNDEFINED << 4 | BOOL:
        case UNDEFINED << 4 | CHAINE_DE_CHAR:
        case UNDEFINED << 4 | LISTE:
        case UNDEFINED << 4 | POINTEUR:
        case INT << 4 | UNDEFINED:
        case FLOAT << 4 | UNDEFINED:
        case BOOL << 4 | UNDEFINED:
        case CHAINE_DE_CHAR << 4 | UNDEFINED:
        case LISTE << 4 | UNDEFINED:
        case POINTEUR << 4 | UNDEFINED:
            return false;
            break;

        case UNDEFINED << 4 | UNDEFINED:
            return true;
            break;

        default: {
            char* error = safe_alloc(NULL, 128 * sizeof(char));
            sprintf(error, "Impossible de comparer l'égalité d'un élément de type %s et d'un élément de type %s.", str_type(v1), str_type(v2));
            custom_error(error, p, env);
            return false;
            break;
        }
    }
}

bool is_greater(val_t* v1, val_t* v2, phrase_t* p, environnement_t* env) {  // not strict greater
    switch (v1->type << 4 | v2->type) {
        case INT << 4 | INT:
            return v1->value.entier >= v2->value.entier;
        case BOOL << 4 | INT:
            return v1->value.booleen >= v2->value.entier;
        case INT << 4 | BOOL:
            return v1->value.entier >= v2->value.booleen;
            break;

        case FLOAT << 4 | FLOAT:
            return v1->value.flottant >= v2->value.flottant;
        case FLOAT << 4 | INT:
            return v1->value.flottant >= v2->value.entier;
        case INT << 4 | FLOAT:
            return v1->value.entier >= v2->value.flottant;
        case FLOAT << 4 | BOOL:
            return v1->value.flottant >= v2->value.booleen;
        case BOOL << 4 | FLOAT:
            return v1->value.booleen >= v2->value.flottant;
            break;

        case BOOL << 4 | BOOL:
            return v1->value.booleen >= v2->value.booleen;
            break;

        case CHAINE_DE_CHAR << 4 | CHAINE_DE_CHAR:

            return strcmp(v1->value.chaine->chars, v2->value.chaine->chars) >= 0;
            break;

        case LISTE << 4 | LISTE:
            return is_greater_list(v1->value.liste, v1->value.liste, p, env);
            break;

        case UNDEFINED << 4 | INT:
        case UNDEFINED << 4 | FLOAT:
        case UNDEFINED << 4 | BOOL:
        case UNDEFINED << 4 | LISTE:
        case UNDEFINED << 4 | CHAINE_DE_CHAR:
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
            char* error = safe_alloc(NULL, 100 * sizeof(char));
            sprintf(error, "Impossible de comparer un élément de type %s et un élément de type %s.", str_type(v1), str_type(v2));
            custom_error(error, p, env);
            break;
        }
    }
    return false;
}

bool is_strict_greater(val_t* v1, val_t* v2, phrase_t* p, environnement_t* env) {
    switch (v1->type << 4 | v2->type) {
        case INT << 4 | INT:
            return v1->value.entier > v2->value.entier;
        case BOOL << 4 | INT:
            return v1->value.booleen > v2->value.entier;
        case INT << 4 | BOOL:
            return v1->value.entier > v2->value.booleen;
            break;

        case FLOAT << 4 | FLOAT:
            return v1->value.flottant > v2->value.flottant;
        case FLOAT << 4 | INT:
            return v1->value.flottant > v2->value.entier;
        case INT << 4 | FLOAT:
            return v1->value.entier > v2->value.flottant;
        case FLOAT << 4 | BOOL:
            return v1->value.flottant > v2->value.booleen;
        case BOOL << 4 | FLOAT:
            return v1->value.booleen > v2->value.flottant;
            break;

        case BOOL << 4 | BOOL:
            return v1->value.booleen > v2->value.booleen;
            break;

        case CHAINE_DE_CHAR << 4 | CHAINE_DE_CHAR:

            return strcmp(v1->value.chaine->chars, v2->value.chaine->chars) > 0;
            break;

        case LISTE << 4 | LISTE:

            return is_strict_greater_list(v1->value.liste, v2->value.liste, p, env);
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
            char* error = safe_alloc(NULL, 100 * sizeof(char));
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
            if (v->value.booleen) {
                printf("vrai");
            } else {
                printf("faux");
            }
            break;
        }

        case INT: {
            char* str = str_from_int(v->value.entier);
            printf("%s", str);
            free(str);
            break;
        }

        case FLOAT: {
            char* str = str_from_float(v->value.flottant);
            printf("%s", str);
            free(str);
            break;
        }

        case LISTE:
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

        case POINTEUR:
            printf("ptr");
            printf(" -> %p", v->value.ptr);
            break;

        default:
            custom_error("le type de val_t n'est pas reconnu dans print_val", p, env);
            break;
    }

    if (new_line) {
        printf("\n");
    }
    fflush(stdout);
};
