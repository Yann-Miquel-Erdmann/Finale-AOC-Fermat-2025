#include "../instructions.h"
bool test_inst_create_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** l = malloc(sizeof(char*));
    int len = 0;

    bool result = analyse(phrase, CREATION_LISTE_S, l, &len, false);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    phrase->phraseId = CREATION_LISTE;
    phrase->constant = true;
    addToVariableList(function->env, new_variable(l[0], new_val_t(LISTE)));

    return true;
}
