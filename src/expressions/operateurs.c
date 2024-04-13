#include "operateurs.h"

#include "../constants.h"
#include "../custom_error.h"

void somme(phrase_t* phrase, bool constant) {
    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[0]->valeur->type == FLOAT) {
        set_float(phrase->valeur, get_as_float(phrase->args[0]->valeur) + get_as_float(phrase->args[1]->valeur));
    } else {
        set_int(phrase->valeur, get_as_int(phrase->args[0]->valeur) + get_as_int(phrase->args[1]->valeur));
    }
    phrase->constant = constant;
};

void difference(phrase_t* phrase, bool constant) {
    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[0]->valeur->type == FLOAT) {
        set_float(phrase->valeur, get_as_float(phrase->args[0]->valeur) - get_as_float(phrase->args[1]->valeur));
    } else {
        set_int(phrase->valeur, get_as_int(phrase->args[0]->valeur) - get_as_int(phrase->args[1]->valeur));
    }
    phrase->constant = constant;
};

void produit(phrase_t* phrase, bool constant) {
    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[0]->valeur->type == FLOAT) {
        set_float(phrase->valeur, get_as_float(phrase->args[0]->valeur) * get_as_float(phrase->args[1]->valeur));
    } else {
        set_int(phrase->valeur, get_as_int(phrase->args[0]->valeur) * get_as_int(phrase->args[1]->valeur));
    }
    phrase->constant = constant;
};

void quotient(phrase_t* phrase, bool constant) {
    if (get_as_float(phrase->args[1]->valeur) == 0) {
        custom_error("Division par 0", phrase);
    }
    set_float(phrase->valeur, get_as_float(phrase->args[0]->valeur) / get_as_float(phrase->args[1]->valeur));
    if ((float)get_as_int(phrase->valeur) == get_as_float(phrase->valeur)) {
        set_int(phrase->valeur, get_as_int(phrase->valeur));
    }
    phrase->constant = constant;
};

void quotient_entier(phrase_t* phrase, bool constant) {
    if (get_as_float(phrase->args[1]->valeur) == 0) {
        custom_error("Division par 0", phrase);
    }

    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[0]->valeur->type == FLOAT) {
        set_float(phrase->valeur, (int)(get_as_float(phrase->args[0]->valeur) / get_as_float(phrase->args[1]->valeur)));
    } else {
        set_int(phrase->valeur, (int)(get_as_int(phrase->args[0]->valeur) / get_as_int(phrase->args[1]->valeur)));
    }
    phrase->constant = constant;
};

void reste(phrase_t* phrase, bool constant) {
    if (get_as_float(phrase->args[1]->valeur) == 0) {
        custom_error("Division par 0", phrase);
    }
    if (phrase->args[0]->valeur->type == FLOAT || phrase->args[1]->valeur->type == FLOAT) {
        set_float(phrase->valeur, (get_as_float(phrase->args[0]->valeur) / get_as_float(phrase->args[1]->valeur)) - (get_as_int(phrase->args[0]->valeur) / get_as_int(phrase->args[1]->valeur)));
    } else {
        set_int(phrase->valeur, get_as_int(phrase->args[0]->valeur) % get_as_int(phrase->args[1]->valeur));
    }
    phrase->constant = constant;
};

void negation_booleenne(phrase_t* phrase, bool constant) {
    set_bool(phrase->valeur, !get_as_bool(phrase->args[0]->valeur));
    phrase->constant = constant;
};
