#if !defined(CUSTOM_ERROR_H)
#define CUSTOM_ERROR_H

#include <stdbool.h>

#include "structures/phrase.h"

// afficher le message d'erreur dans la console d'erreur puis arrête le programme
void custom_error(char* err_message, phrase_t* p, environnement_t* env) __dead2;
void set_ignore(void);

#endif  // CUSTOM_ERROR_H
