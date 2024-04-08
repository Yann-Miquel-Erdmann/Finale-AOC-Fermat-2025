#include "../instructions.h"
#include "../../structures/val.h"

bool test_inst_var_init(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }
    
    char** l = malloc(sizeof(char*));
    int len = 0;
    
    bool result = analyse(phrase, DEFINITION_VARIABLE_AVEC_INIT_S, l, &len);

    if (!result){
        return false;
    }
    if (len > 1){
        custom_error("too much arguments given", phrase);
    }
    
    phrase->phraseId = DEFINITION_VARIABLE_AVEC_INIT;
    phrase->constant = false;
    phrase->variable = getVariable(function->env, l[0]);
    if (phrase->variable == NULL){
        phrase->variable = new_variable(l[0]);
        addToVariableList(function->env, phrase->variable);
    }
    
    return true;
}
