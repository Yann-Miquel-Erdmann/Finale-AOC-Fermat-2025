#include "../expressions.h"
bool test_expr_taille(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, TAILLE_S, &len, DEFAULT_SEPARATOR);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }

    phrase->phraseId = TAILLE;
    free_l(result, len);
    // renvoie true si l'expression est une taille list
    return true;
}
