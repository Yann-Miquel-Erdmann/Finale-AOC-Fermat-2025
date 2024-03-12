#include "instructions.h"

void test_inst_def_func_args(phrase_t* phrase){
    if (phrase->phraseId != -1){
        return;
    }
    
    char** result_str = cut_a_b(phrase->text, 5, 11);
    char** result_str_2 = split_word(result_str[1], "une fonction qui lorsqu'elle est appelée avec");
    if (!strcmp(result_str_2[0], "")){
        return;
    }
    strcat(result_str[0], " une fonction qui lorsqu'elle est appelée avec *");
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], DEFINITION_FONCTION_ARGUMENT_S)){
        printf("definition de la fonction %s avec arguments\n", result_str[1]);
        phrase->phraseId = DEFINITION_FONCTION_ARGUMENT;
        phrase->function_call = result_str_2[0];
        phrase->variable_call = result_str_2[1];
        
    }else{
        free(result_str[1]);
    }
    
    free_pointers(result_str);
    free(result_str_2);
}
