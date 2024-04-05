#include "../instructions.h"
bool test_inst_create_var(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }

    int index = 0;
    int index_const = 0;
    int mode = 0;
    char* varible = malloc(sizeof(char));
    int var_len = 0;
    int var_size = 1;
    
    while (phrase->text[index] != '\0' && DEFINITION_VARIABLE_SANS_INIT_S[index_const] != '\0'){
        if (DEFINITION_VARIABLE_SANS_INIT_S[index_const] == '$'){
            mode = 1;
        }
        if (mode){
            if (phrase->text[index] == ' ' || phrase->text[index] == '.'){
                mode = 0;
                index_const++;
                continue;
            }
            if (var_size == var_len+1){
                var_size *= 2;
                varible = realloc(varible, var_size*sizeof(char));
            }
            varible[var_len] = phrase->text[index];
            index++;
            var_len++;
            continue;
        }
        if (phrase->text[index] != DEFINITION_VARIABLE_SANS_INIT_S[index_const]){
            break;
        }
        index ++;
        index_const++;
    }
    
    if (phrase->text[index] != '\0' || DEFINITION_VARIABLE_SANS_INIT_S[index_const] != '\0'){
        return false;
    }
    
    phrase->phraseId = DEFINITION_VARIABLE_SANS_INIT;
    phrase->constant = true;
    phrase->variable = getVariable(function->env, varible);
    
    return true;
}
