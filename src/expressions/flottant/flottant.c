#include "../expressions.h"
#include "../../safe_alloc.h"

int puiss10(int a) {
    float i = 1;
    while (a > 0) {
        a /= 10;
        i *= 10;
    }
    return i;
}

bool test_expr_flottant(phrase_t* phrase, environnement_t* env) {
    if ((int)strlen(phrase->text) < 13 || phrase->phraseId != NO_ID) {
        return false;
    }

    int len = 0;
    char** result = analyse(phrase, EXPR_FLOTTANT_S, &len, NUMBER_SEPARATOR);
    if (result == NULL) {
        return false;
    }

    if (len != 1) {
        custom_error("Expression flottante ne prend pas d'arguments", phrase, env);
    }
    
    float num;
    if (eval_float(result[0], (int)strlen(result[0]), &num)) {
        phrase->phraseId = EXPR_FLOTTANT;

        phrase->constant = true;
        set_float(env->phraseValeurs[phrase->uniqueId], num);
    } else {
        char* err = safe_alloc(NULL, (strlen(result[0]) + 32) * sizeof(char));

        strcpy(err, result[0]);
        strcat(err, " n'est pas un flottant valide");

        custom_error(err, phrase, env);
    }


    free_l(result, len);

    return true;
}
