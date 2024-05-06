#include "../instructions.h"

bool test_inst_modif_var(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, MODIFICATION_VARIABLE_S, &len, DEFAULT_SEPARATOR);
    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    phrase->phraseId = MODIFICATION_VARIABLE;
    phrase->variable = getVariable(function->env, result[0]);
    if (phrase->variable == NULL) {
        custom_error("variable not found", phrase);
    }


    free_l(result, len);

    return true;
}
