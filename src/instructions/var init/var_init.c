#include "../instructions.h"
bool test_inst_var_init(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 5, 31);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], DEFINITION_VARIABLE_AVEC_INIT_S)){
        //printf("variable init: %s\n", result_str[1]);
        phrase->phraseId = DEFINITION_VARIABLE_AVEC_INIT;
        variable_t* var = new_variable(result_str[1]);
        addToVariableList(function->env, var);
        phrase->variable = var;

    } else {
        free(result_str[1]);
    }

    free_pointers(result_str);

    // renvoie true si l'expression est une var init
    return phrase->phraseId != -1;
}
