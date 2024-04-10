#include "../expressions.h"

bool test_expr_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** l = malloc(sizeof(char*));
    int len = 0;

    bool result = analyse(phrase, EXPR_LISTE_S, l, &len, false);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    printf("l[0]: '%s'\n", l[0]);

    phrase->phraseId = EXPR_LISTE;
    phrase->constant = true;
    set_liste(phrase->valeur, getVariable(function->env, l[0])->valeur->liste);

    free_l(l, len);

    return true;
};