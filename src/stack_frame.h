#ifndef STACK_FRAME_H
#define STACK_FRAME_H

#include "phrase.h"
#include "environnement.h"

typedef struct stack_frame{
    phrase_t* ast;
    environnement_t * var_env;
    val_t* result; // pointeur vers l'adresse où mettre le résultat de la fonction
} stack_frame_t;

#endif  