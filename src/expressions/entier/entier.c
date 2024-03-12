#include "expressions.h"

void free_pointers_e(char** ptr){
    free(ptr[0]);
    free(ptr[1]);
    free(ptr[2]);
    free(ptr);
}

void test_expr_entier(phrase_t* phrase){
    char** result_str = cut_a_b(phrase->text, 9, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXPR_ENTIER_S)){
        int* result_num = eval_number(result_str[1], (int)strlen(result_str[1]));
        
        if (result_num[0]){
            printf("integer: %d\n", result_num[1]);
            
            phrase->valeur = new_val();
            phrase->phraseId = EXPR_ENTIER;
            set_int(phrase->valeur, result_num[1]);
            
            free(result_num);
            free_pointers_e(result_str);
            
            return;
        }else{
            char* err = malloc((strlen(result_str[1])+0)*sizeof(char));
            
            strcpy(err, result_str[1]);
            strcat(err, " isn't recognized as an integer.");
            
            custom_error(err, phrase);
        }
        free(result_num);
    }
    free_pointers_e(result_str);
};
