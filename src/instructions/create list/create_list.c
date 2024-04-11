#include "../instructions.h"
bool test_inst_create_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, CREATION_LISTE_S, &len, DEFAULT_SEPARATOR);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    phrase->phraseId = CREATION_LISTE;
    phrase->constant = true;
    addToVariableList(function->env, new_variable(result[0], new_val_t(LISTE)));
    free(result);
    return true;
}
