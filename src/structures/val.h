#ifndef val_h
#define val_h
#include <stdbool.h>

typedef struct liste liste_t;
typedef struct val {
    char type;
    int value;
    liste_t* liste;
} val_t;

val_t* new_val_t(char type);
void free_val_t(val_t* v);

int get_int(val_t* v);
float get_float(val_t* v);
bool get_bool(val_t* v);
liste_t* get_liste(val_t* v);

int get_as_int(val_t* v);
float get_as_float(val_t* v);
bool get_as_bool(val_t* v);

void set_int(val_t* v, int valeur);
void set_float(val_t* v, float valeur);
void set_bool(val_t* v, bool valeur);
void set_undefined(val_t* v);
void set_liste(val_t*, liste_t* l);

void copy_val(val_t* dest, val_t* src);

void print_val(val_t* v);

#endif
