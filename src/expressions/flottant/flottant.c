#include "../expressions.h"

bool test_expr_flottant(phrase_t* phrase) {
    if ((int)strlen(phrase->text) < 13 || phrase->phraseId != -1) {
        return false;
    }
    char** result_str = cut_a_b(phrase->text, 12, 1);
    char** result_virgule = split_word(result_str[1], "virgule");
    if (!strcmp(result_str[0], "") || !strcmp(result_virgule[1], "")) {
        free(result_str[1]);
        free_pointers(result_str);
        free(result_virgule[0]);
        free(result_virgule[1]);
        free(result_virgule);
        return false;
    }
    strcat(result_str[0], " virgule *");
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], EXPR_FLOTTANT_S)) {
        int* result_num = eval_number(result_virgule[0], (int)strlen(result_virgule[0]));
        int* result_num_2 = eval_number(result_virgule[1], (int)strlen(result_virgule[1]));
        if (result_num[0] && result_num_2[0]) {
            float num = (float)result_num[1] + ((float)result_num_2[1]) / (puiss10(result_num_2[1]));
            // printf("float: %f\n", num);
            phrase->phraseId = EXPR_FLOTTANT;
            set_float(phrase->valeur, num);
        }else{
            printf("invalid flottant\n");
        }
        free(result_num);
        free(result_num_2);
    }
    free(result_str[1]);
    free_pointers(result_str);
    free(result_virgule[0]);
    free(result_virgule[1]);
    free(result_virgule);
    
    // renvoie true si l'expression est un flottant
    return phrase->phraseId != -1;
}
