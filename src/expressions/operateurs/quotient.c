#include "../../custom_error.h"
#include "../../constants.h"
#include "operateurs.h"

void quotient(phrase_t* phrase, environnement_t* env) {
    if (get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env) == 0) {
        custom_error("Division par 0", phrase, env);
    }
    set_float(env->phraseValeurs[phrase->uniqueId], get_as_float(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) / get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    if ((float)get_as_int(env->phraseValeurs[phrase->uniqueId], phrase, env) == get_as_float(env->phraseValeurs[phrase->uniqueId], phrase, env)) {
        set_int(env->phraseValeurs[phrase->uniqueId], get_as_int(env->phraseValeurs[phrase->uniqueId], phrase, env));
    }
};