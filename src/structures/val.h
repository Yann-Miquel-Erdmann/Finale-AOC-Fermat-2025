#ifndef val_h
#define val_h
#include <stdbool.h>

typedef struct val {
    char type;
    int value;
} val_t;

val_t* new_val(void);
void free_val_t(val_t* v);

int get_int(val_t* v);
float get_float(val_t* v);
bool get_bool(val_t* v);

int get_as_int(val_t* v);
float get_as_float(val_t* v);
bool get_as_bool(val_t* v);

void set_int(val_t* v, int valeur);
void set_float(val_t* v, float valeur);
void set_bool(val_t* v, bool valeur);
void set_undefined(val_t* v);

void copy_val(val_t* dest, val_t* src);

void print_val(val_t* v);

#endif
