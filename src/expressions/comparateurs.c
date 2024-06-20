#include "comparateurs.h"

#include "../constants.h"

void egalite(phrase_t* phrase, environnement_t* env) {
    env->phraseValeurs[phrase->uniqueId]->value.booleen = is_equal(env->phraseValeurs[phrase->args[0]->uniqueId], env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env);
};

void inegalite(phrase_t* phrase, environnement_t* env) {
    env->phraseValeurs[phrase->uniqueId]->value.booleen = !is_equal(env->phraseValeurs[phrase->args[0]->uniqueId], env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env);
};

void plus_grand(phrase_t* phrase, environnement_t* env) {
    env->phraseValeurs[phrase->uniqueId]->value.booleen = is_greater(env->phraseValeurs[phrase->args[0]->uniqueId], env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env);
};

void strict_plus_grand(phrase_t* phrase, environnement_t* env) {
    env->phraseValeurs[phrase->uniqueId]->value.booleen = is_strict_greater(env->phraseValeurs[phrase->args[0]->uniqueId], env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env);
};

void plus_petit(phrase_t* phrase, environnement_t* env) {
    env->phraseValeurs[phrase->uniqueId]->value.booleen = !is_strict_greater(env->phraseValeurs[phrase->args[0]->uniqueId], env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env);
};

void strict_plus_petit(phrase_t* phrase, environnement_t* env) {
    env->phraseValeurs[phrase->uniqueId]->value.booleen = !is_greater(env->phraseValeurs[phrase->args[0]->uniqueId], env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env);
};
