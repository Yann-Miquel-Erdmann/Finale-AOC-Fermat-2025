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
        custom_error("too many arguments given", phrase);
    }
    if (phrase->argsLen != 1 || phrase->innerPhraseLen > 0){
        custom_error("Initialisation de variable prend un seul argument", phrase);
    }

    phrase->phraseId = DEFINITION_VARIABLE_AVEC_INIT;
    phrase->constant = false;
    phrase->variable = getVariable(function->env, result[0]);
    if (phrase->variable == NULL) {
        phrase->variable = new_variable(result[0], new_val_t(UNDEFINED));
        addToVariableList(function->env, phrase->variable);
    }else{
        free(result[0]);
    }

    free(result);

    return true;
}
