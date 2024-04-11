#include "../expressions.h"

bool test_expr_access_var(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, ACCESSION_VARIABLE_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    phrase->phraseId = ACCESSION_VARIABLE;
    phrase->constant = false;
    phrase->variable = getVariable(function->env, result[0]);

    return true;
}
