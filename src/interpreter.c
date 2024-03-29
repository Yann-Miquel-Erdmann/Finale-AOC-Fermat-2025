#include "interpreter.h"

#include <string.h>

#include "constants.h"
#include "custom_error.h"
#include "eval_numbers.h"
#include <string.h>


void interpreter(function_t* function, function_list_t* functions, val_t* result, int layer) {
    if (layer > MAX_RECUSION_DEPTH) {
        custom_error("limite de récursion atteinte", NULL);
    }

    phrase_t* phraseActuelle = function->ast;

    while (phraseActuelle != NULL) {
        //printf("'%s' %d %d %d %d\n", phraseActuelle->text, phraseActuelle->phraseId, phraseActuelle->argsLen, phraseActuelle->interpreterArgsIndex, (int)phraseActuelle->constant);
        if (phraseActuelle->constant) {
            phraseActuelle = phraseActuelle->parentPhrase;
        } else if (phraseActuelle->interpreterArgsIndex < phraseActuelle->argsLen) {
            phraseActuelle->interpreterArgsIndex++;
            phraseActuelle = phraseActuelle->args[phraseActuelle->interpreterArgsIndex - 1];
        } else {
            switch (phraseActuelle->phraseId) {
                case MAIN_PHRASE: {
                    printf("main phrase: %s\n", function->nom);
                    if (phraseActuelle->interpreterInnerIndex < phraseActuelle->innerPhraseLen) {
                        phraseActuelle->interpreterInnerIndex++;
                        phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                    } else {
                        phraseActuelle = phraseActuelle->parentPhrase;
                    }
                    break;
                }

                case EXECUTION_FONCTION: {
                    //printf("execution de la fonction %s\n", phraseActuelle->function->nom);
                    function_t* new_func = copy_function(phraseActuelle->function);
                    interpreter(new_func, functions, phraseActuelle->valeur, layer + 1);
                    free_function_t(new_func);

                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case EXECUTION_FONCTION_ARGUMENT: {
                    //printf("execution de la fonction %s\n", phraseActuelle->function->nom);
                    function_t* new_func = copy_function(phraseActuelle->function);

                    // initialise les arguments
                    for (int i = 0; i < phraseActuelle->argsLen; i++) {
                        copy_val(new_func->env->variable_list[i]->valeur, phraseActuelle->args[i]->valeur);
                    }

                    interpreter(new_func, functions, phraseActuelle->valeur, layer + 1);
                    free_function_t(new_func);

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

                case AFFICHE_STR: {
                    printf("%s\n", phraseActuelle->args[0]->text);
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }

                case AFFICHE_EXPR: {
                    //printf("affiche expr\n");
                    if (phraseActuelle->args[0]->valeur != NULL) {
                        if (phraseActuelle->args[0]->valeur->type == BOOL) {
                            if (get_bool(phraseActuelle->args[0]->valeur)) {
                                printf("Vrai\n");
                            } else {
                                printf("Faux\n");
                            }

                        } else if (phraseActuelle->args[0]->valeur->type == INT) {
                            char* str = str_from_int(phraseActuelle->args[0]->valeur->value);
                            printf("%s\n", str);
                            free(str);

                        } else if (phraseActuelle->args[0]->valeur->type == FLOAT) {
                            char* str = str_from_float(phraseActuelle->args[0]->valeur->value);
                            printf("%s\n", str);
                            free(str);

                        } else {
                            custom_error("Type non supporté pour l'affichage", phraseActuelle);
                        }
                    }
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;
                }
                    
                case SI_ALORS: {
                    printf("if statement\n");
                    if (phraseActuelle->args[0]->constant) { // TODO enlever ça -> interpreter normalement
                        if (phraseActuelle->interpreterInnerIndex == -1){
                            phraseActuelle->interpreterInnerIndex = 0;
                        }
                        if (get_bool(phraseActuelle->args[0]->valeur)){
                            //printf("true\n");
                            if (phraseActuelle->interpreterInnerIndex < phraseActuelle->innerPhraseLen) {
                                phraseActuelle->interpreterInnerIndex++;
                                phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                            } else {
                                phraseActuelle->interpreterInnerIndex = 0;
                                phraseActuelle = phraseActuelle->parentPhrase;
                            }
                        }else{
                            //printf("false\n");
                            phraseActuelle->interpreterInnerIndex = -1;
                            phraseActuelle = phraseActuelle->parentPhrase;
                        }
                    }
                    break;
                }
                
                case SINON: {
                    printf("got here\n");
                    if (phraseActuelle->parentPhrase->interpreterInnerIndex != 0){
                        phrase_t* previous_phrase = phraseActuelle->parentPhrase->innerPhrase[phraseActuelle->parentPhrase->interpreterInnerIndex-1];
                        if (previous_phrase->phraseId == SI_ALORS){
                            if (!get_bool(previous_phrase->args[0]->valeur)){
                                if (phraseActuelle->interpreterInnerIndex < phraseActuelle->innerPhraseLen) {
                                    phraseActuelle->interpreterInnerIndex++;
                                    phraseActuelle = phraseActuelle->innerPhrase[phraseActuelle->interpreterInnerIndex - 1];
                                } else {
                                    phraseActuelle = phraseActuelle->parentPhrase;
                                }
                            }else{
                                phraseActuelle = phraseActuelle->parentPhrase;
                            }
                        }else{
                            custom_error("Syntax Error: Sinon déclaré sans Si", phraseActuelle);
                        }
                    }else{
                        custom_error("Syntax Error: Sinon déclaré sans Si", phraseActuelle);
                    }
                        
                    
                }
                

                default:
                    //printf("erreur: %d\n", phraseActuelle->phraseId);
                    //printf("%s\n", phraseActuelle->text);
                    phraseActuelle = phraseActuelle->parentPhrase;
                    //return;
                    break;
            }
        }
    }
}
