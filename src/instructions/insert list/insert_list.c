#include "../instructions.h"

bool test_inst_insert_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1 || strlen(phrase->text) <= 48) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 37, 15);
    strcat(result_str[0], result_str[2]);
    
    printf("'_%s'\n", result_str[0]);

    if (!strcmp(result_str[0], INSERTION_LISTE_S)) {
        printf("ajout à la liste %s\n", result_str[1]);
        phrase->phraseId = INSERTION_LISTE;
        phrase->liste = getListe(function->env, result_str[1]);
    }
    free(result_str[1]);
    free_pointers(result_str);

    // renvoie true si l'expression est une add list
    return phrase->phraseId != -1;
}
