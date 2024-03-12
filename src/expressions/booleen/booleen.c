#include "expressions.h"

void free_pointer_b(char** ptr){
    free(ptr[0]);
    free(ptr[1]);
    free(ptr[2]);
    free(ptr);
}

void test_expr_booleen(phrase_t* phrase){
    char** result_str = cut_a_b(phrase->text, 12, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXPR_BOOLEEN_S)){
        if (!strcmp(result_str[1], "vrai")){
            printf("booléen: vrai\n");
            phrase->phraseId = EXPR_CHAINE;
            phrase->valeur = new_val();
            set_bool(phrase->valeur, true);
            
            free_pointer_b(result_str);
            
            return;
        }else if(!strcmp(result_str[1], "faux")){
            printf("booléen: faux\n");
            phrase->phraseId = EXPR_CHAINE;
            phrase->valeur = new_val();
            set_bool(phrase->valeur, false);
            
            free_pointer_b(result_str);

            
            return;
        }
    }
    free_pointer_b(result_str);
}
