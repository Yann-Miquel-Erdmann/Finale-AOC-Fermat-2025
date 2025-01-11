#include "../instructions.h"
bool test_inst_exec_func_args(phrase_t* phrase, function_list_t* function_list, environnement_t* env) {
    if (phrase->phraseId != NO_ID) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, EXECUTION_FONCTION_ARGUMENT_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("Un seul nom de fonction attendu", phrase, env);
    }
    if (phrase->argsLen == 0){
        custom_error("Exécution de fonction prend au moins un argument", phrase, env);
    }
    if(phrase->innerPhraseLen > 0){
        custom_error("Exécution de fonction ne doit pas contenir d'instructions", phrase, env);
    }
    
    phrase->phraseId = EXECUTION_FONCTION_ARGUMENT;
    phrase->function = new_function(result[0], phrase);

    free(result);
    return true;
}
