#include "../expressions.h"

bool test_expr_access_var(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != NO_ID) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, ACCESSION_VARIABLE_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("L'accession à une variable ne prend pas d'arguments", phrase, function->env);
    }

    phrase->phraseId = ACCESSION_VARIABLE;

    phrase->variableId = getVariableId(function->env, result[0]);
    if (phrase->variableId == -1) {
        custom_error("La variable entrée n'existe pas", phrase, function->env);
    }

    free_l(result, len);

    return true;
}
