#ifndef expr_h
#define expr_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct expr expr_t;
    
typedef struct expr{
    char* text;
    int len;
    expr_t** expr_list;
    int list_len;
    int value_type;
    
    int operation_num;
    
    int int_final_value;
    float float_final_value;
    bool bool_final_value;
    // à voir si on laisse comme ça
    // je ne sais pas trop comment faire pour l'instant des listes d'éléments de types différents
    
} expr_t;

expr_t* new_expr(void);
void free_expr(expr_t* expr);
void print_expr(expr_t* expr);

#endif
