#include "../instructions.h"

bool test_inst_insert_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** l = malloc(sizeof(char*));
    int len = 0;

    bool result = analyse(phrase, INSERTION_LISTE_S, l, &len, false);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }
    
    phrase->phraseId = INSERTION_LISTE;
    phrase->valeur = new_val_t(UNDEFINED);
    set_liste(phrase->valeur, getVariable(function->env, l[0])->valeur->liste);

    // renvoie true si l'expression est une add list
    return phrase->phraseId != -1;
}