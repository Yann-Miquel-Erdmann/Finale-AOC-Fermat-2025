#include "custom_error.h"

#include <stdio.h>
#include <stdlib.h>

bool ignore_errors = false;

void set_ignore(void){
    ignore_errors = true;
}

void custom_error(char* err_message, phrase_t* phrase, environnement_t* env) {
    int ligne = phrase->line_number;
    if (ignore_errors){
        printf("\n\n========== ERREUR ===========\n\n");
        printf("Une erreur est survenue avec le message suivant:\n%s\n\n", err_message);
    }else{
        fprintf(stderr, "\n\n========== ERREUR ===========\n\n");
        fprintf(stderr, "Une erreur est survenue avec le message suivant:\n%s\n\n", err_message);
    }

    if (phrase != NULL) {
        phrase->error = true;
        while (phrase->parentPhrase != NULL && phrase->text[phrase->textLen-1] != '.') {
            phrase = phrase->parentPhrase;
        }
        if (ignore_errors){
            printf("À la ligne %d: \n", ligne);
        }else{
            fprintf(stderr, "À la ligne %d: \n", ligne);
        }
        if (env != NULL){
            printPhrase(phrase, env);
        }else{
            printPhrase(phrase, NULL);
        }
    }
    exit((int)!ignore_errors);
}
