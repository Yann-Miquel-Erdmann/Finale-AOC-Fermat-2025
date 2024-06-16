#include "../expressions.h"

int puiss10(int a) {
    float i = 1;
    while (a > 0) {
        a /= 10;
        i *= 10;
    }
    return i;
}

bool test_expr_flottant(phrase_t* phrase, environnement_t* env) {
    if ((int)strlen(phrase->text) < 13 || phrase->phraseId != -1) {
        return false;
    }

    int len = 0;
    char** result = analyse(phrase, EXPR_FLOTTANT_S, &len, NUMBER_SEPARATOR);
    if (result == NULL) {
        return false;
    }

    if (len > 1) {
        custom_error("too many arguments given", phrase, env);
    } else if (len < 1) {
        custom_error("not enough arguments", phrase, env);
    }

    char** res = split_word(result[0], "virgule");
    bool valid_entier;
    int partie_entiere = eval_number(res[0], (int)strlen(res[0]), &valid_entier);
    bool valid_flotant;
    float partie_decimale = eval_float(res[1], (int)strlen(res[1]), &valid_flotant);
    if (valid_entier && valid_flotant) {
        float num = (float)partie_entiere + partie_decimale;
        phrase->phraseId = EXPR_FLOTTANT;

        phrase->constant = true;
        set_float(getValeur(env, phrase->uniqueId), num);
    } else {
        custom_error("Flottant invalide", phrase, env);
    }

    free(res[0]);
    free(res[1]);
    free(res);

    free_l(result, len);

    return true;
}
