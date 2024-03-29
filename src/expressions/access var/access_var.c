#include "../expressions.h"

bool test_expr_access_var(phrase_t* phrase, function_t* func) {
    if (phrase->phraseId != -1 || strlen(phrase->text) <= 13) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 12, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], ACCESSION_VARIABLE_S)) {
        phrase->phraseId = ACCESSION_VARIABLE;
        phrase->variable = getVariable(func->env, result_str[1]);
    }

    free(result_str[0]);
    free(result_str[1]);
    free(result_str[2]);
    free(result_str);
    // renvoie true si l'expression est une access var
    return phrase->phraseId != -1;
}
