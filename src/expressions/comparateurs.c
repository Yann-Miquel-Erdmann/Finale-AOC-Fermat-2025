#include "comparateurs.h"

#include "../constants.h"

void egalite(phrase_t* phrase, bool constant) {
    set_bool(phrase->valeur, is_equal(phrase->args[0]->valeur, phrase->args[1]->valeur, phrase));
    phrase->constant = constant;
};

void inegalite(phrase_t* phrase, bool constant) {
    set_bool(phrase->valeur, !is_equal(phrase->args[0]->valeur, phrase->args[1]->valeur, phrase));
    phrase->constant = constant;
};

void plus_grand(phrase_t* phrase, bool constant) {
    set_bool(phrase->valeur, is_greater(phrase->args[0]->valeur, phrase->args[1]->valeur, phrase));
    phrase->constant = constant;
};

void strict_plus_grand(phrase_t* phrase, bool constant) {
    set_bool(phrase->valeur, is_strict_greater(phrase->args[0]->valeur, phrase->args[1]->valeur, phrase));
    phrase->constant = constant;
};

void plus_petit(phrase_t* phrase, bool constant) {
    set_bool(phrase->valeur, !is_strict_greater(phrase->args[0]->valeur, phrase->args[1]->valeur, phrase));
    phrase->constant = constant;
};

void strict_plus_petit(phrase_t* phrase, bool constant) {
    set_bool(phrase->valeur, !is_greater(phrase->args[0]->valeur, phrase->args[1]->valeur, phrase));
    phrase->constant = constant;
};
