#include "constants.h"
#include "values.h"
#include "phrase.h"
#include "stdlib.h"
#include "stdio.h"

phrase_t* new_phrase(phrase_t * parent) {
    phrase_t* phrase = malloc(sizeof(phrase_t));

    phrase->text = malloc(MAX_PHRASE_TEXT_LEN * sizeof(char));
    phrase->textLen = 0;
    phrase->text[0] = '\0';

    phrase->args = malloc(MAX_PHRASE_ARGS * sizeof(phrase_t*));
    phrase->argsLen = 0;

    phrase->parentPhrase = parent;

    phrase->innerPhrase = malloc(DEFAULT_PHRASE_INNER * sizeof(phrase_t*));
    phrase->innerPhraseLen = 0;
    phrase->innerPhraseLen = DEFAULT_PHRASE_INNER;

    phrase->phraseId = -1;

    phrase->inst = false;
    phrase->expr = false;

    return phrase;
}


void free_phrase(phrase_t* phrase) {
    free(phrase->text);

    for (int i = 0; i < phrase->argsLen; i++) {
        free_phrase(phrase->args[i]);
    }
    free(phrase->args);

    for (int i = 0; i < phrase->innerPhraseLen; i++) {
        free_phrase(phrase->innerPhrase[i]);
    }
    free(phrase->innerPhrase);

    free(phrase);
}

// double la taille du tableau de pointeurs vers les innerPhrase
void doubleInnerSize(phrase_t* phrase){
    phrase->innerPhrase = realloc(phrase->innerPhrase, phrase->innerPhraseSize*2);
    if (phrase->innerPhrase == NULL){
        fprintf(stderr, "manque de mémoire pour innerPhrase\n");
        exit(1);
    }
    phrase->innerPhraseSize*=2;
}

void _printPhrase(phrase_t* phrase, int decalage){
    for (int i = 0; i< decalage; i++){
        printf("|\t");
    }
    
}

void printPhrase(phrase_t* phrase){
    _printPhrase(phrase, 0);
}