#include "phrase.h"

#include "constants.h"
#include "custom_error.h"
#include "function.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "variable.h"

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

    phrase->function = NULL;
    phrase->variable = NULL;
    phrase->liste_call = NULL;

    phrase->error = false;

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

    if (phrase->function != NULL) {
        free_function_t(phrase->function);
    }
    if (phrase->variable != NULL) {
        free_variable_t(phrase->variable);
    }
    if (phrase->liste_call != NULL) {
        free(phrase->liste_call);
    }

    if (phrase->expr){
        free(phrase->valeur);
    }
    
    free(phrase);
}

// double la taille du tableau de pointeurs vers les innerPhrase
void doubleInnerSize(phrase_t* phrase) {
    phrase->innerPhrase = realloc(phrase->innerPhrase, phrase->innerPhraseSize * 2 * sizeof(phrase_t*));
    if (phrase->innerPhrase == NULL) {
        custom_error("manque de mémoire pour innerPhrase", false);
    }
    phrase->innerPhraseSize *= 2;
}

void doubleTextSize(phrase_t* phrase) {
    phrase->text = realloc(phrase->text, phrase->textSize * 2 * sizeof(char));
    if (phrase->text == NULL) {
        custom_error("manque de mémoire pour text", false);
    }
    phrase->textSize *= 2;
}

void doubleArgsSize(phrase_t* phrase) {
    phrase->args = realloc(phrase->args, phrase->argsSize * 2 * sizeof(phrase_t*));
    if (phrase->args == NULL) {
        custom_error("manque de mémoire pour args", false);
    }
    phrase->argsSize *= 2;
}

void addToArg(phrase_t* phrase, phrase_t* elem) {
    if (phrase->argsLen >= phrase->argsSize) {
        doubleArgsSize(phrase);
    }
    phrase->args[phrase->argsLen] = elem;
    phrase->argsLen++;
}

void addToInner(phrase_t* phrase, phrase_t* elem) {
    if (phrase->innerPhraseLen >= phrase->innerPhraseSize) {
        doubleInnerSize(phrase);
    }
    phrase->innerPhrase[phrase->innerPhraseLen] = elem;
    phrase->innerPhraseLen++;
}

void addToText(phrase_t* phrase, char c) {
    if (phrase->textLen >= phrase->textSize) {
        doubleTextSize(phrase);
    }
    phrase->text[phrase->textLen] = c;
    phrase->textLen++;
}

void _printPhrase(phrase_t* phrase, int decalage, int last_elem) {
    if (phrase == NULL){
        return;
    }
    if (phrase->inst){
        for (int i = 0; i < decalage; i++) {
            printf("|\t");
        }
        printf("\n");
    }
    for (int i = 0; i < decalage - last_elem; i++) {
        printf("|\t");
    }
    for (int i = 0; i < last_elem && i < decalage; i++) {
        if (last_elem && phrase->innerPhraseLen == 0 && phrase->argsLen == 0) {
            printf("\\\t");
        } else {
            printf("|\t");
        }
    }
    printf("%s", phrase->text);
    if (phrase->expr && phrase->valeur->type != -1){
        switch (phrase->valeur->type) {
            case INT:
                printf("  ->  %d", get_int(phrase->valeur));
                break;
            case FLOAT:
                printf("  ->  %f", get_float(phrase->valeur));
                break;
            case BOOL:
                if (get_bool(phrase->valeur)){
                    printf("  ->  true");
                }else{
                    printf("  ->  false");
                }

                break;
            default:
                break;
        }
    }
    if (phrase->error){
        printf("\t\t\t <= ERROR HERE\n");
    } else {
        printf("\n");
    }

    if (phrase->argsLen > 0) {
        for (int i = 0; i < decalage; i++) {
            printf("|\t");
        }

        printf("args:\n");
        for (int i = 0; i < phrase->argsLen - 1; i++) {
            _printPhrase(phrase->args[i], decalage + 1, 0);
        }
        _printPhrase(phrase->args[phrase->argsLen - 1], decalage + 1, last_elem + 1);
    }

    if (phrase->innerPhraseLen > 0) {
        for (int i = 0; i < decalage; i++) {
            printf("|\t");
        }

        printf("inner :\n");
        for (int i = 0; i < phrase->innerPhraseLen - 1; i++) {
            _printPhrase(phrase->innerPhrase[i], decalage + 1, 0);
        }
        _printPhrase(phrase->innerPhrase[phrase->innerPhraseLen - 1], decalage + 1, last_elem + 1);
    }
}

void printPhrase(phrase_t* phrase) {
    for (int i = 0; i < phrase->innerPhraseLen; i++) {
        _printPhrase(phrase->innerPhrase[i], 0, false);
    }
}

void phraseCopy(phrase_t* p1, phrase_t* p2) {
    p2->text = realloc(p2->text, p1->textSize * sizeof(char));
    strcpy(p2->text, p1->text);
    p2->textSize = p1->textSize;
    p2->textLen = p1->textLen;

    for (int i = 0; i < p1->argsLen; i++) {
        phrase_t* tmp = new_phrase(p2);
        phraseCopy(p1->args[i], tmp);
        addToArg(p2, tmp);
    }

    p2->argsSize = p1->argsSize;
    p2->argsLen = p1->argsLen;

    p2->phraseId = p1->phraseId;

    p2->inst = p1->inst;

    for (int i = 0; i < p1->innerPhraseLen; i++) {
        phrase_t* tmp = new_phrase(p2);
        phraseCopy(p1->innerPhrase[i], tmp);
        addToInner(p2, tmp);
    }

    p2->innerPhraseLen = p1->innerPhraseLen;
    p2->innerPhraseSize = p2->innerPhraseSize;

    p2->expr = p1->expr;
    p2->valeur = p1->valeur;
}
