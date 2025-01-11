#include "pointeur.h"

#include "custom_error.h"

// renvoie vrai si il y a une boucle de pointeurs (ferme = true)
bool parcours_profondeur(val_t* v, phrase_t* p, environnement_t* env) {
    if (v->ferme) {  // il y a une boucle de pointeurs
        return false;
    }

    if (v->ouvert) {  // il déjà été visité
        return true;
    }

    v->ouvert = true;

    switch (v->type) {
        case INT:
        case FLOAT:
        case BOOL:
        case CHAINE_DE_CHAR:

        case UNDEFINED:
            v->ferme = true;
            return false;
            break;

        case LISTE:

            for (int i = 0; i < v->value.liste->valeursLen; i++) {
                if (parcours_profondeur(v->value.liste->valeurs[i], p, env)) {
                    v->ferme = true;
                    return true;
                }
            }
            v->ferme = true;
            return false;
            break;

        case POINTEUR:
        {
            bool res = parcours_profondeur(v->value.ptr, p, env);
            v->ferme = true;
            return res;
            break;
        }
    }

    custom_error("le type de val_t n'est pas reconnu dans parcours_profondeur", p, env);
    return false;
}

void reset_pointeur_graph(val_t* v) {
    if (!v->ouvert && !v->ferme) {
        return;
    }
    v->ouvert = false;
    v->ferme = false;
    switch (v->type) {
        case LISTE:

            for (int i = 0; i < v->value.liste->valeursLen; i++) {
                reset_pointeur_graph(v->value.liste->valeurs[i]);
            }
            break;
        case POINTEUR:
            reset_pointeur_graph(v->value.ptr);
            break;
        default:
            break;
    }
}

// renvoie vrai si il y a une boucle de pointeurs en partant de ptr
bool boucle_pointeur(val_t* ptr, phrase_t* p, environnement_t* env) {
    bool res = parcours_profondeur(ptr, p, env);
    reset_pointeur_graph(ptr);
    return res;
}