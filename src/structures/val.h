#ifndef val_h
#define val_h
#include <stdbool.h>

#include "chaine_de_char.h"

typedef struct liste liste_t;
typedef struct val {
    char type;
    long int value;
    bool to_free_list;
    bool to_free_chaine;
    liste_t* liste;
    chaine_t* chaine;
} val_t;

typedef struct phrase phrase_t;

val_t* new_val_t(char type);
void free_val_t(val_t* v, bool free_chaine, bool free_liste);
void copy_val(val_t* dest, val_t* src, bool copy_chaine, bool copy_liste);

int get_int(val_t* v, phrase_t* p);
float get_float(val_t* v, phrase_t* p);
bool get_bool(val_t* v, phrase_t* p);
liste_t* get_liste(val_t* v, phrase_t* p);
chaine_t* get_char(val_t* v, phrase_t* p);

int get_as_int(val_t* v, phrase_t* p);
float get_as_float(val_t* v, phrase_t* p);
bool get_as_bool(val_t* v, phrase_t* p);

void set_int(val_t* v, int valeur);
void set_float(val_t* v, float valeur);
void set_bool(val_t* v, bool valeur);
void set_liste(val_t*, liste_t* l);
void set_char(val_t* v, chaine_t* chaine);
void set_undefined(val_t* v);

char* str_type(val_t* v);

bool is_equal(val_t* v1, val_t* v2, phrase_t* p);
bool is_greater(val_t* v1, val_t* v2, phrase_t* p);
bool is_strict_greater(val_t* v1, val_t* v2, phrase_t* p);

void taille(phrase_t* phrase);
    
    void print_val(val_t * v, bool new_line, phrase_t* p);

#endif
