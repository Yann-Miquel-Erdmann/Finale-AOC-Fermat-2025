#include "../expressions.h"

bool test_expr_func_call_args(phrase_t* phrase, function_list_t* func_list, environnement_t* env) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, APPEL_VALEUR_FONCTION_ARGUMENT_S, &len, DEFAULT_SEPARATOR);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("Un seul nom de fonction attendu", phrase, env);
    }
    if (phrase->argsLen == 0){
        custom_error("Appel de fonction prend au moins un argument", phrase, env);
    }
    if (phrase->innerPhraseLen > 0){
        custom_error("Appel de fonction ne doit pas contenir d'instructions", phrase, env);
    }
    
    phrase->phraseId = APPEL_VALEUR_FONCTION_ARGUMENT;

    phrase->function = new_function(result[0], phrase);

    free(result);
    return true;
}
