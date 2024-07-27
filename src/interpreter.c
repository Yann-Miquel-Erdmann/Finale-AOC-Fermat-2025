#include "interpreter.h"

#include <math.h>
#include <string.h>

#include "constants.h"
#include "custom_error.h"
#include "eval_numbers.h"
#include "expressions/comparateurs.h"
#include "expressions/operateurs/operateurs.h"
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
        // printf("\n");

        // printf("'%s' %d %d %d\n", phraseActuelle->text, phraseActuelle->phraseId, phraseActuelle->interpreterInnerIndex, (int)phraseActuelle->constant);
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
            case EXECUTION_FONCTION_ARGUMENT:
            {
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
                // printf("modif variable %s\n", phraseActuelle->text);
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type == POINTEUR){
                    if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.ptr == env->variable_list[phraseActuelle->variableId]->valeur){
                        custom_error("Il n'est pas possible de faire pointer une variable sur elle même", phraseActuelle, env);
                    }
                    set_pointer(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.ptr, env->variable_list[phraseActuelle->variableId]->valeur);
                }else{
                    copy_val(env->variable_list[phraseActuelle->variableId]->valeur, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
                }
                phraseActuelle = phraseActuelle->suivant;
                break;

            case MODIFICATION_VARIABLE:
                if (env->variable_list[phraseActuelle->variableId]->valeur->type == POINTEUR){
                    copy_val(env->variable_list[phraseActuelle->variableId]->valeur->value.ptr, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
                }
                else{
                    copy_val(env->variable_list[phraseActuelle->variableId]->valeur, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
                }
                
                phraseActuelle = phraseActuelle->suivant;
                break;
                
            case ACCESSION_VARIABLE:
                if (env->variable_list[phraseActuelle->variableId]->valeur->type == LISTE || env->variable_list[phraseActuelle->variableId]->valeur->type == LISTE_P) {
                    env->phraseValeurs[phraseActuelle->uniqueId]->type = env->variable_list[phraseActuelle->variableId]->valeur->type;
                    env->phraseValeurs[phraseActuelle->uniqueId]->value.liste = env->variable_list[phraseActuelle->variableId]->valeur->value.liste;
                    env->phraseValeurs[phraseActuelle->uniqueId]->type = LISTE_P;
                } else {
                    copy_val(env->phraseValeurs[phraseActuelle->uniqueId], env->variable_list[phraseActuelle->variableId]->valeur, true, true);
                }

                phraseActuelle = phraseActuelle->suivant;
                break;
                
            case POINTEUR_VARIABLE:
                //printf("got here\n");
                if (phraseActuelle->args[0]->variableId != -1){
                    set_pointer(env->variable_list[phraseActuelle->args[0]->variableId]->valeur, env->phraseValeurs[phraseActuelle->uniqueId]);
                }else{
                    if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type == LISTE_P){ // phrase en argument est un index de liste
                        val_t* temp = env->variable_list[phraseActuelle->args[0]->args[0]->variableId]->valeur->value.liste->valeurs[
                            env->phraseValeurs[phraseActuelle->args[0]->args[1]->uniqueId]->value.entier];
                        
                        set_pointer(temp, env->phraseValeurs[phraseActuelle->uniqueId]);
                    }
                    else {
                        set_pointer(env->phraseValeurs[phraseActuelle->args[0]->uniqueId], env->phraseValeurs[phraseActuelle->uniqueId]);
                    }
                }
                
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
            case EXPR_LISTE:
                if (env->variable_list[phraseActuelle->variableId]->valeur->type == POINTEUR){
                    if (*env->variable_list[phraseActuelle->variableId]->valeur->ptrType != LISTE && *env->variable_list[phraseActuelle->variableId]->valeur->ptrType != LISTE_P){
                        custom_error("La variable n'est pas une liste", phraseActuelle, env);
                    }
                    
                    env->phraseValeurs[phraseActuelle->uniqueId]->value.liste = env->variable_list[phraseActuelle->variableId]->valeur->value.ptr->value.liste;
                    env->phraseValeurs[phraseActuelle->uniqueId]->type = LISTE_P;
                }else{
                    if (env->variable_list[phraseActuelle->variableId]->valeur->type != LISTE && env->variable_list[phraseActuelle->variableId]->valeur->type != LISTE_P){
                        custom_error("La variable n'est pas une liste", phraseActuelle, env);
                    }
                    
                    // copy_val(env->phraseValeurs[phraseActuelle->uniqueId], env->variable_list[phraseActuelle->variableId]->valeur,true,true);
                    env->phraseValeurs[phraseActuelle->uniqueId]->value.liste = env->variable_list[phraseActuelle->variableId]->valeur->value.liste;
                    env->phraseValeurs[phraseActuelle->uniqueId]->type = LISTE_P;
                }
               

                phraseActuelle = phraseActuelle->suivant;
                break;

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
                    ajout(env->phraseValeurs[phraseActuelle->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[i]->uniqueId]);
                }

                phraseActuelle = phraseActuelle->suivant;
                break;

            case ACCESSION_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE && env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE_P) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }

                // ne fait pas de deep copy pour les listes et les chaînes de caractères (pour pouvoir les modifier à l’intérieur d'une liste)
                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != INT) {
                    custom_error("le type de val_t ne correspond pas, un entier est attendu", phraseActuelle, env);
                }

                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier < 0 || env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier >= env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeursLen) {
                    custom_error("indice hors de la liste", phraseActuelle, env);
                }
                switch (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier]->type) {
                    case LISTE:
                    case LISTE_P:
                        copy_val(env->phraseValeurs[phraseActuelle->uniqueId], env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier], true, false);

                        break;
                    case CHAINE_DE_CHAR:
                    case CHAINE_DE_CHAR_P:
                        copy_val(env->phraseValeurs[phraseActuelle->uniqueId], env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier], false, false);
                        break;
                    case INT:
                        if (env->phraseValeurs[phraseActuelle->uniqueId]->type == LISTE) {
                            free_liste_t(env->phraseValeurs[phraseActuelle->uniqueId]->value.liste, true, true);
                        } else if (env->phraseValeurs[phraseActuelle->uniqueId]->type == CHAINE_DE_CHAR) {
                            free_chaine_t(env->phraseValeurs[phraseActuelle->uniqueId]->value.chaine);
                        }
                        env->phraseValeurs[phraseActuelle->uniqueId]->type = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier]->type;
                        env->phraseValeurs[phraseActuelle->uniqueId]->value.entier = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier]->value.entier;
                        break;
                    case FLOAT:
                        if (env->phraseValeurs[phraseActuelle->uniqueId]->type == LISTE) {
                            free_liste_t(env->phraseValeurs[phraseActuelle->uniqueId]->value.liste, true, true);
                        } else if (env->phraseValeurs[phraseActuelle->uniqueId]->type == CHAINE_DE_CHAR) {
                            free_chaine_t(env->phraseValeurs[phraseActuelle->uniqueId]->value.chaine);
                        }
                        env->phraseValeurs[phraseActuelle->uniqueId]->type = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier]->type;
                        env->phraseValeurs[phraseActuelle->uniqueId]->value.flottant = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier]->value.flottant;
                        break;
                    case BOOL:
                        if (env->phraseValeurs[phraseActuelle->uniqueId]->type == LISTE) {
                            free_liste_t(env->phraseValeurs[phraseActuelle->uniqueId]->value.liste, true, true);
                        } else if (env->phraseValeurs[phraseActuelle->uniqueId]->type == CHAINE_DE_CHAR) {
                            free_chaine_t(env->phraseValeurs[phraseActuelle->uniqueId]->value.chaine);
                        }

                        env->phraseValeurs[phraseActuelle->uniqueId]->type = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier]->type;
                        env->phraseValeurs[phraseActuelle->uniqueId]->value.booleen = env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste->valeurs[env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier]->value.booleen;
                        break;
                }
                phraseActuelle = phraseActuelle->suivant;
                break;

            case MODIFICATION_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE && env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE_P)) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != INT) {
                    custom_error("le type de val_t ne correspond pas, un entier est attendu", phraseActuelle, env);
                }
                modification(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier, env->phraseValeurs[phraseActuelle->args[2]->uniqueId], phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case AJOUT_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE && env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE_P)) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                ajout(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[1]->uniqueId]);
                
                phraseActuelle = phraseActuelle->suivant;
                break;

            case SUPPRESSION_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[0]->uniqueId] == NULL || (env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE && env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->type != LISTE_P)) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != INT) {
                    custom_error("le type de val_t ne correspond pas, un entier est attendu", phraseActuelle, env);
                }
                suppression(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.entier, phraseActuelle, env);

                phraseActuelle = phraseActuelle->suivant;
                break;

            case INSERTION_LISTE:
                if (env->phraseValeurs[phraseActuelle->args[1]->uniqueId] == NULL || (env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != LISTE && env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->type != LISTE_P)) {
                    custom_error("La variable n'est pas une liste", phraseActuelle, env);
                }
                if (env->phraseValeurs[phraseActuelle->args[2]->uniqueId]->type != INT) {
                    custom_error("le type de val_t ne correspond pas, un entier est attendu", phraseActuelle, env);
                }
                inserer(env->phraseValeurs[phraseActuelle->args[1]->uniqueId]->value.liste, env->phraseValeurs[phraseActuelle->args[2]->uniqueId]->value.entier, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], phraseActuelle, env);

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
                if (env->variable_list[phraseActuelle->variableId]->valeur->type == UNDEFINED) {  //  initialisation de l’itérateur
                    copy_val(env->variable_list[phraseActuelle->variableId]->valeur, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
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
                    env->variable_list[phraseActuelle->variableId]->valeur->type = UNDEFINED;
                    phraseActuelle = phraseActuelle->suivant;
                }

                break;

            case POUR_SANS_PAS:
                if (env->variable_list[phraseActuelle->variableId]->valeur->type == UNDEFINED) {  //  initialisation de l’itérateur
                    copy_val(env->variable_list[phraseActuelle->variableId]->valeur, env->phraseValeurs[phraseActuelle->args[0]->uniqueId], true, true);
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
                    env->variable_list[phraseActuelle->variableId]->valeur->type = UNDEFINED;
                    phraseActuelle = phraseActuelle->suivant;
                }
                break;

            case QUITTER_BOUCLE:
                // réinitialise l'itérateur de la boucle pour
                if (phraseActuelle->suivant->phraseId == POUR_AVEC_PAS || phraseActuelle->suivant->phraseId == POUR_SANS_PAS) {
                    env->variable_list[phraseActuelle->suivant->variableId]->valeur->type = UNDEFINED;
                }

                phraseActuelle = phraseActuelle->suivant->suivant;
                break;

            case TYPE_EXPR:
                env->phraseValeurs[phraseActuelle->uniqueId]->value.chaine = new_chaine_t(str_type(env->phraseValeurs[phraseActuelle->args[0]->uniqueId]));

                phraseActuelle = phraseActuelle->suivant;
                break;

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
                // default:
                //     printf("erreur: %d, %d\n", phraseActuelle->phraseId, phraseActuelle->constant);
                //     custom_error("erreur d'interprétation", phraseActuelle, env);
                //     break;
        }
    }
}
