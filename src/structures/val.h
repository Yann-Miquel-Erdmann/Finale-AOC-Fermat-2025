#ifndef val_h
#define val_h
#include <stdbool.h>

#include "chaine_de_char.h"

typedef struct environnement environnement_t;
typedef struct liste liste_t;
typedef struct phrase phrase_t;

typedef struct val {
    int type;
    int value;
    bool to_free_list;
    bool to_free_chaine;
    liste_t* liste;
    chaine_t* chaine;
} val_t;


val_t* new_val_t(char type);
void free_val_t(val_t* v, bool free_chaine, bool free_liste);
void copy_val(val_t* dest, val_t* src, bool copy_chaine, bool copy_liste);

int get_int(val_t* v, phrase_t* p, environnement_t* env);
float get_float(val_t* v, phrase_t* p, environnement_t* env);
bool get_bool(val_t* v, phrase_t* p, environnement_t* env);
liste_t* get_liste(val_t* v, phrase_t* p, environnement_t* env);
chaine_t* get_char(val_t* v, phrase_t* p, environnement_t* env);

int get_as_int(val_t* v, phrase_t* p, environnement_t* env);
float get_as_float(val_t* v, phrase_t* p, environnement_t* env);
bool get_as_bool(val_t* v, phrase_t* p, environnement_t* env);

void set_int(val_t* v, int valeur);
void set_float(val_t* v, float valeur);
void set_bool(val_t* v, bool valeur);
void set_liste(val_t*, liste_t* l);
void set_char(val_t* v, chaine_t* chaine);
void set_undefined(val_t* v);

char* str_type(val_t* v);

bool is_equal(val_t* v1, val_t* v2, phrase_t* p, environnement_t* env);
bool is_greater(val_t* v1, val_t* v2, phrase_t* p , environnement_t* env);
bool is_strict_greater(val_t* v1, val_t* v2, phrase_t* p, environnement_t* env);

void taille(phrase_t* phrase, environnement_t* env);

void print_val(val_t* v, bool new_line, phrase_t* p, environnement_t* env);

#endif
