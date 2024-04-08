#include "../expressions.h"

bool test_expr_booleen(phrase_t* phrase) {
    if (phrase->phraseId != -1) {
        return false;
    }
    
    char** l = malloc(sizeof(char*));
    int len = 0;
    
    bool result = analyse(phrase, EXPR_BOOLEEN_S, l, &len, false);

    if (!result){
        return false;
    }
    if (len > 1){
        custom_error("too much arguments given", phrase);
    }
    
    if (!strcmp(l[0], "vrai")) {
        // printf("booléen: vrai\n");
        phrase->phraseId = EXPR_BOOLEEN;
        phrase->constant = true;
        set_bool(phrase->valeur, true);
    } else if (!strcmp(l[0], "faux")) {
        // printf("booléen: faux\n");
        phrase->phraseId = EXPR_BOOLEEN;
        phrase->constant = true;

        set_bool(phrase->valeur, false);
    } else {
        custom_error("Le booléen doit être vrai ou faux.", phrase);
    }

    return true;
}
