#include "interpreter.h"

#include "constants.h"
#include "custom_error.h"

void interpreter(function_t* function, function_list_t* functions, val_t* result, int layer) {
    if (layer > MAX_RECUSION_DEPTH) {
        custom_error("limite de récursion atteinte", NULL);
    }

    phrase_t* phraseActuelle = function->ast;

    while (phraseActuelle != NULL) {
        if (phraseActuelle->interpreterArgsIndex < phraseActuelle->argsLen) {
            phraseActuelle->interpreterArgsIndex++;
            phraseActuelle = phraseActuelle->args[phraseActuelle->interpreterArgsIndex - 1];
        } else {
            switch (phraseActuelle->phraseId) {
                case EXECUTION_FONCTION:
                    function_t* new_func = copy_function(phraseActuelle->function);
                    interpreter(new_func, functions, phraseActuelle->valeur, layer + 1);
                    free_function_t(new_func);
                    break;

                case RENVOI_FONCTION:
                    if (result != NULL && phraseActuelle->argsLen > 0) {
                        copy_val(result, phraseActuelle->args[0]->valeur);
                    }
                    return;
                    break;

                default:
                    break;
            }
        }
    }
}
