#include "phrase.h"

phrase_t* new_phrase(phrase_t* parent) {
    phrase_t* phrase = malloc(sizeof(phrase_t));

    phrase->text = malloc(DEFAULT_PHRASE_TEXT_SIZE * sizeof(char));
    phrase->textLen = 0;
    phrase->textSize = DEFAULT_PHRASE_TEXT_SIZE;
    phrase->text[0] = '\0';

    phrase->args = malloc(DEFAULT_PHRASE_ARGS * sizeof(phrase_t*));
    phrase->argsLen = 0;
    phrase->argsSize = DEFAULT_PHRASE_ARGS;
    phrase->interpreterArgsIndex = 0;

    phrase->parentPhrase = parent;

    phrase->innerPhrase = malloc(DEFAULT_PHRASE_INNER * sizeof(phrase_t*));
    phrase->innerPhraseLen = 0;
    phrase->innerPhraseSize = DEFAULT_PHRASE_INNER;
    phrase->interpreterInnerIndex = 0;

    phrase->phraseId = -1;

    phrase->inst = false;
    phrase->expr = false;

    phrase->function = NULL;
    phrase->variable = NULL;
    phrase->valeur = NULL;

    phrase->error = false;
    phrase->constant = false;

    return phrase;
}

void free_phrase(phrase_t* phrase) {
    if (phrase == NULL) {
        return;
    }

    if (phrase->text != NULL) {
        free(phrase->text);
    }

    for (int i = 0; i < phrase->argsLen; i++) {
        free_phrase(phrase->args[i]);
    }
    free(phrase->args);

    for (int i = 0; i < phrase->innerPhraseLen; i++) {
        free_phrase(phrase->innerPhrase[i]);
    }
    free(phrase->innerPhrase);

    if (phrase->valeur != NULL) {
        free_val_t(phrase->valeur);
    }

    free(phrase);
}

phrase_t* copy_phrase(phrase_t* phrase, phrase_t* parent, environnement_t* new_env) {
    phrase_t* new = new_phrase(parent);
    strcpy(new->text, phrase->text);
    new->textLen = phrase->textLen;
    new->textSize = phrase->textSize;
    new->argsLen = phrase->argsLen;
    new->argsSize = phrase->argsSize;

    new->phraseId = phrase->phraseId;

    for (int i = 0; i < phrase->argsLen; i++) {
        new->args[i] = copy_phrase(phrase->args[i], new, new_env);
    }

    new->innerPhraseLen = phrase->innerPhraseLen;
    new->innerPhraseSize = phrase->innerPhraseSize;
    for (int i = 0; i < phrase->innerPhraseLen; i++) {
        new->innerPhrase[i] = copy_phrase(phrase->innerPhrase[i], new, new_env);
    }

    new->inst = phrase->inst;
    new->expr = phrase->expr;
    new->constant = phrase->constant;

    if (phrase->function != NULL) {
        new->function = phrase->function;
    }
    if (phrase->variable != NULL) {
        new->variable = getVariable(new_env, phrase->variable->nom);
    }

    if (phrase->valeur != NULL) {
        new->valeur = malloc(sizeof(val_t));
        copy_val(new->valeur, phrase->valeur);
    }

    new->error = phrase->error;
    new->constant = phrase->constant;

    return new;
}

// double la taille du tableau de pointeurs vers les innerPhrase
void doubleInnerSize(phrase_t* phrase) {
    phrase->innerPhrase = realloc(phrase->innerPhrase, phrase->innerPhraseSize * 2 * sizeof(phrase_t*));
    if (phrase->innerPhrase == NULL) {
        custom_error("manque de mémoire pour phrase innerPhrase", NULL);
    }
    phrase->innerPhraseSize *= 2;
}

void doubleTextSize(phrase_t* phrase) {
    phrase->text = realloc(phrase->text, phrase->textSize * 2 * sizeof(char));
    if (phrase->text == NULL) {
        custom_error("manque de mémoire pour phrase text", NULL);
    }
    phrase->textSize *= 2;
}

void doubleArgsSize(phrase_t* phrase) {
    phrase->args = realloc(phrase->args, phrase->argsSize * 2 * sizeof(phrase_t*));
    if (phrase->args == NULL) {
        custom_error("manque de mémoire pour phrase args", NULL);
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
    if (phrase->inst) {
        for (int i = 0; i < decalage; i++) {
            // printf("|\t");
        }
        // printf("\n");
    }
    for (int i = 0; i < decalage - last_elem; i++) {
        // printf("|\t");
    }
    for (int i = 0; i < last_elem && i < decalage; i++) {
        if (last_elem && phrase->innerPhraseLen == 0 && phrase->argsLen == 0) {
            // printf("\\\t");
        } else {
            // printf("|\t");
        }
    }
    // printf("%s", phrase->text);
    if (phrase->expr && phrase->valeur->type != -1) {
        switch (phrase->valeur->type) {
            case INT:
                // printf("  ->  %d", get_int(phrase->valeur));
                break;
            case FLOAT:
                // printf("  ->  %f", get_float(phrase->valeur));
                break;
            case BOOL:
                if (get_bool(phrase->valeur)) {
                    // printf("  ->  true");
                } else {
                    // printf("  ->  false");
                }

                break;
            default:
                break;
        }
    }
    if (phrase->error) {
        // printf("\t\t\t <= ERROR HERE\n");
    } else {
        // printf("\n");
    }

    if (phrase->argsLen > 0) {
        for (int i = 0; i < decalage; i++) {
            // printf("|\t");
        }

        // printf("args:\n");
        for (int i = 0; i < phrase->argsLen - 1; i++) {
            _printPhrase(phrase->args[i], decalage + 1, 0);
        }
        _printPhrase(phrase->args[phrase->argsLen - 1], decalage + 1, last_elem + 1);
    }

    if (phrase->innerPhraseLen > 0) {
        for (int i = 0; i < decalage; i++) {
            // printf("|\t");
        }

        // printf("inner :\n");
        for (int i = 0; i < phrase->innerPhraseLen - 1; i++) {
            _printPhrase(phrase->innerPhrase[i], decalage + 1, 0);
        }
        _printPhrase(phrase->innerPhrase[phrase->innerPhraseLen - 1], decalage + 1, last_elem + 1);
    }
}

void printPhrase(phrase_t* phrase) {
    for (int i = 0; i < phrase->innerPhraseLen; i++) {
        // printf("print inner %s %d\n", phrase->text, i);
        _printPhrase(phrase->innerPhrase[i], 0, false);
    }
}
