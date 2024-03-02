#include "phrase.h"

#include "constants.h"
#include "stdio.h"
#include "stdlib.h"
#include "values.h"

phrase_t* new_phrase(phrase_t* parent) {
    phrase_t* phrase = malloc(sizeof(phrase_t));

    phrase->text = malloc(DEFAULT_PHRASE_TEXT_LEN * sizeof(char));
    phrase->textLen = 0;
    phrase->textSize = DEFAULT_PHRASE_TEXT_LEN;
    phrase->text[0] = '\0';

    phrase->args = malloc(DEFAULT_PHRASE_ARGS * sizeof(phrase_t*));
    phrase->argsLen = 0;
    phrase->argsSize = DEFAULT_PHRASE_ARGS;

    phrase->parentPhrase = parent;

    phrase->innerPhrase = malloc(DEFAULT_PHRASE_INNER * sizeof(phrase_t*));
    phrase->innerPhraseLen = 0;
    phrase->innerPhraseSize = DEFAULT_PHRASE_INNER;

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
void doubleInnerSize(phrase_t* phrase) {
    phrase->innerPhrase = realloc(phrase->innerPhrase, phrase->innerPhraseSize * 2);
    if (phrase->innerPhrase == NULL) {
        fprintf(stderr, "manque de mémoire pour innerPhrase\n");
        exit(1);
    }
    phrase->innerPhraseSize *= 2;
}

void doubleTextSize(phrase_t* phrase) {
    phrase->text = realloc(phrase->text, phrase->textSize * 2);
    if (phrase->text == NULL) {
        fprintf(stderr, "manque de mémoire pour text\n");
        exit(1);
    }
    phrase->textSize *= 2;
}

void doubleArgsSize(phrase_t* phrase) {
    phrase->args = realloc(phrase->args, phrase->argsSize * 2);
    if (phrase->args == NULL) {
        fprintf(stderr, "manque de mémoire pour args\n");
        exit(1);
    }
    phrase->argsSize *= 2;
}

void addToArg(phrase_t* phrase, phrase_t* elem) {
    if (phrase->argsLen == phrase->argsSize) {
        doubleArgsSize(phrase);
    }
    phrase->args[phrase->argsLen] = elem;
    phrase->argsLen++;
}

void addToInner(phrase_t* phrase, phrase_t* elem) {
    if (phrase->innerPhraseLen == phrase->innerPhraseSize) {
        doubleInnerSize(phrase);
    }
    phrase->innerPhrase[phrase->innerPhraseLen] = elem;
    phrase->innerPhraseLen++;
}

void addToText(phrase_t* phrase, char c) {
    if (phrase->textLen == phrase->textSize) {
        doubleInnerSize(phrase);
    }
    phrase->text[phrase->textLen] = c;
    phrase->textLen++;
}

void _printPhrase(phrase_t* phrase, int decalage) {
    for (int i = 0; i < decalage; i++) {
        printf("|\t");
    }
    printf("%s\n", phrase->text);

    if (phrase->argsLen > 0) {
        for (int i = 0; i < decalage; i++) {
            printf("|\t");
        }

        printf("args:\n");
        for (int i = 0; i < phrase->argsLen; i++) {
            _printPhrase(phrase->args[i], decalage + 1);
        }
    }

    if (phrase->innerPhraseLen > 0) {
        for (int i = 0; i < decalage; i++) {
            printf("|\t");
        }

        printf("inner :\n");
        for (int i = 0; i < phrase->innerPhraseLen; i++) {
            _printPhrase(phrase->innerPhrase[i], decalage + 1);
        }
    }
}

void printPhrase(phrase_t* phrase) {
    for (int i = 0; i < phrase->innerPhraseLen; i++) {
        _printPhrase(phrase->innerPhrase[i], 0);
    }
}