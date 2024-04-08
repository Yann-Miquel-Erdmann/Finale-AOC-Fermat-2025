#include "../instructions.h"
bool test_inst_create_var(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }
    
    char** l = malloc(sizeof(char*));
    int len = 0;
    
    bool result = analyse(phrase, DEFINITION_VARIABLE_SANS_INIT_S, l, &len, false);

    if (!result){
        return false;
    }
    if (len > 1){
        custom_error("too much arguments given", phrase);
    }
    
    phrase->phraseId = DEFINITION_VARIABLE_SANS_INIT;
    phrase->constant = true;
    phrase->variable = getVariable(function->env, l[0]);
    
    if (phrase->variable == NULL){
        phrase->variable = new_variable(l[0], new_val_t(UNDEFINED));
        set_undefined(phrase->variable->valeur);
        addToVariableList(function->env, phrase->variable);
    }else{
        set_undefined(phrase->variable->valeur);
    }
    
    return true;
}
