#include "../../structures/val.h"
#include "../instructions.h"

bool test_inst_var_init(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, DEFINITION_VARIABLE_AVEC_INIT_S, &len, DEFAULT_SEPARATOR);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase, function->env);
    }
    if (phrase->argsLen != 1 || phrase->innerPhraseLen > 0){
        custom_error("Initialisation de variable prend un seul argument", phrase, function->env);
    }

    phrase->phraseId = DEFINITION_VARIABLE_AVEC_INIT;
    phrase->constant = false;
    phrase->variableId = getVariableId(function->env, result[0]);
    if (phrase->variableId == -1) {
        variable_t* var = new_variable(result[0], new_val_t(UNDEFINED));
        phrase->variableId = function->env->variable_list_len;
        addToVariableList(function->env, var);

    } else {
        free(result[0]);
    }

    free(result);

    return true;
}
