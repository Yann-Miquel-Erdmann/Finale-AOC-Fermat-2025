#include "../expressions.h"

bool test_expr_booleen(phrase_t* phrase) {
    if (phrase->phraseId != -1) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 12, 1);
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], EXPR_BOOLEEN_S)) {
        if (!strcmp(result_str[1], "vrai")) {
            // printf("booléen: vrai\n");
            phrase->phraseId = EXPR_CHAINE;
            set_bool(phrase->valeur, true);
        } else if (!strcmp(result_str[1], "faux")) {
            // printf("booléen: faux\n");
            phrase->phraseId = EXPR_CHAINE;
            set_bool(phrase->valeur, false);
        } else {
            free(result_str[1]);
        }
    }
    free(result_str[1]);
    free_pointers(result_str);

    // renvoie true si l'expression est un booléen
    return phrase->phraseId != -1;
}
