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
    
    float num;
    if (eval_float(result[0], (int)strlen(result[0]), &num)) {
        phrase->phraseId = EXPR_FLOTTANT;

        phrase->constant = true;
        set_float(env->phraseValeurs[phrase->uniqueId], num);
    } else {
        custom_error("Flottant invalide", phrase, env);
    }


    free_l(result, len);

    return true;
}
