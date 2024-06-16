#include "../expressions.h"

bool test_expr_booleen(phrase_t* phrase, environnement_t* env) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;

    char** result = analyse(phrase, EXPR_BOOLEEN_S, &len, DEFAULT_SEPARATOR);

    if (!result) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase, env);
    }

    if (!strcmp(result[0], "vrai")) {
        // printf("booléen: vrai\n");
        phrase->phraseId = EXPR_BOOLEEN;
        phrase->constant = true;
        set_bool(env->phraseValeurs[phrase->uniqueId], true);
    } else if (!strcmp(result[0], "faux")) {
        // printf("booléen: faux\n");
        phrase->phraseId = EXPR_BOOLEEN;
        phrase->constant = true;

        set_bool(env->phraseValeurs[phrase->uniqueId], false);
    } else {
        custom_error("Le booléen doit être vrai ou faux.", phrase, env);
    }
    free_l(result, len);

    return true;
}
