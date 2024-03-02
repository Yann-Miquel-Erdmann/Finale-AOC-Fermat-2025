#include "parser.h"

#include "constants.h"
#include "stdlib.h"
#include "val.h"

// renvoie vrai si c est majuscule
bool is_uppercase(char c) {
    if (c < 91 && c > 64) {
        return true;
    }
    return false;
}

phrase_t* parse_file(FILE* f) {
    phrase_t* mainPhrase = new_phrase(NULL);

    phrase_t* phraseActuelle = mainPhrase;

    char c = '\0';
    while (fscanf(f, "%c", &c) != EOF) {
        if (is_uppercase(c)) {
            addToText(phraseActuelle, '*');
            addToArg(phraseActuelle, new_phrase(phraseActuelle));

            phraseActuelle = phraseActuelle->args[phraseActuelle->argsLen - 1];
            addToText(phraseActuelle, c);

        } else {
            switch (c) {
                case '.':

                    addToText(phraseActuelle, c);
                    addToText(phraseActuelle, '\0');
                    phraseActuelle->inst = true;

                    phraseActuelle = phraseActuelle->parentPhrase;

                    // la phrase est une instruction et on l'ajoute
                    addToInner(phraseActuelle, phraseActuelle->args[phraseActuelle->argsLen - 1]);

                    phraseActuelle->args[phraseActuelle->argsLen - 1] = NULL;
                    phraseActuelle->argsLen--;

                    break;

                case '?':

                    // ajoute le caractère au texte
                    addToText(phraseActuelle, c);
                    addToText(phraseActuelle, '\0');
                    phraseActuelle->expr = true;

                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;

                default:
                    // ignore les sauts de lignes et les tabulations
                    if (c == '\n' || c == '\t') {
                        break;
                    }

                // n'ajoute pas les espaces en debut de ligne ou après un espace
                if (c == ' ' && (phraseActuelle->textLen == 0 || phraseActuelle->text[phraseActuelle->textLen - 1] == ' ')) {
                    break;
                }

                // ajoute le caractère au texte
                addToText(phraseActuelle, c);
            }
        }
    }
    return mainPhrase;
}