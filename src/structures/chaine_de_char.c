#include "chaine_de_char.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../constants.h"

void free_chaine_t(chaine_t* c) {
    // printf("free chaine %p\n", c);
    free(c->chars);
    free(c);
}

chaine_t* new_chaine_t(char* c) {
    chaine_t* chaine = malloc(sizeof(chaine_t));
    
    int len = (int)strlen(c);
    int size = DEFAULT_CHAINE_CHARS_SIZE * pow(2,(int)(((log(len) - log(DEFAULT_CHAINE_CHARS_SIZE))/log(2)) + 1));
    chaine->chars = malloc(size * sizeof(char));
    strcpy(chaine->chars, c);
    
    chaine->chars_len = len;
    chaine->chars_size = size;
    return chaine;
}

chaine_t* copy_chaine(chaine_t* src) {
    chaine_t* new_chaine = malloc(sizeof(chaine_t));
    new_chaine->chars = malloc(src->chars_size * sizeof(char));
    new_chaine->chars_len = src->chars_len;
    new_chaine->chars_size = src->chars_size;
    for (int i = 0; i <= src->chars_len; i++) {
        new_chaine->chars[i] = src->chars[i];
    }
    return new_chaine;
}


void ajouter_char(chaine_t* c, char e) {
    if (c->chars_len == c->chars_size) {
        c->chars_size *= 2;
        c->chars = realloc(c->chars, c->chars_size * sizeof(char));
    }
    c->chars[c->chars_len] = e;
    c->chars_len++;
}

void concat_chaines(chaine_t* c1, chaine_t* c2) {
    if (c1->chars_size > c1->chars_len + c2->chars_len) {
        c1->chars_size *= pow(2, (int)(((log(c1->chars_len + c2->chars_len) - log(c1->chars_size)) / log(2)) + 1));
    }
    c1->chars = realloc(c1->chars, c1->chars_size * sizeof(char));

    for (int i = 0; i < c2->chars_len; i++) {
        c1->chars[c1->chars_len] = c2->chars[i];
        c1->chars_len++;
    }
}
