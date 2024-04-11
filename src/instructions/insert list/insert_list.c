#include "../instructions.h"

bool test_inst_insert_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, INSERTION_LISTE_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }
    
    phrase->phraseId = INSERTION_LISTE;
    phrase->valeur = new_val_t(UNDEFINED);
    set_liste(phrase->valeur, getVariable(function->env, result[0])->valeur->liste);
    free_l(result, len);

    return true;
}
