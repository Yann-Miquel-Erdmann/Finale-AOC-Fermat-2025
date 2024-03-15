#include "../instructions.h"
bool test_inst_def_func(phrase_t* phrase, function_list_t* function_list) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 5, 53);
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], DEFINITION_FONCTION_S)){
        //printf("definition de la fonction %s\n", result_str[1]);
        phrase->phraseId = DEFINITION_FONCTION;
        addToFunctionList(function_list, new_function(result_str[1], phrase));

    } else {
        free(result_str[1]);
    }

    free_pointers(result_str);

    // renvoie true si l'expression est une def func
    return phrase->phraseId != -1;
}
