#include "../expressions.h"

bool test_expr_chaine(phrase_t* phrase) {
    if (phrase->phraseId != -1 || strlen(phrase->text) <= 25) {
        return false;
    }
    char** l = malloc(sizeof(char*));
    int len = 0;

    bool result = analyse(phrase, EXPR_CHAINE_S, l, &len, true);

    if (!result) {
        free_l(l, len);
        return false;
    }
    if (len > 1) {
        custom_error("too much arguments given", phrase);
    } else if (len < 1) {
        custom_error("not enough arguments given", phrase);
    }

    phrase->phraseId = EXPR_CHAINE;
    phrase->constant = true;
    phrase->expr = true; 
    chaine_t* c = new_chaine_t(l[0]);
    set_char(phrase->valeur, c);

    free(l);

    return true;
};