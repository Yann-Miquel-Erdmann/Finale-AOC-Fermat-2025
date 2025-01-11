#include "../instructions.h"
bool test_inst_exec_func(phrase_t* phrase, function_list_t* function_list, environnement_t* env) {
    if (phrase->phraseId != NO_ID) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, EXECUTION_FONCTION_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("Un seul nom de fonction attendu", phrase, env);
    }

    phrase->phraseId = EXECUTION_FONCTION;
    phrase->function = new_function(result[0], phrase);

    free(result);
    return true;
}
