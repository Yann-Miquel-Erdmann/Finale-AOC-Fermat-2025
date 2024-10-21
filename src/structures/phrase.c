#include "phrase.h"

#include "../custom_error.h"
#include "../safe_alloc.h"

phrase_t* new_phrase(phrase_t* parent) {
    phrase_t* phrase = safe_alloc(NULL, sizeof(phrase_t));

    phrase->text = safe_alloc(NULL, DEFAULT_PHRASE_TEXT_SIZE * sizeof(char));
    phrase->textLen = 0;
    phrase->textSize = DEFAULT_PHRASE_TEXT_SIZE;
    phrase->text[0] = '\0';

    phrase->args = safe_alloc(NULL, DEFAULT_PHRASE_ARGS * sizeof(phrase_t*));
    phrase->argsLen = 0;
    phrase->argsSize = DEFAULT_PHRASE_ARGS;
    phrase->constant_removed = false;

    phrase->parentPhrase = parent;
    phrase->suivant = NULL;
    phrase->suivantInner1 = NULL;
    phrase->suivantInner2 = NULL;

    phrase->innerPhrase = safe_alloc(NULL, DEFAULT_PHRASE_INNER * sizeof(phrase_t*));
    phrase->innerPhraseLen = 0;
    phrase->innerPhraseSize = DEFAULT_PHRASE_INNER;
    phrase->innerSeparator = 0;

    phrase->phraseId = -1;
    phrase->uniqueId = -1;

    phrase->expr = false;

    phrase->function = NULL;
    phrase->variableId = -1;

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

    free(phrase);
}

phrase_t* copy_phrase(phrase_t* phrase, phrase_t* parent, environnement_t* new_env) {
    phrase_t* new = new_phrase(parent);
    strcpy(new->text, phrase->text);
    new->textLen = phrase->textLen;
    new->textSize = phrase->textSize;

    new->phraseId = phrase->phraseId;

    new->argsLen = phrase->argsLen;
    new->argsSize = phrase->argsSize;
    for (int i = 0; i < phrase->argsLen; i++) {
        new->args[i] = copy_phrase(phrase->args[i], new, new_env);
    }

    new->innerPhraseLen = phrase->innerPhraseLen;
    new->innerPhraseSize = phrase->innerPhraseSize;
    for (int i = 0; i < phrase->innerPhraseLen; i++) {
        new->innerPhrase[i] = copy_phrase(phrase->innerPhrase[i], new, new_env);
    }

    new->expr = phrase->expr;
    new->constant = phrase->constant;

    if (phrase->function != NULL) {
        new->function = phrase->function;
    }

    new->variableId = phrase->variableId;

    new->error = phrase->error;
    new->constant = phrase->constant;

    return new;
}

// double la taille du tableau de pointeurs vers les innerPhrase
void doubleInnerSize(phrase_t* phrase) {
    phrase->innerPhrase = safe_alloc(phrase->innerPhrase, phrase->innerPhraseSize * 2 * sizeof(phrase_t*));
    phrase->innerPhraseSize *= 2;
}

void doubleTextSize(phrase_t* phrase) {
    phrase->text = safe_alloc(phrase->text, phrase->textSize * 2 * sizeof(char));
    phrase->textSize *= 2;
}

void doubleArgsSize(phrase_t* phrase) {
    phrase->args = safe_alloc(phrase->args, phrase->argsSize * 2 * sizeof(phrase_t*));
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

void _printPhrase(phrase_t* phrase, int decalage, int last_elem, environnement_t* env) {
    // printf("%p : ", env->phraseValeurs[phrase->uniqueId]);
    if (!phrase->expr) {
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
    if (env != NULL){
        if (phrase->expr && phrase->uniqueId < env->phraseValeurs_len && phrase->uniqueId != -1 && env->phraseValeurs[phrase->uniqueId]->type != -1) {
            switch (env->phraseValeurs[phrase->uniqueId]->type) {
                case INT:
                    printf("  ->  %d", env->phraseValeurs[phrase->uniqueId]->value.entier);
                    break;
                case FLOAT:
                    printf("  ->  %f", env->phraseValeurs[phrase->uniqueId]->value.flottant);
                    break;
                case BOOL:
                    if (env->phraseValeurs[phrase->uniqueId]->value.booleen) {
                        printf("  ->  true");
                    } else {
                        printf("  ->  false");
                    }
                    
                    break;
                case CHAINE_DE_CHAR:
                case CHAINE_DE_CHAR_P:
                    if (env->phraseValeurs[phrase->uniqueId]->value.chaine != NULL){
                        printf("  ->  %s", env->phraseValeurs[phrase->uniqueId]->value.chaine->chars);
                    }
                default:
                    break;
            }
        }
    }
    if (phrase->error) {
        printf("\t\t\t <= ERREUR ICI\n");
    } else {
        printf("\n");
    }

    if (phrase->argsLen > 0) {
        for (int i = 0; i < decalage; i++) {
            printf("|\t");
        }

        printf("args:\n");
        for (int i = 0; i < phrase->argsLen - 1; i++) {
            _printPhrase(phrase->args[i], decalage + 1, 0, env);
        }
        _printPhrase(phrase->args[phrase->argsLen - 1], decalage + 1, last_elem + 1, env);
    }

    if (phrase->innerPhraseLen > 0) {
        for (int i = 0; i < decalage; i++) {
            printf("|\t");
        }

        printf("inner :\n");
        for (int i = 0; i < phrase->innerPhraseLen - 1; i++) {
            _printPhrase(phrase->innerPhrase[i], decalage + 1, 0, env);
        }
        _printPhrase(phrase->innerPhrase[phrase->innerPhraseLen - 1], decalage + 1, last_elem + 1, env);
    }
    fflush(stdout);
}

void printPhrase(phrase_t* phrase, environnement_t* env) {
    for (int i = 0; i < phrase->innerPhraseLen; i++) {
        // printf("print inner %s %d\n", phrase->text, i);
        _printPhrase(phrase->innerPhrase[i], 0, false, env);
    }
}

phrase_t* parent_loop(phrase_t* phrase, environnement_t* env) {
    phrase_t* p = phrase->parentPhrase;
    while (p->phraseId != TANT_QUE && p->phraseId != POUR_SANS_PAS && p->phraseId != POUR_AVEC_PAS) {
        if (p->parentPhrase == NULL) {
            custom_error("Syntaxe invalide, quitter boucle doit être dans une boucle", phrase, env);
        }
        p = p->parentPhrase;
    }
    return p;
}
