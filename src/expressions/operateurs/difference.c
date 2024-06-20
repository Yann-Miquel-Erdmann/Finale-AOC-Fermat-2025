#include "../../constants.h"
#include "../../custom_error.h"
#include "operateurs.h"

void difference(phrase_t* phrase, environnement_t* env) {
    if (env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT || env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT) {
        set_float(env->phraseValeurs[phrase->uniqueId], get_as_float(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) - get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    } else {
        set_int(env->phraseValeurs[phrase->uniqueId], get_as_int(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) - get_as_int(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    }
};