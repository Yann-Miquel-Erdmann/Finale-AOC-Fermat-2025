#include "instructions.h"

void test_inst_add_list(phrase_t* phrase){
    if (phrase->phraseId != -1){
        return;
    }
    
    char** result_str = cut_a_b(phrase->text, 20, 3);
    strcat(result_str[0], result_str[2]);
    if (!strcmp(result_str[0],AJOUT_LISTE_S)){
        printf("ajout à la liste %s\n", result_str[1]);
        phrase->phraseId = AJOUT_LISTE;
        phrase->liste_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free_pointers(result_str);
}
