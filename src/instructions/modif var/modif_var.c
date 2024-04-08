#include "../instructions.h"

bool test_inst_modif_var(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }
    
    char** l = malloc(sizeof(char*));
    int len = 0;
    
    bool result = analyse(phrase, MODIFICATION_VARIABLE_S, l, &len);
    if (!result){
        return false;
    }
    if (len > 1){
        custom_error("too much arguments given", phrase);
    }
    
    phrase->phraseId = MODIFICATION_VARIABLE;
    phrase->variable = getVariable(function->env, l[0]);

    return true;
}
