#include "instructions.h"

void test_inst_var_init(phrase_t* phrase){
    if (phrase->phraseId != -1){
        return;
    }
    
    char** result_str = cut_a_b(phrase->text, 5, 31);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], DEFINITION_VARIABLE_AVEC_INIT_S)){
        printf("variable init: %s\n", result_str[1]);
        phrase->phraseId = DEFINITION_VARIABLE_AVEC_INIT;
        phrase->variable_call = result_str[1];
    }else{
        free(result_str[1]);
    }

    free_pointers(result_str);
}
