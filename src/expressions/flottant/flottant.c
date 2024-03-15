#include "../expressions.h"
void free_pointers_f(char** ptr, char** ptr1, char** ptr2) {
    free(ptr[0]);
    free(ptr[1]);
    free(ptr[2]);
    free(ptr);
    free(ptr1[0]);
    free(ptr1[1]);
    free(ptr1[2]);
    free(ptr1);
    free(ptr2[0]);
    free(ptr2[1]);
    free(ptr2);
}

bool test_expr_flottant(phrase_t* phrase) {
    if ((int)strlen(phrase->text) < 12 || phrase->phraseId != -1) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 12, (int)strlen(phrase->text) - 12);
    char** result_str_2 = cut_a_b(result_str[2], 0, 1);
    char** result_virgule = split_word(result_str_2[1], "virgule");

    strcat(result_str_2[0], result_str_2[2]);
    strcat(result_str[0], " virgule ");
    strcat(result_str[0], result_str_2[0]);

    if (!strcmp(result_str[0], EXPR_FLOTTANT_S)) {
        int* result_num = eval_number(result_virgule[0], (int)strlen(result_virgule[0]));
        int* result_num_2 = eval_number(result_virgule[1], (int)strlen(result_virgule[1]));
        if (result_num[0] && result_num_2[0]) {
            float num = (float)result_num[1] + ((float)result_num_2[1]) / (log_10_entier(result_num_2[1]));
            printf("float: %f\n", num);
            phrase->phraseId = EXPR_FLOTTANT;
            phrase->valeur = new_val();
            set_float(phrase->valeur, num);
        }
        free(result_num);
        free(result_num_2);
    }
    free_pointers_f(result_str, result_str_2, result_virgule);

    // renvoie true si l'expression est un flottant
    return phrase->phraseId != -1;
}
