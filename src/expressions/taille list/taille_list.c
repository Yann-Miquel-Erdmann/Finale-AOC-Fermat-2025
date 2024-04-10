#include "../expressions.h"

bool test_expr_taille_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** l = malloc(sizeof(char*));
    int len = 0;

    bool result = analyse(phrase, TAILLE_LISTE_S, l, &len, false);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }
    
    phrase->phraseId = TAILLE_LISTE;
    set_liste(phrase->valeur, getVariable(function->env, l[0])->valeur->liste);
    free_l(l, len);
    // renvoie true si l'expression est une taille list
    return true;
}
