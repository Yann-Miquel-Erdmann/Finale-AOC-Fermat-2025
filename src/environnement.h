#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H
#include "variable.h"

typedef struct environnement{
    variable_t** variable_list;
    int variable_list_len;
    int variable_list_size;
} environnement_t;


#endif