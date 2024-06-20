#include "../../constants.h"
#include "../../custom_error.h"
#include "operateurs.h"

void somme(phrase_t* phrase, environnement_t* env) {
    switch (env->phraseValeurs[phrase->args[0]->uniqueId]->type << 4 | env->phraseValeurs[phrase->args[1]->uniqueId]->type) {
        case INT << 4 | INT:
            env->phraseValeurs[phrase->uniqueId]->value.entier = env->phraseValeurs[phrase->args[0]->uniqueId]->value.entier + env->phraseValeurs[phrase->args[1]->uniqueId]->value.entier;
            env->phraseValeurs[phrase->uniqueId]->type = INT;
            break;
        case BOOL << 4 | INT:
            env->phraseValeurs[phrase->uniqueId]->value.entier = env->phraseValeurs[phrase->args[0]->uniqueId]->value.booleen + env->phraseValeurs[phrase->args[1]->uniqueId]->value.entier;
            env->phraseValeurs[phrase->uniqueId]->type = INT;
            break;
        case INT << 4 | BOOL:
            env->phraseValeurs[phrase->uniqueId]->value.entier = env->phraseValeurs[phrase->args[0]->uniqueId]->value.entier + env->phraseValeurs[phrase->args[1]->uniqueId]->value.booleen;
            env->phraseValeurs[phrase->uniqueId]->type = INT;
            break;
        case BOOL << 4 | BOOL:
            env->phraseValeurs[phrase->uniqueId]->value.entier = env->phraseValeurs[phrase->args[0]->uniqueId]->value.booleen + env->phraseValeurs[phrase->args[1]->uniqueId]->value.booleen;
            env->phraseValeurs[phrase->uniqueId]->type = INT;
            break;

        case FLOAT << 4 | FLOAT:
            env->phraseValeurs[phrase->uniqueId]->value.flottant = env->phraseValeurs[phrase->args[0]->uniqueId]->value.flottant + env->phraseValeurs[phrase->args[1]->uniqueId]->value.flottant;
            env->phraseValeurs[phrase->uniqueId]->type = FLOAT;
            break;
        case INT << 4 | FLOAT:
            env->phraseValeurs[phrase->uniqueId]->value.flottant = env->phraseValeurs[phrase->args[0]->uniqueId]->value.entier + env->phraseValeurs[phrase->args[1]->uniqueId]->value.flottant;
            env->phraseValeurs[phrase->uniqueId]->type = FLOAT;
            break;
        case FLOAT << 4 | INT:
            env->phraseValeurs[phrase->uniqueId]->value.flottant = env->phraseValeurs[phrase->args[0]->uniqueId]->value.flottant + env->phraseValeurs[phrase->args[1]->uniqueId]->value.entier;
            env->phraseValeurs[phrase->uniqueId]->type = FLOAT;
            break;
        case BOOL << 4 | FLOAT:
            env->phraseValeurs[phrase->uniqueId]->value.flottant = env->phraseValeurs[phrase->args[0]->uniqueId]->value.booleen + env->phraseValeurs[phrase->args[1]->uniqueId]->value.flottant;
            env->phraseValeurs[phrase->uniqueId]->type = FLOAT;
            break;
        case FLOAT << 4 | BOOL:
            env->phraseValeurs[phrase->uniqueId]->value.flottant = env->phraseValeurs[phrase->args[0]->uniqueId]->value.flottant + env->phraseValeurs[phrase->args[1]->uniqueId]->value.booleen;
            env->phraseValeurs[phrase->uniqueId]->type = FLOAT;

            break;

        default:
            custom_error("Type non géré reste", phrase, env);
            break;
    }

};