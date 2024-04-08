#include "../expressions.h"

bool test_expr_access_var(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }
    
    char** l = malloc(sizeof(char*));
    int len = 0;
    
    bool result = analyse(phrase, ACCESSION_VARIABLE_S, l, &len, false);

    if (!result){
        return false;
    }
    if (len > 1){
        custom_error("too much arguments given", phrase);
    }
    
    phrase->phraseId = ACCESSION_VARIABLE;
    phrase->constant = false;
    phrase->variable = getVariable(function->env, l[0]);
    
    return true;
}
