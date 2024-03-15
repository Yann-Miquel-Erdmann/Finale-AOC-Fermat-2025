#include "../instruction.h" bool test_inst_modif_var(phrase_t* phrase, function_t* function) {
#include "function.h"
if (phrase->phraseId != -1) {
    return false;
}

char** result_str = cut_a_b(phrase->text, 16, 12);
strcat(result_str[0], result_str[2]);

if (!strcmp(result_str[0], MODIFICATION_VARIABLE_S)) {
    printf("modification de la variable %s\n", result_str[1]);
    phrase->phraseId = MODIFICATION_VARIABLE;
    phrase->variable = getVariable(function->env, result_str[1]);

} else {
    free(result_str[1]);
}

free_pointers(result_str);

// renvoie true si l'expression est une modif var
return phrase->phraseId != -1;
}
