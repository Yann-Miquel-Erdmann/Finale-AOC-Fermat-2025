#include "../instructions.h"
bool test_inst_def_func(phrase_t* phrase, function_list_t* function_list, environnement_t* env) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, DEFINITION_FONCTION_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("Un seul nom de fonction attendu", phrase, env);
    }

    phrase->phraseId = DEFINITION_FONCTION;
    // phrase->constant = true;

    function_t* new_func = new_function(result[0], phrase);
    new_func->function_arg_count = 0;
    phrase->function = new_func;
    addToFunctionList(function_list, new_func);

    free(result);
    return true;
}
