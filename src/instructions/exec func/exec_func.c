#include "instructions.h"

void test_inst_exec_func(phrase_t* phrase){
    if (phrase->phraseId != -1){
        return;
    }
    
    char** result_str = cut_a_b(phrase->text, 20, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXECUTION_FONCTION_S)){
        printf("execution de la fonction %s\n", result_str[1]);
        phrase->phraseId = EXECUTION_FONCTION;
        phrase->function_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free_pointers(result_str);
}
