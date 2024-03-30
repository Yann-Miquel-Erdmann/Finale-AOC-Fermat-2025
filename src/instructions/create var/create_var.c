#include "../instructions.h"
bool test_inst_create_var(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1 || strlen(phrase->text) <= 19) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 5, 14);
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], DEFINITION_VARIABLE_SANS_INIT_S)) {
        // printf("variable sans init: %s\n", result_str[1]);
        phrase->phraseId = DEFINITION_VARIABLE_SANS_INIT;
        phrase->constant = true;
        phrase->variable = getVariable(function->env, result_str[1]);
    }
    free(result_str[1]);
    free_pointers(result_str);

    // renvoie true si l'expression est une create var
    return phrase->phraseId != -1;
}
