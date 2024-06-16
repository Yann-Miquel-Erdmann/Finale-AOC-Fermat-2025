#include "comparateurs.h"

#include "../constants.h"

void egalite(phrase_t* phrase, environnement_t* env) {
    set_bool(env->phraseValeurs[phrase->uniqueId], is_equal(getValeur(env, phrase->args[0]->uniqueId), getValeur(env, phrase->args[1]->uniqueId), phrase, env));
};

void inegalite(phrase_t* phrase, environnement_t* env) {
    set_bool(env->phraseValeurs[phrase->uniqueId], !is_equal(getValeur(env, phrase->args[0]->uniqueId), getValeur(env, phrase->args[1]->uniqueId), phrase, env));
};

void plus_grand(phrase_t* phrase, environnement_t* env) {
    set_bool(env->phraseValeurs[phrase->uniqueId], is_greater(getValeur(env, phrase->args[0]->uniqueId), getValeur(env, phrase->args[1]->uniqueId), phrase, env));
};

void strict_plus_grand(phrase_t* phrase, environnement_t* env) {
    set_bool(env->phraseValeurs[phrase->uniqueId], is_strict_greater(getValeur(env, phrase->args[0]->uniqueId), getValeur(env, phrase->args[1]->uniqueId), phrase, env));
};

void plus_petit(phrase_t* phrase, environnement_t* env) {
    set_bool(env->phraseValeurs[phrase->uniqueId], !is_strict_greater(getValeur(env, phrase->args[0]->uniqueId), getValeur(env, phrase->args[1]->uniqueId), phrase, env));
};

void strict_plus_petit(phrase_t* phrase, environnement_t* env) {
    set_bool(env->phraseValeurs[phrase->uniqueId], !is_greater(getValeur(env, phrase->args[0]->uniqueId), getValeur(env, phrase->args[1]->uniqueId), phrase, env));
};
