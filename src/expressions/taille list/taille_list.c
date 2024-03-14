#include "../expressions.h"

void test_expr_taille_list(phrase_t* phrase){
    if (phrase->phraseId != -1){
        return;
    }
    
    char** result_str = cut_a_b(phrase->text, 22, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0],TAILLE_LISTE_S)){
        //printf("la taille de la liste %s\n", result_str[1]);
        phrase->phraseId = TAILLE_LISTE;
        phrase->liste_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free_pointers(result_str);
}
