#include "interpreter.h"

#include <math.h>
#include <string.h>

#include "constants.h"
#include "custom_error.h"
#include "eval_numbers.h"
#include "expressions/comparateurs.h"
#include "expressions/operateurs.h"
#include "syntax_convert.h"

void interpreter(function_t* function, function_list_t* functions, val_t* result, int layer) {
    if (layer > MAX_RECUSION_DEPTH) {
        custom_error("limite de récursion atteinte", NULL, NULL);
    }
    if (function->ast->innerPhraseLen == 0) {
        return;
    }

    environnement_t* env = function->env;

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
        // printf("\n");F

        // printf("'%s' %d %d %d\n", phraseActuelle->text, phraseActuelle->phraseId, phraseActuelle->interpreterInnerIndex, (int)phraseActuelle->constant);
        switch (phraseActuelle->phraseId) {
            case DEFINITION_FONCTION_ARGUMENT:
            case DEFINITION_FONCTION: {
                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case MAIN_PHRASE: {
                // printf("main\n");
                phraseActuelle = phraseActuelle->suivantInner1;
                // printf("%s\n", phraseActuelle->text);
                break;
            }

            case APPEL_VALEUR_FONCTION:
            case EXECUTION_FONCTION:
            case APPEL_VALEUR_FONCTION_ARGUMENT:
            case EXECUTION_FONCTION_ARGUMENT: {
                function_t* new_func = malloc(sizeof(function_t));
                new_func->nom = phraseActuelle->function->nom;
                new_func->ast = phraseActuelle->function->ast;
                new_func->function_arg_count = phraseActuelle->function->function_arg_count;
                new_func->env = copy_environnement(phraseActuelle->function->env);
                new_func->ast->phraseId = 0;

                if (phraseActuelle->phraseId == APPEL_VALEUR_FONCTION_ARGUMENT || phraseActuelle->phraseId == EXECUTION_FONCTION_ARGUMENT) {
                    if (phraseActuelle->argsLen != new_func->function_arg_count) {
                        custom_error("Le nombre d'arguments données ne correspond pas ou nombre d'arguments voulus", phraseActuelle, env);
                    }
                    for (int i = 0; i < phraseActuelle->argsLen; i++) {
                        copy_val(new_func->env->variable_list[i]->valeur,
                                 env->phraseValeurs[phraseActuelle->args[i]->uniqueId], true, true);
                    }
                }

                if (phraseActuelle->phraseId == EXECUTION_FONCTION_ARGUMENT || phraseActuelle->phraseId == EXECUTION_FONCTION) {
                    if (phraseActuelle->argsLen != new_func->function_arg_count) {
                        custom_error("Le nombre d'arguments données ne correspond pas ou nombre d'arguments voulus", phraseActuelle, env);
                    }
                    interpreter(new_func, functions, NULL, layer + 1);
                } else {
                    if (phraseActuelle->argsLen != new_func->function_arg_count) {
                        custom_error("Le nombre d'arguments données ne correspond pas ou nombre d'arguments voulus", phraseActuelle, env);
                    }
                    interpreter(new_func, functions, env->phraseValeurs[phraseActuelle->uniqueId], layer + 1);
                }

                free_environnement(new_func->env);
                free(new_func);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }

            case RENVOI_FONCTION: {
                if (result != NULL) {
                    copy_val(result, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
                }
                return;
                break;
            }

            case AFFICHER_EXPR:
            case AFFICHER_EXPR_NO_RETURN: {
                for (int i = 0; i < phraseActuelle->argsLen - 1; i++) {
                    print_val(env->phraseValeurs[phraseActuelle->args[i]->uniqueId], false, phraseActuelle, env);
                    printf(" ");
                }
                print_val(env->phraseValeurs[phraseActuelle->args[phraseActuelle->argsLen - 1]->uniqueId], phraseActuelle->phraseId == AFFICHER_EXPR, phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case TAILLE: {
                taille(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }

            // variable ------------------------------------------------------
            case MODIFICATION_VARIABLE:
            case DEFINITION_VARIABLE_AVEC_INIT: {
                // printf("modif variable %s\n", phraseActuelle->text);
                copy_val(getVariable(env, phraseActuelle->variableId)->valeur, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }

            case ACCESSION_VARIABLE: {
                if (getVariable(env, phraseActuelle->variableId)->valeur->type == LISTE) {
                    env->phraseValeurs[phraseActuelle->uniqueId]->type = getVariable(env, phraseActuelle->variableId)->valeur->type;
                    env->phraseValeurs[phraseActuelle->uniqueId]->liste = getVariable(env, phraseActuelle->variableId)->valeur->liste;
                    env->phraseValeurs[phraseActuelle->uniqueId]->to_free_list = false;

                } else {
                    copy_val(env->phraseValeurs[phraseActuelle->uniqueId], getVariable(env, phraseActuelle->variableId)->valeur, true, true);
                }

                phraseActuelle = phraseActuelle->suivant;
                break;
            }

                // opérateurs ---------------------------------------------------
            case SOMME: {
                somme(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case DIFFERENCE: {
                difference(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case PRODUIT: {
                produit(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case QUOTIENT: {
                quotient(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case QUOTIENT_ENTIER: {
                quotient_entier(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case RESTE: {
                reste(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case NEGATION_BOOLEENNE: {
                negation_booleenne(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
                // comparateurs ----------------------------------------------------------
            case EGALITE: {
                egalite(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case INEGALITE: {
                inegalite(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case PLUS_GRAND: {
                plus_grand(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case STRICT_PLUS_GRAND: {
                strict_plus_grand(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case PLUS_PETIT: {
                plus_petit(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case STRICT_PLUS_PETIT: {
                strict_plus_petit(phraseActuelle, env);
                phraseActuelle = phraseActuelle->suivant;
                break;
            }

            // liste -----------------------------------------------------------------
            case EXPR_LISTE: {
                if (getVariable(env, phraseActuelle->variableId)->valeur->type != LISTE) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }

                // copy_val(env->phraseValeurs[phraseActuelle->uniqueId], getVariable(env,phraseActuelle->variableId)->valeur,true,true);
                env->phraseValeurs[phraseActuelle->uniqueId]->type = getVariable(env, phraseActuelle->variableId)->valeur->type;
                env->phraseValeurs[phraseActuelle->uniqueId]->liste = getVariable(env, phraseActuelle->variableId)->valeur->liste;
                env->phraseValeurs[phraseActuelle->uniqueId]->to_free_list = false;

                phraseActuelle = phraseActuelle->suivant;
                break;
            }

            case EXPR_LISTE_VIDE: {
                vider_liste(env->phraseValeurs[phraseActuelle->uniqueId]->liste);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }

            case EXPR_LISTE_ELEM: {
                if (env->phraseValeurs[phraseActuelle->uniqueId]->to_free_list) {
                    vider_liste(env->phraseValeurs[phraseActuelle->uniqueId]->liste);
                }
                if (env->phraseValeurs[phraseActuelle->uniqueId]->type != LISTE) {
                    env->phraseValeurs[phraseActuelle->uniqueId]->type = LISTE;
                    env->phraseValeurs[phraseActuelle->uniqueId]->liste = new_liste_t();
                }

                env->phraseValeurs[phraseActuelle->uniqueId]->to_free_list = true;
                for (int i = 0; i < phraseActuelle->argsLen; i++) {
                    ajout(env->phraseValeurs[phraseActuelle->uniqueId]->liste, env->phraseValeurs[phraseActuelle->args[i]->uniqueId]);
                }

                phraseActuelle = phraseActuelle->suivant;
                break;
            }

            case ACCESSION_LISTE: {
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                // ne fait pas de deep copy pour les listes et les chaînes de caractères (pour pouvoir les modifier à l’intérieur d'une liste)
                if (accession(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->liste, get_int(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env), phraseActuelle, env)->type == LISTE) {
                    copy_val(env->phraseValeurs[phraseActuelle->uniqueId], accession(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->liste, get_int(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env), phraseActuelle, env), true, false);
                } else if (accession(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->liste, get_int(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env), phraseActuelle, env)->type == CHAINE_DE_CHAR) {
                    copy_val(env->phraseValeurs[phraseActuelle->uniqueId], accession(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->liste, get_int(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env), phraseActuelle, env), false, true);
                } else {
                    copy_val(env->phraseValeurs[phraseActuelle->uniqueId], accession(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->liste, get_int(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env), phraseActuelle, env), true, true);
                }

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case MODIFICATION_LISTE: {
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                modification(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->liste, get_int(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env), env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case AJOUT_LISTE: {
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                ajout(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->liste, env->phraseValeurs[phraseActuelle->args[1]->uniqueId]);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case SUPPRESSION_LISTE: {
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                suppression(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->liste, get_int(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env), phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case INSERTION_LISTE: {
                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId] == NULL || env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != LISTE) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                inserer(env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->liste, get_int(env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env), env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case SI_ALORS: {
                if (get_bool(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env)) {
                    phraseActuelle = phraseActuelle->suivantInner1;
                } else {
                    phraseActuelle = phraseActuelle->suivant;
                }
                break;
            }

            case SI_ALORS_SINON: {
                if (get_bool(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env)) {
                    phraseActuelle = phraseActuelle->suivantInner1;
                } else {
                    phraseActuelle = phraseActuelle->suivantInner2;
                }

                break;
            }

            case TANT_QUE: {
                if (get_bool(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env)) {
                    phraseActuelle = phraseActuelle->suivantInner1;
                } else {
                    phraseActuelle = phraseActuelle->suivant;
                }
                break;
            }

            case POUR_AVEC_PAS:
            case POUR_SANS_PAS: {
                if (getVariable(env, phraseActuelle->variableId)->valeur->type == UNDEFINED) {  //  initialisation de l’itérateur
                    copy_val(getVariable(env, phraseActuelle->variableId)->valeur, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
                } else {  // incrémentation de l'itérateur
                    if (phraseActuelle->phraseId == POUR_AVEC_PAS) {
                        if (getVariable(env, phraseActuelle->variableId)->valeur->type == FLOAT || env->phraseValeurs[phraseActuelle->args[2]->uniqueId]->type == FLOAT) {
                            set_float(getVariable(env, phraseActuelle->variableId)->valeur, get_as_float(getVariable(env, phraseActuelle->variableId)->valeur, phraseActuelle, env) + get_as_float(env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env));
                        } else {
                            set_int(getVariable(env, phraseActuelle->variableId)->valeur, get_as_int(getVariable(env, phraseActuelle->variableId)->valeur, phraseActuelle, env) + get_as_int(env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env));
                        }
                    } else {
                        if (getVariable(env, phraseActuelle->variableId)->valeur->type == FLOAT) {
                            set_float(getVariable(env, phraseActuelle->variableId)->valeur, get_as_float(getVariable(env, phraseActuelle->variableId)->valeur, phraseActuelle, env) + 1);
                        } else {
                            set_int(getVariable(env, phraseActuelle->variableId)->valeur, get_as_int(getVariable(env, phraseActuelle->variableId)->valeur, phraseActuelle, env) + 1);
                        }
                    }
                }

                if (get_as_float(getVariable(env, phraseActuelle->variableId)->valeur, phraseActuelle, env) < get_as_float(env->phraseValeurs[phraseActuelle->args[1]->uniqueId], phraseActuelle, env)) {
                    phraseActuelle = phraseActuelle->suivantInner1;
                } else {
                    getVariable(env, phraseActuelle->variableId)->valeur->type = UNDEFINED;
                    phraseActuelle = phraseActuelle->suivant;
                }
                break;
            }

            case QUITTER_BOUCLE: {
                // réinitialise l'itérateur de la boucle pour
                if (phraseActuelle->suivant->phraseId == POUR_AVEC_PAS || phraseActuelle->suivant->phraseId == POUR_SANS_PAS) {
                    getVariable(env, phraseActuelle->suivant->variableId)->valeur->type = UNDEFINED;
                }

                phraseActuelle = phraseActuelle->suivant->suivant;
                break;
            }

            case TYPE_EXPR: {
                env->phraseValeurs[phraseActuelle->uniqueId]->chaine = new_chaine_t(str_type(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]));

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case ET: {
                et_booleen(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case OU: {
                ou_booleen(phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            case EXPR_RIEN: {
                set_undefined(env->phraseValeurs[phraseActuelle->uniqueId]);

                phraseActuelle = phraseActuelle->suivant;
                break;
            }
            default:
                printf("erreur: %d, %d\n", phraseActuelle->phraseId, phraseActuelle->constant);
                custom_error("erreur d'interprétation", phraseActuelle, env);
                break;
        }
    }
}
