#include "val.h"

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "custom_error.h"
val_t* new_val() {
    val_t* val = malloc(sizeof(val_t));
    if (val == NULL) {
        custom_error("erreur d'allocation\n");
        exit(1);
    }
    return val;
};

void free_val(val_t* v) {
    free(v);
};

int get_int(val_t* v) {
    if (v->type != INT) {
        custom_error("le type de val_t ne correspond pas\n");
        exit(1);
    }
    return *((int*)&(v->value));
};
float get_float(val_t* v) {
    if (v->type != FLOAT) {
        custom_error("le type de val_t ne correspond pas\n");
        exit(1);
    }
    return *((float*)&(v->value));
};

bool get_bool(val_t* v) {
    if (v->type != BOOL) {
        custom_error("le type de val_t ne correspond pas\n");
        exit(1);
    }
    return *((bool*)&(v->value));
};

void set_int(val_t* v, int valeur) {
    v->type = INT;
    v->value = *((int*)&valeur);
};
void set_float(val_t* v, float valeur) {
    v->type = FLOAT;
    v->value = *((int*)&valeur);
};
void set_bool(val_t* v, bool valeur) {
    v->type = BOOL;
    v->value = *((int*)&valeur);
};

void print_val(val_t* v) {
    switch (v->type) {
        case INT:
            printf("integer: %i\n", get_int(v));
            break;
        case FLOAT:
            printf("float: %i\n", get_float(v));
            break;
        case BOOL:
            if (get_int(v) == 1) {
                printf("bool: true\n");
            } else {
                printf("bool: false\n");
            }
            break;

        default:
            custom_error("le type de vat_t n'est pas reconnu\n");
            exit(1);
            break;
    }
};
