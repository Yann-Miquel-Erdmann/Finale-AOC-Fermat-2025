#include "../instructions.h"
bool test_inst_exec_func_args(phrase_t* phrase, function_list_t* function_list) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, EXECUTION_FONCTION_ARGUMENT_S, &len, DEFAULT_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase);
    }
    
    phrase->phraseId = EXECUTION_FONCTION_ARGUMENT;
    phrase->function = new_function(result[0], phrase);

    free(result);
    return true;
}
