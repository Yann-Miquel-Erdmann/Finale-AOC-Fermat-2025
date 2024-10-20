#include "remove_constants.h"
#include "safe_alloc.h"


void removeConstants(phrase_t* phrase) {
    phrase_t** phrasesWithInner = safe_alloc(NULL, sizeof(phrase_t*) * DEFAULT_PHRASE_INNER);
    int phrasesWithInnerLen = 0;
    int phrasesWithInnerSize = DEFAULT_PHRASE_INNER;
    phrase_t* phraseActuelle = phrase;

    // printf("remove constants %s %d\n", phrase->text, phrase->innerPhraseLen);

    // if (phraseActuelle->constant_removed) {
    //     return;
    // }

    while (phraseActuelle != NULL) {
        // printf("phrase actuelle %s\n", phraseActuelle->text);
        if (phraseActuelle->innerPhraseLen > 0) {
            // printf("inner phrase %d\n", phraseActuelle->innerPhraseLen);
            if (phrasesWithInnerLen == phrasesWithInnerSize) {
                phrasesWithInnerSize *= 2;
                phrasesWithInner = safe_alloc(phrasesWithInner, sizeof(phrase_t*) * phrasesWithInnerSize);
            }
            phrasesWithInner[phrasesWithInnerLen] = phraseActuelle;
            phrasesWithInnerLen++;
        }


        if (phraseActuelle->suivant == NULL) {
            break;
        }

        if (phraseActuelle->phraseId == QUITTER_BOUCLE) {
            break;
        }

        if (phraseActuelle->suivant->constant_removed) {
            // quitte si le suivant a déjà été vu
            break;
        }

        if (phraseActuelle->suivant->constant || phraseActuelle->suivant->phraseId == DEFINITION_FONCTION || phraseActuelle->suivant->phraseId == DEFINITION_FONCTION_ARGUMENT) {
            phraseActuelle->suivant = phraseActuelle->suivant->suivant;
        }

        // printf("%s -> %s\n", phraseActuelle->text, phraseActuelle->suivant->text);
        if (phraseActuelle->suivant != NULL && !phraseActuelle->suivant->constant && !phraseActuelle->suivant->constant_removed) {
            phraseActuelle->constant_removed = true;
            phraseActuelle = phraseActuelle->suivant;
        }

    }
    phraseActuelle->constant_removed = true;

    // printf("phrases with inner len: %d\n", phrasesWithInnerLen);
    // if (phrasesWithInnerLen > 0) {
    //     if (phrasesWithInner[0]->text[0] != '*') {
    //         printf("'%s'\n",phrasesWithInner[0]->text);
    //         exit(1);
    //     } else {
    //         printf("'%s'\n",phrasesWithInner[0]->text);
    //     }
    // }
    int i = 0;
    while (i < phrasesWithInnerLen) {
        while (phrasesWithInner[i]->suivantInner1 != NULL && !phrasesWithInner[i]->suivantInner1->constant_removed && (phrasesWithInner[i]->suivantInner1->constant || phrasesWithInner[i]->suivantInner1->phraseId == DEFINITION_FONCTION || phrasesWithInner[i]->suivantInner1->phraseId == DEFINITION_FONCTION_ARGUMENT)) {
            if (phrasesWithInner[i]->suivantInner1->phraseId == DEFINITION_FONCTION || phrasesWithInner[i]->suivantInner1->phraseId == DEFINITION_FONCTION_ARGUMENT) {
                if (phrasesWithInnerLen == phrasesWithInnerSize) {
                    phrasesWithInnerSize *= 2;
                    phrasesWithInner = safe_alloc(phrasesWithInner, sizeof(phrase_t*) * phrasesWithInnerSize);
                }
                phrasesWithInner[phrasesWithInnerLen] = phrasesWithInner[i]->suivantInner1;
                phrasesWithInnerLen++;
            }

            phrasesWithInner[i]->suivantInner1 = phrasesWithInner[i]->suivantInner1->suivant;
        }

        if (phrasesWithInner[i]->suivantInner1->constant_removed) {
            i++;
            continue;
        }

        // printf("inner1 '%s' -> '%s'\n", phrasesWithInner[i]->text, phrasesWithInner[i]->suivantInner1->text );
        if (phrasesWithInner[i]->phraseId == SI_ALORS || phrasesWithInner[i]->phraseId == SI_ALORS_SINON) {
            // printf("stop %s\n", phrasesWithInner[i]->suivant->text);
            removeConstants(phrasesWithInner[i]->suivantInner1);
        } else {
            removeConstants(phrasesWithInner[i]->suivantInner1);
            // printf("end of inner %s\n", phrasesWithInner[i]->text);
        }

        if (phrasesWithInner[i]->phraseId == SI_ALORS_SINON) {

            while (phrasesWithInner[i]->suivantInner2 != NULL && !phrasesWithInner[i]->suivantInner2->constant_removed && phrasesWithInner[i]->suivantInner2->constant) {
                if (phrasesWithInner[i]->suivantInner2->phraseId == DEFINITION_FONCTION || phrasesWithInner[i]->suivantInner2->phraseId == DEFINITION_FONCTION_ARGUMENT) {
                    if (phrasesWithInnerLen == phrasesWithInnerSize) {
                        phrasesWithInnerSize *= 2;
                        phrasesWithInner = safe_alloc(phrasesWithInner, sizeof(phrase_t*) * phrasesWithInnerSize);
                    }
                    phrasesWithInner[phrasesWithInnerLen] = phrasesWithInner[i]->suivantInner2;
                    phrasesWithInnerLen++;
                }

                // printf("const %s %s\n", phrasesWithInner[i]->text, phrasesWithInner[i]->suivantInner2->text);
                phrasesWithInner[i]->suivantInner2 = phrasesWithInner[i]->suivantInner2->suivant;
            }
            
            if (phrasesWithInner[i]->suivantInner2->constant_removed) {
                i++;
                continue;
            }

            // printf("inner2 '%s' -> '%s'\n", phrasesWithInner[i]->text, phrasesWithInner[i]->suivantInner2->text);
            removeConstants(phrasesWithInner[i]->suivantInner2);

            // exit(1);
        }

        i++;
    }

    free(phrasesWithInner);
}