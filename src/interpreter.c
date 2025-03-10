#include "interpreter.h"

#include <math.h>
#include <string.h>

#include "constants.h"
#include "custom_error.h"
#include "eval_numbers.h"
#include "expressions/comparateurs.h"
#include "expressions/operateurs/operateurs.h"
#include "pointeur.h"
#include "safe_alloc.h"
#include "syntax_convert.h"

void interpreter(function_t* function, function_list_t* functions, val_t* result, int layer) {
    if (layer > MAX_RECUSION_DEPTH) {
        custom_error("Limite de récursion atteinte", NULL, NULL);
    }
    if (function->ast->innerPhraseLen == 0) {
        return;
    }
    environnement_t* env = function->env;

    // printf("new func");

    // phrase_t* ptemp = new_phrase(NULL);
    // ptemp->suivant = function->ast;
    phrase_t* phraseActuelle = function->ast;
    // free_phrase(ptemp);

    while (phraseActuelle != NULL) {
        // printf("'%s' %d %d %d %p\n", phraseActuelle->text, phraseActuelle->phraseId, phraseActuelle->argsLen, (int)phraseActuelle->constant, phraseActuelle);

        // if (phraseActuelle->suivant != NULL) {
        //     printf("%s  --->   %s\n", phraseActuelle->text, phraseActuelle->suivant->text);
        // } else {
        //     printf("%s  --->   NULL\n", phraseActuelle->text);
        // }
        // if (phraseActuelle->suivantInner1 != NULL) {
        //     printf("suivantInner1 %s  --->   %s\n", phraseActuelle->text, phraseActuelle->suivantInner1->text);
        // }
        // if (phraseActuelle->suivantInner2 != NULL) {
        //     printf("suivantInner2 %s  --->   %s\n", phraseActuelle->text, phraseActuelle->suivantInner2->text);
        // }
        // printf("\n");

        // printf("'%s' %d %d\n", phraseActuelle->text, phraseActuelle->phraseId, (int)phraseActuelle->constant);
        switch (phraseActuelle->phraseId) {
            case DEFINITION_FONCTION_ARGUMENT:
            case DEFINITION_FONCTION:
                phraseActuelle = phraseActuelle->suivant;
                break;

            case MAIN_PHRASE:
                // printf("main\n");
                phraseActuelle = phraseActuelle->suivantInner1;
                // printf("%s\n", phraseActuelle->text);
                break;

            case APPEL_VALEUR_FONCTION:
            case EXECUTION_FONCTION:
            case APPEL_VALEUR_FONCTION_ARGUMENT:
            case EXECUTION_FONCTION_ARGUMENT: {
                function_t* new_func = safe_alloc(NULL, sizeof(function_t));
                // printf("'%s' exec function\n", phraseActuelle->function->nom);
                new_func->nom = phraseActuelle->function->nom;
                new_func->ast = phraseActuelle->function->ast;
                new_func->function_arg_count = phraseActuelle->function->function_arg_count;
                new_func->env = copy_environnement(phraseActuelle->function->env);
                new_func->ast->phraseId = MAIN_PHRASE;

                if (phraseActuelle->phraseId == APPEL_VALEUR_FONCTION_ARGUMENT || phraseActuelle->phraseId == EXECUTION_FONCTION_ARGUMENT) {
                    if (phraseActuelle->argsLen != new_func->function_arg_count) {
                        custom_error("Le nombre d'arguments données ne correspond pas au nombre d'arguments attendus", phraseActuelle, env);
                    }
                    for (int i = 0; i < phraseActuelle->argsLen; i++) {
                        copy_val(new_func->env->variable_list[i]->valeur,
                                 env->phraseValeurs[phraseActuelle->args[i]->uniqueId], true, true);
                    }
                }

                if (phraseActuelle->phraseId == EXECUTION_FONCTION_ARGUMENT || phraseActuelle->phraseId == EXECUTION_FONCTION) {
                    if (phraseActuelle->argsLen != new_func->function_arg_count) {
                        custom_error("Le nombre d'arguments données ne correspond pas au nombre d'arguments attendus", phraseActuelle, env);
                    }
                    interpreter(new_func, functions, NULL, layer + 1);
                } else {
                    if (phraseActuelle->argsLen != new_func->function_arg_count) {
                        custom_error("Le nombre d'arguments données ne correspond pas au nombre d'arguments attendus", phraseActuelle, env);
                    }
                    interpreter(new_func, functions, env->phraseValeurs[phraseActuelle->uniqueId], layer + 1);
                }

                free_environnement(new_func->env);
                free(new_func);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case RENVOI_FONCTION:
                if (result != NULL) {
                    copy_val(result, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
                }
                return;
                break;

            case AFFICHER_EXPR:
            case AFFICHER_EXPR_NO_RETURN:
                for (int i = 0; i < phraseActuelle->argsLen - 1; i++) {
                    print_val(env->phraseValeurs[phraseActuelle->args[i]->uniqueId], false, phraseActuelle, env);
                    printf(" ");
                }
                print_val(env->phraseValeurs[phraseActuelle->args[phraseActuelle->argsLen - 1]->uniqueId], phraseActuelle->phraseId == AFFICHER_EXPR, phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case TAILLE:
                taille(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            // variable ------------------------------------------------------
            case DEFINITION_VARIABLE_AVEC_INIT:

                copy_val(env->variable_list[phraseActuelle->variableId]->valeur, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);

                if (env->variable_list[phraseActuelle->variableId]->valeur->references > 1) {  // s'assure qu'il n'y ait pas de boucle de pointeurs
                    if (boucle_pointeur(env->variable_list[phraseActuelle->variableId]->valeur, phraseActuelle, env)) {
                        custom_error("Il y a une boucle de pointeurs.", phraseActuelle, env);
                    }
                }

                phraseActuelle = phraseActuelle->suivant;
                break;

            case MODIFICATION_VARIABLE:
                // printf("MODIFICATION_VARIABLE %p\n", env->variable_list[phraseActuelle->args[0]->variableId]->valeur);
                copy_val(env->phraseValeurs[phraseActuelle->args[0]->uniqueId],
                         env->phraseValeurs[phraseActuelle->args[1]->uniqueId], true, true);

                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->references > 1) {  // s'assure qu'il n'y ait pas de boucle de pointeurs
                    if (boucle_pointeur(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env)) {
                        custom_error("Il y a une boucle de pointeurs.", phraseActuelle, env);
                    }
                }

                phraseActuelle = phraseActuelle->suivant;
                break;

            case ACCESSION_VARIABLE:

                free_val_t(env->phraseValeurs[phraseActuelle->uniqueId], true, true);
                env->phraseValeurs[phraseActuelle->uniqueId] = env->variable_list[phraseActuelle->variableId]->valeur;
                env->phraseValeurs[phraseActuelle->uniqueId]->references++;

                phraseActuelle = phraseActuelle->suivant;
                break;

                // opérateur ---------------------------------------------------
            case SOMME:
                somme(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case DIFFERENCE:
                difference(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case PRODUIT:
                produit(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case QUOTIENT:
                quotient(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case QUOTIENT_ENTIER:
                quotient_entier(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case RESTE:
                reste(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case NEGATION_BOOLEENNE:
                negation_booleenne(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

                // comparateur ----------------------------------------------------------
            case EGALITE:
                // printf("égalité %s %s\n", phraseActuelle->args[0]->text, phraseActuelle->args[1]->text);
                egalite(phraseActuelle, env);
                phraseActuelle = phraseActuelle->suivant;
                break;

            case INEGALITE:
                inegalite(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case PLUS_GRAND:
                plus_grand(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case STRICT_PLUS_GRAND:
                strict_plus_grand(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case PLUS_PETIT:
                plus_petit(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case STRICT_PLUS_PETIT:
                strict_plus_petit(phraseActuelle, env);
                phraseActuelle = phraseActuelle->suivant;
                break;

            // list -----------------------------------------------------------------
            case EXPR_LISTE: {
                val_t* variable = env->variable_list[phraseActuelle->variableId]->valeur;

                if (variable->type != LISTE) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }

                free_val_t(env->phraseValeurs[phraseActuelle->uniqueId], true, true);
                env->phraseValeurs[phraseActuelle->uniqueId] = variable;
                variable->references++;

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case EXPR_LISTE_VIDE:
                vider_liste(env->phraseValeurs[phraseActuelle->uniqueId]->value.liste);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case EXPR_LISTE_ELEM:
                if (env->phraseValeurs[phraseActuelle->uniqueId]->type == LISTE) {
                    vider_liste(env->phraseValeurs[phraseActuelle->uniqueId]->value.liste);
                } else {
                    env->phraseValeurs[phraseActuelle->uniqueId]->type = LISTE;
                    env->phraseValeurs[phraseActuelle->uniqueId]->value.liste = new_liste_t();
                }

                for (int i = 0; i < phraseActuelle->argsLen; i++) {
                    ajout(env->phraseValeurs[phraseActuelle->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[i]->uniqueId], phraseActuelle, env);
                }

                phraseActuelle = phraseActuelle->suivant;
                break;

            case ACCESSION_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }

                // ne fait pas de deep copy pour les listes et les chaînes de caractères (pour pouvoir les modifier à l’intérieur d'une liste)
                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != INT) {
                    custom_error("Le type de l'argument ne correspond pas, un entier est attendu", phraseActuelle, env);
                }

                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier < 0 || env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier >= env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeursLen) {
                    custom_error("Indice hors de la liste", phraseActuelle, env);
                }

                free_val_t(env->phraseValeurs[phraseActuelle->uniqueId], true, true);
                env->phraseValeurs[phraseActuelle->uniqueId] = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier];
                env->phraseValeurs[phraseActuelle->uniqueId]->references++;

                phraseActuelle = phraseActuelle->suivant;
                break;

            case MODIFICATION_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE)) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != INT) {
                    custom_error("Le type de l'argument ne correspond pas, un entier est attendu", phraseActuelle, env);
                }
                modification(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier, env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env);

                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier]->references) {  // s'assure qu'il n'y ait pas de boucle de pointeurs
                    if (boucle_pointeur(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs [env->phraseValeurs [phraseActuelle->args [1]->uniqueId]->value.entier], phraseActuelle, env)) {
                        custom_error("Il y a une boucle de pointeurs.", phraseActuelle, env);
                    }
                }

                phraseActuelle = phraseActuelle->suivant;
                break;

            case AJOUT_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE)) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                ajout(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env);

                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeursLen-1]->references) {  // s'assure qu'il n'y ait pas de boucle de pointeurs
                    if (boucle_pointeur(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeursLen-1], phraseActuelle, env)) {
                        custom_error("Il y a une boucle de pointeurs.", phraseActuelle, env);
                    }
                }

                phraseActuelle = phraseActuelle->suivant;
                break;

            case SUPPRESSION_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE)) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != INT) {
                    custom_error("Le type de l'argument ne correspond pas, un entier est attendu", phraseActuelle, env);
                }
                suppression(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier, phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case INSERTION_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId] == NULL || (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != LISTE)) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                if (env->phraseValeurs[phraseActuelle->args[2]->uniqueId]->type != INT) {
                    custom_error("Le type de l'argument ne correspond pas, un entier est attendu", phraseActuelle, env);
                }
                inserer(env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[2]->uniqueId]->value.entier, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env);

                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[2]->uniqueId]->value.entier]->references) {  // s'assure qu'il n'y ait pas de boucle de pointeurs
                    if (boucle_pointeur(env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[2]->uniqueId]->value.entier], phraseActuelle, env)) {
                        custom_error("Il y a une boucle de pointeurs.", phraseActuelle, env);
                    }
                }

                phraseActuelle = phraseActuelle->suivant;
                break;

            case SI_ALORS:
                if (get_as_bool(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env)) {
                    phraseActuelle = phraseActuelle->suivantInner1;
                } else {
                    phraseActuelle = phraseActuelle->suivant;
                }
                break;

            case SI_ALORS_SINON:
                if (get_as_bool(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env)) {
                    phraseActuelle = phraseActuelle->suivantInner1;
                } else {
                    phraseActuelle = phraseActuelle->suivantInner2;
                }

                break;

            case TANT_QUE:
                if (get_as_bool(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env)) {
                    phraseActuelle = phraseActuelle->suivantInner1;
                } else {
                    phraseActuelle = phraseActuelle->suivant;
                }
                break;

            case POUR_AVEC_PAS:
                if (env->phraseValeurs[phraseActuelle->uniqueId]->value.booleen == false) {  //  initialisation de l’itérateur
                    copy_val(env->variable_list[phraseActuelle->variableId]->valeur, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
                    env->phraseValeurs[phraseActuelle->uniqueId]->value.booleen = true;
                } else {  // incrémentation de l'itérateur
                    if (phraseActuelle->phraseId == POUR_AVEC_PAS) {
                        if (env->variable_list[phraseActuelle->variableId]->valeur->type == FLOAT || env->phraseValeurs[phraseActuelle->args[2]->uniqueId]->type == FLOAT) {
                            set_float(env->variable_list[phraseActuelle->variableId]->valeur, get_as_float(env->variable_list[phraseActuelle->variableId]->valeur, phraseActuelle, env) + get_as_float(env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env));
                        } else {
                            set_int(env->variable_list[phraseActuelle->variableId]->valeur, get_as_int(env->variable_list[phraseActuelle->variableId]->valeur, phraseActuelle, env) + get_as_int(env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env));
                        }
                    }
                }
                if (
                    (get_as_float(env->variable_list[phraseActuelle->variableId]->valeur, phraseActuelle, env) < get_as_float(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env) && get_as_int(env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env) > 0) ||
                    (get_as_float(env->variable_list[phraseActuelle->variableId]->valeur, phraseActuelle, env) > get_as_float(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env) && get_as_int(env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env) < 0)) {
                    phraseActuelle = phraseActuelle->suivantInner1;
                } else {
                    env->phraseValeurs[phraseActuelle->uniqueId]->value.booleen = false;
                    phraseActuelle = phraseActuelle->suivant;
                }

                break;

            case POUR_SANS_PAS:
                if (env->phraseValeurs[phraseActuelle->uniqueId]->value.booleen == false) {  //  initialisation de l’itérateur
                    copy_val(env->variable_list[phraseActuelle->variableId]->valeur, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
                    env->phraseValeurs[phraseActuelle->uniqueId]->value.booleen = true;
                } else {  // incrémentation de l'itérateur

                    if (env->variable_list[phraseActuelle->variableId]->valeur->type == FLOAT) {
                        set_float(env->variable_list[phraseActuelle->variableId]->valeur, get_as_float(env->variable_list[phraseActuelle->variableId]->valeur, phraseActuelle, env) + 1);
                    } else {
                        set_int(env->variable_list[phraseActuelle->variableId]->valeur, get_as_int(env->variable_list[phraseActuelle->variableId]->valeur, phraseActuelle, env) + 1);
                    }
                }
                if (get_as_float(env->variable_list[phraseActuelle->variableId]->valeur, phraseActuelle, env) < get_as_float(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env)) {
                    phraseActuelle = phraseActuelle->suivantInner1;
                } else {
                    env->phraseValeurs[phraseActuelle->uniqueId]->value.booleen = false;
                    phraseActuelle = phraseActuelle->suivant;
                }
                break;

            case QUITTER_BOUCLE:
                // réinitialise l'itérateur de la boucle pour
                if (phraseActuelle->suivant->phraseId == POUR_AVEC_PAS || phraseActuelle->suivant->phraseId == POUR_SANS_PAS) {
                    env->phraseValeurs[phraseActuelle->suivant->uniqueId]->value.booleen = false;
                }

                phraseActuelle = phraseActuelle->suivant->suivant;
                break;

            case TYPE_EXPR:
            {
                char* s = str_type(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]);
                val_t* tmp = new_chaine_val_t(s, true);
                copy_val(env->phraseValeurs[phraseActuelle->uniqueId], tmp, false, true);
                free_val_t(tmp, true, true);
                free(tmp);
                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case ET:
                et_booleen(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case OU:
                ou_booleen(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case EXPR_RIEN:
                set_undefined(env->phraseValeurs[phraseActuelle->uniqueId]);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case DEFINIR_SEED:
                srand(get_as_int(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env));
                phraseActuelle = phraseActuelle->suivant;
                break;

            case NOMBRE_ALEATOIRE:
                set_float(env->phraseValeurs[phraseActuelle->uniqueId], ((float)rand() / (float)2147483647));
                phraseActuelle = phraseActuelle->suivant;
                break;

            case PARTIE_ENTIERE:
                set_int(env->phraseValeurs[phraseActuelle->uniqueId], get_as_int(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env));
                phraseActuelle = phraseActuelle->suivant;
                break;
            case INPUT_INT: {
                val_t* val = new_val_t(UNDEFINED);
                get_input(val);

                int value_i;
                int lenght = val->value.chaine->chars_len;
                if (eval_number(val->value.chaine->chars, lenght, &value_i)) {
                    set_int(env->phraseValeurs[phraseActuelle->uniqueId], value_i);
                    phraseActuelle = phraseActuelle->suivant;
                } else {
                    printf("La chaîne donnée ne correspond pas à un entier.\nVeuillez enter un entier.\n");
                    fflush(stdout);
                }
                free_val_t(val, true, true);
                break;
            }
            case INPUT_FLOAT: {
                val_t* val = new_val_t(UNDEFINED);
                get_input(val);

                float value_f;
                int lenght = val->value.chaine->chars_len;
                if (eval_float(val->value.chaine->chars, lenght, &value_f)) {
                    set_float(env->phraseValeurs[phraseActuelle->uniqueId], value_f);
                    phraseActuelle = phraseActuelle->suivant;
                } else {
                    printf("La chaîne donnée ne correspond pas à un flottant.\nVeuillez entrer un flottant.\n");
                    fflush(stdout);
                }
                free_val_t(val, true, true);
                break;
            }
            case INPUT_BOOL: {
                val_t* val = new_val_t(UNDEFINED);
                get_input(val);

                int lenght = val->value.chaine->chars_len;
                char* str = val->value.chaine->chars;
                if (!strcmp(str, "faux") || !strcmp(str, "vrai")) {
                    set_bool(env->phraseValeurs[phraseActuelle->uniqueId], (lenght != 0 && strcmp(val->value.chaine->chars, "faux")));
                    phraseActuelle = phraseActuelle->suivant;
                } else {
                    printf("La chaîne donnée ne correspond pas à un booléen.\nVeuillez enter un booléen.\n");
                    fflush(stdout);
                }
                free_val_t(val, true, true);
                break;
            }
            case INPUT: {
                val_t* val = new_val_t(UNDEFINED);
                get_input(val);

                int lenght = val->value.chaine->chars_len;
                char* str = val->value.chaine->chars;

                if (str[0] != '"' || str[lenght - 1] != '"') {
                    printf("La chaîne donnée ne correspond pas à une chaîne de caractères, des guillemets sont requis.\nVeuillez recommencer avec des guillemets.\n");
                    fflush(stdout);
                } else {
                    copy_val(env->phraseValeurs[phraseActuelle->uniqueId], val, true, true);
                    phraseActuelle = phraseActuelle->suivant;
                }
                free_val_t(val, true, true);
                break;
            }
            case CONVERT_TO_INT:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type == CHAINE_DE_CHAR) {
                    int value;
                    int lenght = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.chaine->chars_len;
                    if (!eval_number(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.chaine->chars, lenght, &value)) {
                        set_undefined(env->phraseValeurs[phraseActuelle->uniqueId]);
                    }
                    set_int(env->phraseValeurs[phraseActuelle->uniqueId], value);

                } else {
                    set_int(env->phraseValeurs[phraseActuelle->uniqueId], get_as_int(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env));
                }
                phraseActuelle = phraseActuelle->suivant;
                break;
            case CONVERT_TO_FLOAT:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type == CHAINE_DE_CHAR) {
                    float value;
                    int lenght = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.chaine->chars_len;
                    if (!eval_float(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.chaine->chars, lenght, &value)) {
                        set_undefined(env->phraseValeurs[phraseActuelle->uniqueId]);
                    }
                    set_float(env->phraseValeurs[phraseActuelle->uniqueId], value);

                } else {
                    set_float(env->phraseValeurs[phraseActuelle->uniqueId], get_as_float(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env));
                }
                phraseActuelle = phraseActuelle->suivant;
                break;
            case CONVERT_TO_BOOL:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type == CHAINE_DE_CHAR) {
                    int lenght = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.chaine->chars_len;
                    set_bool(env->phraseValeurs[phraseActuelle->uniqueId], (lenght != 0 && strcmp(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.chaine->chars, "faux")));
                } else {
                    set_bool(env->phraseValeurs[phraseActuelle->uniqueId], get_as_bool(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env));
                }
                phraseActuelle = phraseActuelle->suivant;
                break;
            case CONVERT_TO_CHAR:
                switch (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type) {
                    case INT: {
                        char* s = str_from_int(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.entier);
                        set_char(env->phraseValeurs[phraseActuelle->uniqueId], new_chaine_t(s));
                        free(s);
                        break;
                    }
                    case FLOAT: {
                        char* s = str_from_float(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.flottant);
                        set_char(env->phraseValeurs[phraseActuelle->uniqueId], new_chaine_t(s));
                        free(s);
                        break;
                    }
                    case BOOL:
                        if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.booleen) {
                            set_char(env->phraseValeurs[phraseActuelle->uniqueId], new_chaine_t("vrai"));
                        } else {
                            set_char(env->phraseValeurs[phraseActuelle->uniqueId], new_chaine_t("faux"));
                        }
                        break;
                    case LISTE:
                        set_char(env->phraseValeurs[phraseActuelle->uniqueId], list_to_chaine(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste));
                        break;
                    case CHAINE_DE_CHAR:

                        copy_val(env->phraseValeurs[phraseActuelle->uniqueId], env->phraseValeurs[phraseActuelle->args[0]->uniqueId], false, true);
                        break;
                    case POINTEUR:
                        set_char(env->phraseValeurs[phraseActuelle->uniqueId], new_chaine_t("ptr"));
                        break;
                    case UNDEFINED:
                        set_char(env->phraseValeurs[phraseActuelle->uniqueId], new_chaine_t("rien"));
                        break;
                }
                phraseActuelle = phraseActuelle->suivant;
                break;

            case POINTEUR_VERS_VALEUR:
                // printf("POINTEUR_VERS_VALEUR %p\n", env->phraseValeurs[phraseActuelle->args[0]->uniqueId]);
                set_pointer(env->phraseValeurs[phraseActuelle->uniqueId], env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case VALEUR_POINTEE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != POINTEUR) {
                    custom_error("La valeur donnée n'est pas un pointeur", phraseActuelle, env);
                }

                free_val_t(env->phraseValeurs[phraseActuelle->uniqueId], true, true);
                env->phraseValeurs[phraseActuelle->uniqueId] = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.ptr;
                env->phraseValeurs[phraseActuelle->uniqueId]->references++;

                phraseActuelle = phraseActuelle->suivant;
                break;
            case VALEUR_FINALE_POINTEE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != POINTEUR) {
                    custom_error("La valeur donnée n'est pas un pointeur", phraseActuelle, env);
                }
                val_t* var = env->phraseValeurs[phraseActuelle->args[0]->uniqueId];

                while (var->type == POINTEUR) {
                    var = var->value.ptr;
                }

                free_val_t(env->phraseValeurs[phraseActuelle->uniqueId], true, true);
                env->phraseValeurs[phraseActuelle->uniqueId] = var;
                env->phraseValeurs[phraseActuelle->uniqueId]->references++;

                phraseActuelle = phraseActuelle->suivant;
                break;
            case MOINS:
                moins(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
                
            case NO_ID:
                custom_error("Erreur d'interprétation", phraseActuelle, env);
                break;
        }
    }
}
