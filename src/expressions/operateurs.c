#include "operateurs.h"

#include "../constants.h"
#include "../custom_error.h"

void somme(phrase_t* phrase, environnement_t* env) {
    if (env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT || env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT) {
        set_float(env->phraseValeurs[phrase->uniqueId], get_as_float(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) + get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    } else {
        set_int(env->phraseValeurs[phrase->uniqueId], get_as_int(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) + get_as_int(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    }
};

void difference(phrase_t* phrase, environnement_t* env) {
    if (env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT || env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT) {
        set_float(env->phraseValeurs[phrase->uniqueId], get_as_float(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) - get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    } else {
        set_int(env->phraseValeurs[phrase->uniqueId], get_as_int(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) - get_as_int(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    }
};

void produit(phrase_t* phrase, environnement_t* env) {
    if (env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT || env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT) {
        set_float(env->phraseValeurs[phrase->uniqueId], get_as_float(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) * get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    } else {
        set_int(env->phraseValeurs[phrase->uniqueId], get_as_int(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) * get_as_int(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    }
};

void quotient(phrase_t* phrase, environnement_t* env) {
    if (get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env) == 0) {
        custom_error("Division par 0", phrase, env);
    }
    set_float(env->phraseValeurs[phrase->uniqueId], get_as_float(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) / get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    if ((float)get_as_int(env->phraseValeurs[phrase->uniqueId], phrase, env) == get_as_float(env->phraseValeurs[phrase->uniqueId], phrase, env)) {
        set_int(env->phraseValeurs[phrase->uniqueId], get_as_int(env->phraseValeurs[phrase->uniqueId], phrase, env));
    }
};

void quotient_entier(phrase_t* phrase, environnement_t* env) {
    if (get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env) == 0) {
        custom_error("Division par 0", phrase, env);
    }

    if (env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT || env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT) {
        set_float(env->phraseValeurs[phrase->uniqueId], (int)(get_as_float(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) / get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env)));
    } else {
        set_int(env->phraseValeurs[phrase->uniqueId], (int)(get_as_int(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) / get_as_int(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env)));
    }
};

void reste(phrase_t* phrase, environnement_t* env) {
    if (get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env) == 0) {
        custom_error("Division par 0", phrase, env);
    }
    
    if (env->phraseValeurs[phrase->args[0]->uniqueId]->type == FLOAT || env->phraseValeurs[phrase->args[1]->uniqueId]->type == FLOAT) {
        set_float(env->phraseValeurs[phrase->uniqueId],
                  (get_as_float(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) / get_as_float(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env)) -
                      (get_as_int(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) / get_as_int(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env)));
    } else {
        set_int(env->phraseValeurs[phrase->uniqueId],
                get_as_int(env->phraseValeurs[phrase->args[0]->uniqueId], phrase, env) % get_as_int(env->phraseValeurs[phrase->args[1]->uniqueId], phrase, env));
    }
};

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
