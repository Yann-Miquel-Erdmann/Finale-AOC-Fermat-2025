#include "chaine_de_char.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../constants.h"

void free_chaine_t(chaine_t* c) {
    free(c->chars);
    free(c);
};

chaine_t* new_chaine_t(char* c) {
    chaine_t* chaine = malloc(sizeof(chaine_t));
    
    int len = strlen(c);
    int size = DEFAULT_CHAINE_CHARS_SIZE * ((int)log((DEFAULT_CHAINE_CHARS_SIZE + len) / DEFAULT_CHAINE_CHARS_SIZE) + 1);
    c = realloc(c, size * sizeof(char));
    chaine->chars = c;
    
    chaine->chars_len = len;
    chaine->chars_size = 0;
};

void ajouter_char(chaine_t* c, char e) {
    if (c->chars_len == c->chars_size) {
        c->chars_size *= 2;
        c->chars = realloc(c->chars, c->chars_size * sizeof(char));
    }
    c->chars[c->chars_len] = e;
    c->chars_len++;
};

void concat_char(chaine_t* c1, chaine_t* c2) {
    if (c1->chars_size > c1->chars_len + c2->chars_len) {
        c1->chars_size *= (int)log((c1->chars_len + c2->chars_len) / c1->chars_len) + 1;
    }
    c1->chars = realloc(c1->chars, c1->chars_size * sizeof(char));

    for (int i = 0; i < c2->chars_len; i++) {
        c1->chars[c1->chars_len] = c2->chars[i];
        c1->chars_len++;
    }
};
