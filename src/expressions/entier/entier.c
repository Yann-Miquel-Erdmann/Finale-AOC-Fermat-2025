#include "../expressions.h"

bool test_expr_entier(phrase_t* phrase) {
    if (phrase->phraseId != -1) {
        return false;
    }
    
    char** l = malloc(sizeof(char*));
    int len = 0;
    
    bool result = analyse(phrase, EXPR_ENTIER_S, l, &len, true);

    if (!result){
        return false;
    }
    if (len > 1){
        custom_error("too much arguments given", phrase);
    }
    
    int* result_num = eval_number(l[0], (int)strlen(l[0]));

    if (result_num[0]) {

        phrase->phraseId = EXPR_ENTIER;
        phrase->constant = true;
        set_int(phrase->valeur, result_num[1]);
    } else {
        char* err = malloc((strlen(l[0]) + 32) * sizeof(char));

        strcpy(err, l[0]);
        strcat(err, " isn't recognized as an integer.");

        custom_error(err, phrase);
    }
    free(result_num);

    return true;
};
