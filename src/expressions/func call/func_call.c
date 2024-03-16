#include "../expressions.h"

bool test_expr_func_call(phrase_t* phrase, function_list_t* func_list) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 36, 1);
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], APPEL_VALEUR_FONCTION_S)) {
        // printf("appel de la fonction %s\n", result_str[1]);
        phrase->phraseId = APPEL_VALEUR_FONCTION;

        phrase->function = getFunction(func_list, result_str[1]);

    } else {
        free(result_str[1]);
    }

    free_pointers(result_str);

    // renvoie true si l'expression est une func call
    return phrase->phraseId != -1;
}
