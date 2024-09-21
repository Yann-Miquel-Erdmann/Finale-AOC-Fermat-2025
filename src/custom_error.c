#include "custom_error.h"

#include <stdio.h>
#include <stdlib.h>

bool ignore_errors = false;

void set_ignore(void){
    ignore_errors = true;
}

void custom_error(char* err_message, phrase_t* phrase, environnement_t* env) {
    if (ignore_errors){
        printf("\n\n========== ERROR ===========\n\n");
        printf("Une erreur est survenue avec le message suivant:\n%s\n\n", err_message);
    }else{
        fprintf(stderr, "\n\n========== ERROR ===========\n\n");
        fprintf(stderr, "Une erreur est survenue avec le message suivant:\n%s\n\n", err_message);
    }

    if (phrase != NULL) {
        phrase->error = true;
        while (phrase->parentPhrase != NULL) {
            phrase = phrase->parentPhrase;
        }
        if (ignore_errors){
            printf("Dans le code suivant: \n");
        }else{
            fprintf(stderr, "Dans le code suivant: \n");
        }
        printPhrase(phrase, env);
    }
    exit((int)!ignore_errors);
}
