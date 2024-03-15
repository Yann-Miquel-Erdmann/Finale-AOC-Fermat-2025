#include "../expressions.h"
bool test_expr_chaine(phrase_t* phrase) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 26, 1);
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], EXPR_CHAINE_S)) {
        if (result_str[1][0] == '"' && result_str[1][(int)strlen(result_str[1]) - 1] == '"') {
            printf("chaine: %s\n", result_str[1]);
            phrase->phraseId = EXPR_CHAINE;
            phrase->textLen = (int)strlen(result_str[1]);
            strcpy(phrase->text, result_str[1]);
            phrase->textSize = phrase->textLen;
        } else {
            free(result_str[1]);
        }
    }
    free_pointers(result_str);

    // renvoie true si l'expression est une chaîne de caractères
    return phrase->phraseId != -1;
}
