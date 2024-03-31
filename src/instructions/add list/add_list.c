#include "../instructions.h"
bool test_inst_add_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1 || strlen(phrase->text) <= 23) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 20, 3);
    strcat(result_str[0], result_str[2]);
    
    
    if (!strcmp(result_str[0], AJOUT_LISTE_S)) {
        printf("ajout à la liste %s\n", result_str[1]);
        phrase->phraseId = AJOUT_LISTE;
        phrase->valeur->liste = getVariable(function->env, result_str[1])->valeur->liste;
    }
    free(result_str[1]);
    free_pointers(result_str);

    // renvoie true si l'expression est une add list
    return phrase->phraseId != -1;
}
