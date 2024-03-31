#include "../expressions.h"

bool test_expr_taille_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1 || strlen(phrase->text) <= 23) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 22, 1);
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], TAILLE_LISTE_S)) {
        // printf("la taille de la liste %s\n", result_str[1]);
        phrase->phraseId = TAILLE_LISTE;
        set_liste(phrase->valeur, getVariable(function->env, result_str[1])->valeur->liste);
    }
    free(result_str[1]);
    free_pointers(result_str);

    // renvoie true si l'expression est une taille list
    return phrase->phraseId != -1;
}
