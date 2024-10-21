#ifndef phrase_h
#define phrase_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../constants.h"
#include "environnement.h"
#include "function.h"
#include "val.h"
#include "variable.h"

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

    struct phrase* parentPhrase;
    struct phrase* suivant;
    struct phrase* suivantInner1;  // phrase à interpreter dans le cas du si
    struct phrase* suivantInner2;  // phrase à interpreter dans le cas du sinon

    int phraseId;  // identificateur de l'instruction ou de l'expression

    // informations relatives à une expression
    bool expr;
    int uniqueId;  // indice de la valeur dans l'environnement

    // informations relatives à une instruction
    struct phrase** innerPhrase;  // les instructions dans les if, for, while
    int innerPhraseLen;           // nombre taille de la liste
    int innerPhraseSize;          // nombre inst_t alloués en mémoire
    int innerSeparator;           // séparateur entre les instructions du si et du sinon

    // variables et fonction appelées dans la phrase actuelle (ne peut y en avoir qu'un par expression)
    function_t* function;
    int variableId;  // indice de la variable associée dans l'environnement

    bool constant_removed;
    bool constant;
    bool error;
    
    int line_number;
    
} phrase_t;

phrase_t* new_phrase(phrase_t* parent);
void free_phrase(phrase_t* phrase);

void doubleInnerSize(phrase_t* phrase);
void doubleTextSize(phrase_t* phrase);
void doubleArgsSize(phrase_t* phrase);

void addToArg(phrase_t* phrase, phrase_t* elem);
void addToInner(phrase_t* phrase, phrase_t* elem);
void addToText(phrase_t* phrase, char c);

void _printPhrase(phrase_t* phrase, int decalage, int last_elem, environnement_t* env);
void printPhrase(phrase_t* phrase, environnement_t* env);

phrase_t* copy_phrase(phrase_t* p2, phrase_t* parent, environnement_t* env);
phrase_t* parent_loop(phrase_t* phrase, environnement_t* env);
#endif
