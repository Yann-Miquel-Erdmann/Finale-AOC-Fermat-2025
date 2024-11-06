#include "chaine_de_char.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../constants.h"
#include "../custom_error.h"
#include "../safe_alloc.h"
#include "val.h"

void free_chaine_t(chaine_t* c) {
    // printf("free chaine %p\n", c);
    free(c->chars);
    free(c);
}

chaine_t* new_chaine_t(char* c) {
    chaine_t* chaine = safe_alloc(NULL, sizeof(chaine_t));
    int len = (int)strlen(c);
    int size = DEFAULT_CHAINE_CHARS_SIZE * pow(2,(int)(((log(len) - log(DEFAULT_CHAINE_CHARS_SIZE))/log(2)) + 1));
    if (size == 0){
        size = DEFAULT_CHAINE_CHARS_SIZE;
    }
    chaine->chars = safe_alloc(NULL, size * sizeof(char));
    strcpy(chaine->chars, c);
    
    chaine->chars_len = len;
    chaine->chars_size = size;
    return chaine;
}

val_t* new_chaine_val_t(char* c, bool free_after_use){
    val_t* val = safe_alloc(NULL, sizeof(val_t));
    chaine_t* chaine = safe_alloc(NULL, sizeof(chaine_t));
    int len = (int)strlen(c);
    int size = DEFAULT_CHAINE_CHARS_SIZE * pow(2,(int)(((log(len) - log(DEFAULT_CHAINE_CHARS_SIZE))/log(2)) + 1));
    if (size == 0){
        size = DEFAULT_CHAINE_CHARS_SIZE;
    }
    chaine->chars = safe_alloc(NULL, size * sizeof(char));
    strcpy(chaine->chars, c);
    
    if (free_after_use) {
        free(c);
    }
    
    chaine->chars_len = len;
    chaine->chars_size = size;
    val->value.chaine = chaine;
    val->type = CHAINE_DE_CHAR;
    val->ferme = false;
    val->ouvert = false;
    val->references = 0;
    return val;
}

chaine_t* copy_chaine(chaine_t* src) {
    chaine_t* new_chaine = safe_alloc(NULL, sizeof(chaine_t));
    new_chaine->chars = safe_alloc(NULL, src->chars_size * sizeof(char));
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
        c->chars = safe_alloc(c->chars, c->chars_size * sizeof(char));
    }
    c->chars[c->chars_len] = e;
    c->chars_len++;
}

void ajouter_chaine(chaine_t* c, char* e){
    int len = (int)sizeof(e);
    if (c->chars_size > c->chars_len + len) {
        c->chars_size *= pow(2, (int)(((log(c->chars_len + len) - log(c->chars_size)) / log(2)) + 1));
    }
    c->chars = safe_alloc(c->chars, c->chars_size * sizeof(char));

    for (int i = 0; i < len; i++) {
        c->chars[c->chars_len] = e[i];
        c->chars_len++;
    }
}

void concat_chaines(chaine_t* c1, chaine_t* c2) {
    if (c1->chars_size > c1->chars_len + c2->chars_len) {
        c1->chars_size *= pow(2, (int)(((log(c1->chars_len + c2->chars_len) - log(c1->chars_size)) / log(2)) + 1));
    }
    c1->chars = safe_alloc(c1->chars, c1->chars_size * sizeof(char));

    for (int i = 0; i < c2->chars_len; i++) {
        c1->chars[c1->chars_len] = c2->chars[i];
        c1->chars_len++;
    }
}
