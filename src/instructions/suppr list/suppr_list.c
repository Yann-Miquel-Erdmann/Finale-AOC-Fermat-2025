#include "../instructions.h"

bool test_inst_suppr_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** l = malloc(sizeof(char*));
    int len = 0;

    bool result = analyse(phrase, SUPPRESSION_LISTE_S, l, &len, false);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    phrase->phraseId = SUPPRESSION_LISTE;
    phrase->valeur = new_val_t(UNDEFINED);
    variable_t* var = getVariable(function->env, l[0]);
    if (var == NULL) {
        custom_error("variable not found", phrase);
    }
    if (var->valeur->type != LISTE) {
        custom_error("variable is not a list", phrase);
    }
    set_liste(phrase->valeur, var->valeur->liste);

    return true;
}
