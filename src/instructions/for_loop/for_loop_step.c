#include "../instructions.h"

bool test_inst_for_loop_step(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, POUR_AVEC_PAS_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    phrase->phraseId = POUR_AVEC_PAS;
    phrase->inst = true;

    phrase->variable = getVariable(function->env, result[0]);
    if (phrase->variable == NULL) {
        phrase->variable = new_variable(result[0], new_val_t(UNDEFINED));
        set_undefined(phrase->variable->valeur);
        addToVariableList(function->env, phrase->variable);
    } else {
        free(result[0]);
        set_undefined(phrase->variable->valeur);
    }

    free(result);
    return true;
}