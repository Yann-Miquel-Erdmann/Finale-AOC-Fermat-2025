#include "../instructions.h"

bool test_inst_affiche_message(phrase_t* phrase){
    if (phrase->phraseId != -1 || strlen(phrase->text) <= 20){
        return false;
    }
    
    char** result_str = cut_a_b(phrase->text, 19, 1);
    strcat(result_str[0], result_str[2]);
    if (!strcmp(result_str[0], AFFICHER_STR_S)){
        if (result_str[1][0] == '"' && result_str[1][(int)strlen(result_str[1])-1] == '"'){
            //printf("chaîne: %s\n", result_str[1]);
            phrase->phraseId = AFFICHER_STR;

            addToArg(phrase, new_phrase(phrase));
            phrase->args[0]->phraseId = EXPR_CHAINE;
            phrase->args[0]->textLen = (int)strlen(result_str[1]);

            strcpy(phrase->args[0]->text, result_str[1]);
            phrase->args[0]->textSize = phrase->args[0]->textLen*sizeof(char);
            phrase->args[0]->constant = true;

            phrase->textLen = (int)strlen(result_str[0]);
            strcpy(phrase->text, result_str[0]);
            phrase->textSize = phrase->textLen;
        }
        
    }
    free(result_str[1]);
    free_pointers(result_str);

    // 
    return phrase->phraseId != -1;
}
