#include "../../structures/val.h"
#include "../instructions.h"

bool test_inst_var_init(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** l = malloc(sizeof(char*));
    int len = 0;

    bool result = analyse(phrase, DEFINITION_VARIABLE_AVEC_INIT_S, l, &len, false);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    phrase->phraseId = DEFINITION_VARIABLE_AVEC_INIT;
    phrase->constant = false;
    phrase->variable = getVariable(function->env, l[0]);
    if (phrase->variable == NULL) {
        phrase->variable = new_variable(l[0], new_val_t(UNDEFINED));
        addToVariableList(function->env, phrase->variable);
    }
    free(l);

    return true;
}
