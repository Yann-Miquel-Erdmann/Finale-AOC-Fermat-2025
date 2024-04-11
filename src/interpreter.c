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

                case EXECUTION_FONCTION: {
                    // printf("execution de la fonction %s\n", phraseActuelle->function->nom);

                    function_t* new_func = copy_function(phraseActuelle->function);
                    new_func->ast->phraseId = 0;
                    interpreter(new_func, functions, phraseActuelle->valeur, layer + 1);
                    free_function_t(new_func);

                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case EXECUTION_FONCTION_ARGUMENT: {
                    // printf("execution de la fonction avec arg %s\n", phraseActuelle->function->nom);
                    function_t* new_func = copy_function(phraseActuelle->function);
                    new_func->ast->phraseId = 0;

                    // printf("%d\n", new_func->env->variable_list_len);
                    //  initialise les arguments
                    for (int i = 0; i < phraseActuelle->argsLen; i++) {
                        copy_val(new_func->env->variable_list[i]->valeur,
                                 phraseActuelle->args[i]->valeur);
                    }

                    interpreter(new_func, functions, phraseActuelle->valeur, layer + 1);
                    free_function_t(new_func);

                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case RENVOI_FONCTION: {
                    if (result != NULL && phraseActuelle->argsLen > 0) {
                        copy_val(result, phraseActuelle->args[0]->valeur);
                    }
                    return;
                    break;
                }

                case AFFICHER_EXPR: {
                    print_val(phraseActuelle->args[0]->valeur, true);
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
                    copy_val(phraseActuelle->variable->valeur, phraseActuelle->args[0]->valeur);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case ACCESSION_VARIABLE: {
                    copy_val(phraseActuelle->valeur, phraseActuelle->variable->valeur);
                    // printf("'%d'\n", get_int(phraseActuelle->valeur));
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
                case ACCESSION_LISTE: {
                    copy_val(phraseActuelle->valeur, accession(phraseActuelle->valeur->liste, get_int(phraseActuelle->args[0]->valeur), phraseActuelle));
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case MODIFICATION_LISTE: {
                    modification(phraseActuelle->valeur->liste, get_int(phraseActuelle->args[0]->valeur), phraseActuelle->args[1]->valeur, phraseActuelle);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case AJOUT_LISTE: {
                    ajout(phraseActuelle->valeur->liste, phraseActuelle->args[0]->valeur);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case SUPPRESSION_LISTE: {
                    suppression(phraseActuelle->valeur->liste, get_int(phraseActuelle->args[0]->valeur), phraseActuelle);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                case INSERTION_LISTE: {
                    // printf("%d\n", phraseActuelle->args[1]->valeur->type);
                    inserer(phraseActuelle->valeur->liste, get_int(phraseActuelle->args[1]->valeur), phraseActuelle->args[0]->valeur, phraseActuelle);
                    phraseActuelle->interpreterArgsIndex = 0;
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case SI_ALORS: {
                    if (phraseActuelle->interpreterInnerIndex == -1) {
                        phraseActuelle->interpreterInnerIndex = 0;
                    }

                    if (get_bool(phraseActuelle->args[0]->valeur)) {
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
                    if (get_bool(phraseActuelle->args[0]->valeur)) {
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

                case TANT_QUE:{
                    if (phraseActuelle->interpreterInnerIndex == -1) {
                        phraseActuelle->interpreterInnerIndex = 0;
                    }

                    if (get_bool(phraseActuelle->args[0]->valeur)) {
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

                default:
                    // printf("erreur: %d, %d\n", phraseActuelle->phraseId, phraseActuelle->constant);
                    custom_error("erreur d'interprétation", phraseActuelle);
                    break;
            }
            
        }
    }
}
