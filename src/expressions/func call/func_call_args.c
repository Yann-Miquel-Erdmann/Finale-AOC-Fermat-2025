#include "../expressions.h"

bool test_expr_func_call_args(phrase_t* phrase, function_list_t* func_list) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, APPEL_VALEUR_FONCTION_ARGUMENT_S, &len, DEFAULT_SEPARATOR);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }
    
    phrase->phraseId = APPEL_VALEUR_FONCTION_ARGUMENT;
    phrase->function = getFunction(func_list, result[0]);

    return true;
}
