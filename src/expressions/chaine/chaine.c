#include "../../structures/val.h"
#include "../expressions.h"

bool test_expr_chaine(phrase_t* phrase, environnement_t* env) {
    if (phrase->phraseId != -1) {
        return false;
    }
    int len = 0;

    char** result = analyse(phrase, EXPR_CHAINE_S, &len, STRING_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase, env);
    } else if (len < 1) {
        custom_error("not enough arguments given", phrase, env);
    }

    phrase->phraseId = EXPR_CHAINE;

    phrase->constant = true;
    phrase->expr = true;

    chaine_t* c = new_chaine_t(result[0]);
    set_char(getValeur(env, phrase->uniqueId), c);
    getValeur(env, phrase->uniqueId)->to_free_chaine = true;

    free(result);

    return true;
}
