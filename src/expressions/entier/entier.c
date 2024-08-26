#include "../expressions.h"

bool test_expr_entier(phrase_t* phrase, environnement_t* env) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int len = 0;
    // printf("%s\n", phrase->text);
    char** result = analyse(phrase, EXPR_ENTIER_S, &len, NUMBER_SEPARATOR);

    if (result == NULL) {
        return false;
    }
    if (len > 1) {
        custom_error("too many arguments given", phrase, env);
    }

    int result_num;
    if (eval_number(result[0], (int)strlen(result[0]), &result_num)) {
        phrase->phraseId = EXPR_ENTIER;
        phrase->constant = true;
        // printf("%p\n", env->phraseValeurs[ phrase->uniqueId]);
        set_int(env->phraseValeurs[phrase->uniqueId], result_num);
        
    } else {
        char* err = malloc((strlen(result[0]) + 32) * sizeof(char));

        strcpy(err, result[0]);
        strcat(err, " isn't recognized as an integer.");

        custom_error(err, phrase, env);
    }

    free_l(result, len);

    return true;
};
