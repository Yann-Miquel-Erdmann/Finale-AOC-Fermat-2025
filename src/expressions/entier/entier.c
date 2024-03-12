#include "expressions.h"

void test_expr_entier(phrase_t* phrase){
    if (phrase->phraseId != -1){
        return;
    }
    
    
    char** result_str = cut_a_b(phrase->text, 9, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXPR_ENTIER_S)){
        int* result_num = eval_number(result_str[1], (int)strlen(result_str[1]));
        
        if (result_num[0]){
            printf("integer: %d\n", result_num[1]);
            
            phrase->valeur = new_val();
            phrase->phraseId = EXPR_ENTIER;
            set_int(phrase->valeur, result_num[1]);
        }else{
            char* err = malloc((strlen(result_str[1])+32)*sizeof(char));
            
            strcpy(err, result_str[1]);
            strcat(err, " isn't recognized as an integer.");
            
            free(result_num);
            free_pointers(result_str);
            
            custom_error(err, phrase);
        }
        free(result_num);
    }
    free_pointers(result_str);
};
