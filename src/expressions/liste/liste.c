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
    variable_t* var = getVariable(function->env, result[0]);
    if (var == NULL) {
        custom_error("variable not found", phrase);
    }

    phrase->variable = var;

    free_l(result, len);

    return true;
};
