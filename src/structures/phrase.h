#ifndef phrase_h
#define phrase_h

#include <stdbool.h>

#include "val.h"
#include "environnement.h"
#include "function.h"
#include "variable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "../custom_error.h"

// def de la structure function pour le cross referencing
typedef struct function function_t;

// structure de l'instruction
typedef struct phrase {
    char* text;  // le texte de l'instruction ou de l'expression
    int textSize;
    int textLen;

    struct phrase** args;  // arguments de l'instruction: les expressions données en "paramètres"
    int argsSize;
    int argsLen;
    int interpreterArgsIndex;

    struct phrase* parentPhrase;

    int phraseId;  // identificateur de l'instruction ou de l'expression

    // informations relatives à une instruction
    bool inst;
    struct phrase** innerPhrase;  // les instructions dans les if, for, while
    int innerPhraseLen;           // nombre taille de la liste
    int innerPhraseSize;          // nombre inst_t alloués en mémoire
    int interpreterInnerIndex;
    int innerSeparator;  // séparateur entre les instructions du si et du sinon

    // informations relatives à une expression
    bool expr;
    val_t* valeur;  // valeur de retour de l'expression

    // variables et fonction appelées dans la phrase actuelle (ne peut y en avoir qu'un par expression)
    function_t* function;
    variable_t* variable;

    bool constant;
    bool error;
} phrase_t;

phrase_t* new_phrase(phrase_t* parent);
void free_phrase(phrase_t* phrase);

void doubleInnerSize(phrase_t* phrase);
void doubleTextSize(phrase_t* phrase);
void doubleArgsSize(phrase_t* phrase);

void addToArg(phrase_t* phrase, phrase_t* elem);
void addToInner(phrase_t* phrase, phrase_t* elem);
void addToText(phrase_t* phrase, char c);

void _printPhrase(phrase_t* phrase, int decalage, int last_elem);
void printPhrase(phrase_t* phrase);

phrase_t* copy_phrase(phrase_t* p2,phrase_t* parent,  environnement_t* env);
#endif
