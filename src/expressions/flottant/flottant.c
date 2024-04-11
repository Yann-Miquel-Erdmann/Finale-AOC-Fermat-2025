#include "../expressions.h"

bool test_expr_flottant(phrase_t* phrase) {
    if ((int)strlen(phrase->text) < 13 || phrase->phraseId != -1) {
        return false;
    }

    int len = 0;
    char** result = analyse(phrase, EXPR_FLOTTANT_S, &len, NUMBER_SEPARATOR);
    if (result == NULL) {
        return false;
    }

    if (len > 1) {
        custom_error("too many arguments given", phrase);
    } else if (len < 1) {
        custom_error("not enough arguments", phrase);
    }

    char** res = split_word(result[0], "virgule");
    int* partie_entiere = eval_number(res[0], (int)strlen(res[0]));
    int* partie_decimale = eval_number(res[1], (int)strlen(res[1]));
    if (partie_entiere[0] && partie_decimale[0]) {
        float num = (float)partie_entiere[1] + ((float)partie_decimale[1]) / (puiss10(partie_decimale[1]));
        phrase->phraseId = EXPR_FLOTTANT;
        phrase->constant = true;
        set_float(phrase->valeur, num);
    } else {
        custom_error("invalid flottant", phrase);
    }

    free(res[0]);
    free(res[1]);
    free(res);

    free(partie_entiere);
    free(partie_decimale);
    free_l(result, len);

    return true;
}
