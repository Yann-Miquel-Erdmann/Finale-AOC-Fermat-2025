#include "../../constants.h"
#include "../../custom_error.h"
#include "operateurs.h"

void moins(phrase_t* phrase, environnement_t* env) {
    switch (env->phraseValeurs[phrase->args[0]->uniqueId]->type) {
        case INT:
        case BOOL:
            env->phraseValeurs[phrase->uniqueId]->value.entier = -get_as_int(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env);
            env->phraseValeurs[phrase->uniqueId]->type = INT;
            break;
        case FLOAT:
            env->phraseValeurs[phrase->uniqueId]->value.flottant = -get_as_float(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env);
            env->phraseValeurs[phrase->uniqueId]->type = FLOAT;

            break;

        default:
            custom_error("Le type donnée ne peut pas être nié.", phrase, env);
            break;
    }

};
