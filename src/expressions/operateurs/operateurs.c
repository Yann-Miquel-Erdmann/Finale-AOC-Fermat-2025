#include "operateurs.h"

#include "../../constants.h"
#include "../../custom_error.h"

void negation_booleenne(phrase_t* phrase, environnement_t* env) {
    set_bool(env->phraseValeurs[phrase->uniqueId], !get_as_bool(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env));
};

void ou_booleen(phrase_t* phrase, environnement_t* env) {
    set_bool(env->phraseValeurs[phrase->uniqueId],
             get_as_bool(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) || (get_as_bool(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env)));
}

void et_booleen(phrase_t* phrase, environnement_t* env) {
    set_bool(env->phraseValeurs[phrase->uniqueId],
             get_as_bool(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) && (get_as_bool(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env)));
}
