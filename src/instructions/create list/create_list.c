#include "../instructions.h"
bool test_inst_create_list(phrase_t* phrase, function_t* function) {
    if (phrase->phraseId != -1) {
        return false;
    }
    
    char** l = malloc(sizeof(char*));
    int len = 0;
    
    bool result = analyse(phrase, CREATION_LISTE_S, l, &len);

    if (!result){
        return false;
    }
    if (len > 1){
        custom_error("too much arguments given", phrase);
    }

    phrase->phraseId = CREATION_LISTE;
    phrase->constant = true;
    liste_t* liste = new_liste_t(l[0]);
    addToListeList(function->env, liste);
    phrase->liste = liste;

    return true;
}
