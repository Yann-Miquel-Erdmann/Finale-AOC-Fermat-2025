#ifndef phrase_h
#define phrase_h


#include "stdbool.h"
#include "val.h"



// structure de l'instruction
typedef struct phrase {
    char* text; // le texte de l'instruction ou de l'expression
    int textSize;
    int textLen;

    struct phrase ** args;  // arguments de l'instruction: les expressions données en "paramètres"
    int argsSize;
    int argsLen;
    
    struct phrase * parentPhrase;
    
    int phraseId; // identificateur de l'instruction ou de l'expression

    // informations relatives à une instruction
    bool inst;
    struct phrase ** innerPhrase;  // les instructions dans les if, for, while
    int innerPhraseLen;    // nombre taille de la liste
    int innerPhraseSize;   // nombre inst_t alloués en mémoire


    // informations relatives à une expression
    bool expr;
    val_t* valeur; // valeur de retour de l'expression

} phrase_t;

phrase_t* new_phrase(phrase_t* parent);
void free_phrase(phrase_t* phrase);

void doubleInnerSize(phrase_t* phrase);
void doubleTextSize(phrase_t* phrase);
void doubleArgsSize(phrase_t* phrase);

void addToArg(phrase_t* phrase, phrase_t* elem);
void addToInner(phrase_t* phrase, phrase_t* elem);
void addToText(phrase_t* phrase, char c);

void _printPhrase(phrase_t* phrase, int decalage);
void printPhrase(phrase_t* phrase);
#endif