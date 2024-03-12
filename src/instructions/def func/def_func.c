#include "instructions.h"

void test_inst_def_func(phrase_t* phrase){
    if (phrase->phraseId != -1){
        return;
    }
    
    char** result_str = cut_a_b(phrase->text, 5, 53);
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], DEFINITION_FONCTION_S)){
        printf("definition de la fonction %s\n", result_str[1]);
        phrase->phraseId = DEFINITION_FONCTION;
        phrase->function_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free_pointers(result_str);
}
