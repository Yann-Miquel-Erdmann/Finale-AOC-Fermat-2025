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
        custom_error("too many arguments given", phrase, function->env);
    }

    phrase->phraseId = EXPR_LISTE;

    phrase->variableId = getVariableId(function->env, result[0]);
    if (phrase->variableId == -1) {
        custom_error("variable not found", phrase, function->env);
    }

 

    free_l(result, len);

    return true;
};
