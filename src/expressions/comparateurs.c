#include "comparateurs.h"

#include "../constants.h"

void egalite(phrase_t* phrase, bool constant) {
    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[1]->valeur->type == FLOAT) {
        set_bool(phrase->valeur, get_as_float(phrase->args[0]->valeur, phrase) == get_as_float(phrase->args[1]->valeur, phrase));
    } else {
        set_bool(phrase->valeur, get_as_int(phrase->args[0]->valeur, phrase) == get_as_int(phrase->args[1]->valeur, phrase));
    }
    phrase->constant = constant;
};

void plus_grand(phrase_t* phrase, bool constant) {
    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[1]->valeur->type == FLOAT) {
        set_bool(phrase->valeur, get_as_float(phrase->args[0]->valeur, phrase) >= get_as_float(phrase->args[1]->valeur, phrase));
    } else {
        set_bool(phrase->valeur, get_as_int(phrase->args[0]->valeur, phrase) >= get_as_int(phrase->args[1]->valeur, phrase));
    }
    phrase->constant = constant;
};

void strict_plus_grand(phrase_t* phrase, bool constant) {
    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[1]->valeur->type == FLOAT) {
        set_bool(phrase->valeur, get_as_float(phrase->args[0]->valeur, phrase) > get_as_float(phrase->args[1]->valeur, phrase));
    } else {
        set_bool(phrase->valeur, get_as_int(phrase->args[0]->valeur, phrase) > get_as_int(phrase->args[1]->valeur, phrase));
    }
    phrase->constant = constant;
};

void plus_petit(phrase_t* phrase, bool constant) {
    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[1]->valeur->type == FLOAT) {
        set_bool(phrase->valeur, get_as_float(phrase->args[0]->valeur, phrase) <= get_as_float(phrase->args[1]->valeur, phrase));
    } else {
        set_bool(phrase->valeur, get_as_int(phrase->args[0]->valeur, phrase) <= get_as_int(phrase->args[1]->valeur, phrase));
    }
    phrase->constant = constant;
};

void strict_plus_petit(phrase_t* phrase, bool constant) {
    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[1]->valeur->type == FLOAT) {
        set_bool(phrase->valeur, get_as_float(phrase->args[0]->valeur, phrase) < get_as_float(phrase->args[1]->valeur, phrase));
    } else {
        set_bool(phrase->valeur, get_as_int(phrase->args[0]->valeur, phrase) < get_as_int(phrase->args[1]->valeur, phrase));
    }
    phrase->constant = constant;
};
