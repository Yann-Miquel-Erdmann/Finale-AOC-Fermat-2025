#include "interpreter.h"

#include <string.h>

#include "constants.h"
#include "custom_error.h"
#include "eval_numbers.h"
#include "expressions/comparateurs.h"
#include "expressions/operateurs.h"

void interpreter(function_t* function, function_list_t* functions, val_t* result, int layer) {
    if (layer > MAX_RECUSION_DEPTH) {
        custom_error("limite de récursion atteinte", NULL);
    }
    phrase_t* phraseActuelle = function->ast;

    while (phraseActuelle != NULL) {
        // printf("'%s' %d %d %d %d %p\n", phraseActuelle->text, phraseActuelle->phraseId, phraseActuelle->argsLen, phraseActuelle->interpreterArgsIndex, (int)phraseActuelle->constant, phraseActuelle);

        if (phraseActuelle->constant) {
            phraseActuelle->interpreterArgsIndex = 0;
            phraseActuelle = phraseActuelle->parentPhrase;
        } else if (phraseActuelle->interpreterArgsIndex < phraseActuelle->argsLen) {
            phraseActuelle->interpreterArgsIndex++;
            phraseActuelle = phraseActuelle->args[phraseActuelle->interpreterArgsIndex - 1];
        } else {
            // printf("'%s' %d %d %d\n", phraseActuelle->text, phraseActuelle->phraseId, phraseActuelle->interpreterInnerIndex, (int)phraseActuelle->constant);
            switch (phraseActuelle->phraseId) {
                case DEFINITION_FONCTION_ARGUMENT:
                case DEFINITION_FONCTION: {
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case MAIN_PHRASE: {
                    if (phraseActuelle->interpreterInnerIndex == -1) {
                        phraseActuelle->interpreterInnerIndex = 0;
                    }

                    // printf("main phrase: '%s', %d\n", function->nom, phraseActuelle->interpreterInnerIndex);
                    if (phraseActuelle->interpreterInnerIndex < phraseActuelle->innerPhraseLen) {
                        phraseActuelle->interpreterInnerIndex++;
                        // printf("'%s' %d %d %d, %d\n", phraseActuelle->text, phraseActuelle->phraseId, phraseActuelle->interpreterInnerIndex, phraseActuelle->innerPhraseLen, (int)phraseActuelle->constant);
                        phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                    } else {
                        phraseActuelle->interpreterArgsIndex = 0;
                        phraseActuelle = phraseActuelle->parentPhrase;
                    }
                    break;
                }

                case APPEL_VALEUR_FONCTION:
                case EXECUTION_FONCTION:
                case APPEL_VALEUR_FONCTION_ARGUMENT:
                case EXECUTION_FONCTION_ARGUMENT: {
                    function_t* new_func = copy_function(phraseActuelle->function);
                    new_func->ast->phraseId = 0;

                    if (phraseActuelle->phraseId == APPEL_VALEUR_FONCTION_ARGUMENT || phraseActuelle->phraseId == EXECUTION_FONCTION_ARGUMENT) {
                        for (int i = 0; i < phraseActuelle->argsLen; i++) {
                            copy_val(new_func->env->variable_list[i]->valeur,
                                     phraseActuelle->args[i]->valeur, true, true);
                        }
                    }

                    if (phraseActuelle->phraseId == EXECUTION_FONCTION_ARGUMENT || phraseActuelle->phraseId == EXECUTION_FONCTION) {
                        interpreter(new_func, functions, NULL, layer + 1);
                    } else {
                        interpreter(new_func, functions, phraseActuelle->valeur, layer + 1);
                    }

                    free_function_t(new_func);

                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case RENVOI_FONCTION: {
                    if (result != NULL) {
                        copy_val(result, phraseActuelle->args[0]->valeur, true, true);
                    }
                    return;
                    break;
                }

                case AFFICHER_EXPR: {
                    print_val(phraseActuelle->args[0]->valeur, true, phraseActuelle);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case TAILLE: {
                    if (phraseActuelle->args[0]->valeur->type == LISTE) {
                        set_int(phraseActuelle->valeur, taille(phraseActuelle->args[0]->valeur->liste));
                    } else if (phraseActuelle->args[0]->valeur->type == CHAINE_DE_CHAR) {
                        set_int(phraseActuelle->valeur, phraseActuelle->args[0]->valeur->chaine->chars_len);
                    } else {
                        custom_error("taille ne peut être appliqué qu'à une liste ou une chaîne de caractères", phraseActuelle);
                    }
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                // variable ------------------------------------------------------
                case MODIFICATION_VARIABLE:
                case DEFINITION_VARIABLE_AVEC_INIT: {
                    copy_val(phraseActuelle->variable->valeur, phraseActuelle->args[0]->valeur, true, true);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case ACCESSION_VARIABLE: {
                    copy_val(phraseActuelle->valeur, phraseActuelle->variable->valeur, true, true);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                    // opérateurs ---------------------------------------------------
                case SOMME: {
                    somme(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case DIFFERENCE: {
                    difference(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case PRODUIT: {
                    produit(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case QUOTIENT: {
                    quotient(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case QUOTIENT_ENTIER: {
                    quotient_entier(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case RESTE: {
                    reste(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case NEGATION_BOOLEENNE: {
                    negation_booleenne(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                    // comparateurs ----------------------------------------------------------
                case EGALITE: {
                    egalite(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case PLUS_GRAND: {
                    plus_grand(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case STRICT_PLUS_GRAND: {
                    strict_plus_grand(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case PLUS_PETIT: {
                    plus_petit(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case STRICT_PLUS_PETIT: {
                    strict_plus_petit(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                // liste -----------------------------------------------------------------
                case EXPR_LISTE: {
                    phraseActuelle->valeur->type = phraseActuelle->variable->valeur->type;
                    phraseActuelle->valeur->liste = phraseActuelle->variable->valeur->liste;
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case EXPR_LISTE_VIDE: {
                    vider_liste(phraseActuelle->valeur->liste);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                
                case EXPR_LISTE_ELEM :{
                    if (phraseActuelle->valeur->to_free_list){
                        vider_liste(phraseActuelle->valeur->liste);
                    }
                    if (phraseActuelle->valeur->type != LISTE){
                        phraseActuelle->valeur->type = LISTE;
                        phraseActuelle->valeur->liste = new_liste_t();
                    }
                    
                    phraseActuelle->valeur->to_free_list = true;
                    for (int i = 0; i< phraseActuelle->argsLen; i++){
                        ajout(phraseActuelle->valeur->liste, phraseActuelle->args[i]->valeur);
                    }
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                
                case ACCESSION_LISTE: {
                    copy_val(phraseActuelle->valeur, accession(phraseActuelle->args[0]->valeur->liste, get_int(phraseActuelle->args[0]->valeur), phraseActuelle), true, true);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case MODIFICATION_LISTE: {
                    modification(phraseActuelle->args[0]->valeur->liste, get_int(phraseActuelle->args[1]->valeur), phraseActuelle->args[1]->valeur, phraseActuelle);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case AJOUT_LISTE: {
                    ajout(phraseActuelle->args[0]->valeur->liste, phraseActuelle->args[1]->valeur);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case SUPPRESSION_LISTE: {
                    suppression(phraseActuelle->args[0]->valeur->liste, get_int(phraseActuelle->args[1]->valeur), phraseActuelle);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case INSERTION_LISTE: {
                    inserer(phraseActuelle->args[1]->valeur->liste, get_int(phraseActuelle->args[2]->valeur), phraseActuelle->args[0]->valeur, phraseActuelle);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case SI_ALORS: {
                    if (phraseActuelle->interpreterInnerIndex == -1) {
                        phraseActuelle->interpreterInnerIndex = 0;
                    }

                    if (get_bool(phraseActuelle->args[0]->valeur, phraseActuelle)) {
                        if (phraseActuelle->interpreterInnerIndex < phraseActuelle->innerPhraseLen) {
                            phraseActuelle->interpreterInnerIndex++;
                            phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                        } else {
                            phraseActuelle->interpreterInnerIndex = 0;
                            phraseActuelle->interpreterArgsIndex = 0;
                            phraseActuelle = phraseActuelle->parentPhrase;
                        }
                    } else {
                        phraseActuelle->interpreterInnerIndex = -1;
                        phraseActuelle->interpreterArgsIndex = 0;
                        phraseActuelle = phraseActuelle->parentPhrase;
                    }
                    break;
                }

                case SI_ALORS_SINON: {
                    if (phraseActuelle->interpreterInnerIndex == -1) {
                        phraseActuelle->interpreterInnerIndex = 0;
                    }
                    if (get_bool(phraseActuelle->args[0]->valeur, phraseActuelle)) {
                        if (phraseActuelle->interpreterInnerIndex <= phraseActuelle->innerSeparator) {
                            phraseActuelle->interpreterInnerIndex++;
                            phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                        } else {
                            phraseActuelle->interpreterInnerIndex = -1;
                            phraseActuelle->interpreterArgsIndex = 0;
                            phraseActuelle = phraseActuelle->parentPhrase;
                        }

                    } else {
                        if (phraseActuelle->interpreterInnerIndex == 0) {
                            phraseActuelle->interpreterInnerIndex = phraseActuelle->innerSeparator + 1;
                        }
                        if (phraseActuelle->interpreterInnerIndex < phraseActuelle->innerPhraseLen) {
                            phraseActuelle->interpreterInnerIndex++;
                            phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                        } else {
                            phraseActuelle->interpreterInnerIndex = -1;
                            phraseActuelle->interpreterArgsIndex = 0;
                            phraseActuelle = phraseActuelle->parentPhrase;
                        }
                    }

                    break;
                }

                case TANT_QUE: {
                    if (phraseActuelle->interpreterInnerIndex == -1) {
                        phraseActuelle->interpreterInnerIndex = 0;
                    }

                    if (get_bool(phraseActuelle->args[0]->valeur, phraseActuelle)) {
                        if (phraseActuelle->interpreterInnerIndex < phraseActuelle->innerPhraseLen) {
                            phraseActuelle->interpreterInnerIndex++;
                            phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                        } else {
                            phraseActuelle->interpreterArgsIndex = 0;
                            phraseActuelle->interpreterInnerIndex = -1;
                        }
                    } else {
                        phraseActuelle->interpreterInnerIndex = -1;
                        phraseActuelle->interpreterArgsIndex = 0;
                        phraseActuelle = phraseActuelle->parentPhrase;
                    }
                    break;
                }

                case POUR_AVEC_PAS:
                case POUR_SANS_PAS: {
                    if (phraseActuelle->interpreterInnerIndex == -1) {
                        phraseActuelle->interpreterInnerIndex = 0;
                        copy_val(phraseActuelle->variable->valeur, phraseActuelle->args[0]->valeur, true, true);
                    }

                    if (get_as_float(phraseActuelle->variable->valeur, phraseActuelle) < get_as_float(phraseActuelle->args[1]->valeur, phraseActuelle)) {
                        if (phraseActuelle->interpreterInnerIndex < phraseActuelle->innerPhraseLen) {
                            phraseActuelle->interpreterInnerIndex++;
                            phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                        } else {
                            phraseActuelle->interpreterInnerIndex = 0;

                            if (phraseActuelle->phraseId == POUR_AVEC_PAS) {
                                if (phraseActuelle->variable->valeur->type == FLOAT || phraseActuelle->args[2]->valeur->type == FLOAT){
                                    set_float(phraseActuelle->variable->valeur, get_as_float(phraseActuelle->variable->valeur, phraseActuelle) + get_as_float(phraseActuelle->args[2]->valeur, phraseActuelle));
                                }else{
                                    set_int(phraseActuelle->variable->valeur, get_as_int(phraseActuelle->variable->valeur, phraseActuelle) + get_as_int(phraseActuelle->args[2]->valeur, phraseActuelle));
                                }
                            } else {
                                if (phraseActuelle->variable->valeur->type == FLOAT){
                                    set_float(phraseActuelle->variable->valeur, get_as_float(phraseActuelle->variable->valeur, phraseActuelle) + 1);
                                }else{
                                    set_int(phraseActuelle->variable->valeur, get_as_int(phraseActuelle->variable->valeur, phraseActuelle) + 1);
                                }
                            }
                        }
                    } else {
                        phraseActuelle->interpreterInnerIndex = -1;
                        phraseActuelle->interpreterArgsIndex = 0;
                        phraseActuelle = phraseActuelle->parentPhrase;
                    }

                    break;
                }
                case TYPE_EXPR:{
                    char* type = malloc(DEFAULT_CHAINE_CHARS_SIZE*sizeof(char));
                    switch (phraseActuelle->args[0]->valeur->type) {
                        case INT:
                            strcpy(type, "INT");
                            break;
                        case FLOAT:
                            strcpy(type, "FLOAT");
                            break;
                        case LISTE:
                            strcpy(type, "LISTE");
                            break;
                        case BOOL:
                            strcpy(type, "BOOL");
                            break;
                        case CHAINE_DE_CHAR:
                            strcpy(type, "CHAINE_DE_CHAR");
                            break;
                        default:
                            strcpy(type, "UNDEFINED");
                            break;
                    }
                    phraseActuelle->valeur->chaine = new_chaine_t(type);
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case ET:{
                    et_booleen(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case OU:{
                    ou_booleen(phraseActuelle, false);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case EXPR_RIEN:{
                    set_undefined(phraseActuelle->valeur);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                default:
                    printf("erreur: %d, %d\n", phraseActuelle->phraseId, phraseActuelle->constant);
                    custom_error("erreur d'interprétation", phraseActuelle);
                    break;
            }
        }
    }
}
