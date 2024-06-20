#include "../instructions.h"

bool test_inst_for_loop(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, POUR_SANS_PAS_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase, function->env);
    }

    phrase->phraseId = POUR_SANS_PAS;

    phrase->variableId = getVariableId(function->env, result[0]);

    if (phrase->variableId == -1) {
        variable_t* var = new_variable(result[0], new_val_t(UNDEFINED));
        phrase->variableId = function->env->variableListLen;
        addToVariableList(function->env, var);
    } else {
        free(result[0]);
    }

    free(result);
    return true;
}