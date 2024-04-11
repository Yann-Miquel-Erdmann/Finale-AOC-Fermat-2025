#include "../expressions.h"

bool test_expr_access_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, ACCESSION_LISTE_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    } else if (len < 1) {
        custom_error("not enough arguments given", phrase);
    }

    phrase->phraseId = ACCESSION_LISTE;
    variable_t* var = getVariable(function->env, result[0]);
    if (var == NULL) {
        custom_error("variable not found", phrase);
    }
    if (var->valeur->type != LISTE) {
        custom_error("variable is not a list", phrase);
    }
    set_liste(phrase->valeur, var->valeur->liste);
    
    free_l(result, len);
    return true;
}
