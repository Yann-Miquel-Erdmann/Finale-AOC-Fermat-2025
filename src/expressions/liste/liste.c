#include "../expressions.h"

bool test_expr_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, EXPR_LISTE_S, &len, DEFAULT_SEPARATOR);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    phrase->phraseId = EXPR_LISTE;
    phrase->constant = true;
    set_liste(phrase->valeur, getVariable(function->env, result[0])->valeur->liste);

    free_l(result, len);

    return true;
};
