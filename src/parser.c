#include "parser.h"

#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "custom_error.h"
#include "structures/val.h"
#include "syntax_convert.h"

// renvoie vrai si c est majuscule
bool is_uppercase(char c) {
    if (c < 91 && c > 64) {
        return true;
    }
    return false;
}

phrase_t* parse_file(FILE* f) {
    phrase_t* mainPhrase = new_phrase(NULL);
    addToText(mainPhrase, '*');
    addToText(mainPhrase, '\0');

    phrase_t* phraseActuelle = mainPhrase;
    phrase_t* Prec = NULL;
    phrase_t* Inst1 = NULL;
    phrase_t* Inst2 = phraseActuelle;

    char buffer = '.';
    int line = 0;

    bool in_string = false;
    int in_comment = 0;
    char c = '\0';
    char prec_c;
    while (fscanf(f, "%c", &c) != EOF) {
        if (in_string) {
            if (c == '"') {
                in_string = !in_string;
            }
            // ajoute le caractère au texte
            addToText(phraseActuelle, c);
        } else if (in_comment) {
            if (c == ')') {
                in_comment -= 1;
            }
            if (c == '(') {
                in_comment += 1;
            }
        } else if (is_uppercase(c)) {
            if (phraseActuelle->textLen > 0 && phraseActuelle->text[phraseActuelle->textLen - 1] != '*') {
                addToText(phraseActuelle, '*');
            }
            phrase_t* n = new_phrase(phraseActuelle);
            addToArg(phraseActuelle, n);

            n->suivant = Prec;
            if (buffer == '.' || buffer == ':') {
                Inst1 = Inst2;
                Inst2 = n;
                // printf("switch  char: '%c' inst1:%s\n",c, Inst1->text);
            }
            Prec = n;

            phraseActuelle = phraseActuelle->args[phraseActuelle->argsLen - 1];
            addToText(phraseActuelle, c);

        } else {
            switch (c) {
                case '.':
                    if (buffer == ' ') {  // pour enlever les espaces avant les points (éviter quelques erreurs difficiles à trouver)
                        phraseActuelle->text[phraseActuelle->textLen - 1] = c;
                    } else {
                        addToText(phraseActuelle, c);
                    }
                    addToText(phraseActuelle, '\0');
                    phraseActuelle->inst = true;
                    phraseActuelle->expr = false;

                    Inst1->suivant = Prec;

                    phraseActuelle = phraseActuelle->parentPhrase;

                    if (phraseActuelle == NULL) {
                        char* err_mess = malloc(100 * sizeof(char));
                        sprintf(err_mess, "Syntax Error: Il y a un point de trop à la ligne %d", line + 1);
                        custom_error(err_mess, NULL, NULL);
                    }

                    // la phrase est une instruction et on l'ajoute
                    addToInner(phraseActuelle, phraseActuelle->args[phraseActuelle->argsLen - 1]);

                    phraseActuelle->args[phraseActuelle->argsLen - 1] = NULL;
                    phraseActuelle->argsLen--;

                    buffer = c;
                    break;

                case '?':

                    // ajoute le caractère au texte
                    if (buffer == ' ') {  // pour enlever les espaces avant les points d’interrogation (éviter quelques erreurs difficiles à trouver)
                        phraseActuelle->text[phraseActuelle->textLen - 1] = c;
                    } else {
                        addToText(phraseActuelle, c);
                    }
                    addToText(phraseActuelle, '\0');
                    phraseActuelle->expr = true;
                    phraseActuelle->inst = false;

                    phraseActuelle = phraseActuelle->parentPhrase;
                    buffer = c;
                    break;
                case ':':
                    // ajoute le caractère au texte
                    if (buffer == ' ') {
                        phraseActuelle->text[phraseActuelle->textLen - 1] = c;
                    } else {
                        addToText(phraseActuelle, c);
                    }
                    buffer = c;

                    // printf("inst1->suivant  '%s'  -->  ", Inst1->text);
                    // fflush(stdout);
                    // printf("'%s'\n", Prec->text);

                    Inst1->suivant = Prec;

                    phraseActuelle->innerSeparator = phraseActuelle->innerPhraseLen - 1;
                    break;
                default:
                    if (c == '"' && !in_comment) {
                        in_string = !in_string;
                    }
                    if (c == '(' && !in_string) {
                        in_comment += 1;
                        break;
                    }
                    if (c == '\n') {
                        line++;
                    }
                    // n'ajoute pas la virgule et l'espace entre les différents arguments
                    if ((c == ',' && phraseActuelle->text[phraseActuelle->textLen - 1] == '*') || (c == ' ' && buffer == ',')) {
                        buffer = c;
                        break;
                    }
                    // enlève les espaces avants les virgules
                    if (c == ',' && buffer == ' ') {
                        phraseActuelle->text[phraseActuelle->textLen - 1] = c;
                        buffer = c;
                        break;
                    }
                    // enlève les espaces après les points
                    if (c == ' ' && (buffer == '.' || buffer == ':')) {
                        break;
                    }

                    if (c == '\t') {
                        break;
                    }

                    // ignore les sauts de lignes et les tabulations
                    if ((c == '\n' && (buffer == '.' || buffer == ':' || prec_c == ')' || in_comment))) {
                        break;
                    } else if (c == '\n' && !in_comment) {
                        char* err_mess = malloc(100 * sizeof(char));
                        sprintf(err_mess, "Syntax Error: Il manque un point à la fin de la ligne %d", line);
                        custom_error(err_mess, NULL, NULL);
                        break;
                    }

                    // n'ajoute pas les espaces en debut de ligne ou après un espace
                    if (c == ' ' && (phraseActuelle->textLen == 0 || phraseActuelle->text[phraseActuelle->textLen - 1] == ' ')) {
                        break;
                    }

                    // check si l'écriture est valide i.e. pas directement dans la mainPhrase
                    if (phraseActuelle == mainPhrase && !in_comment) {
                        char* error = malloc(100 * sizeof(char));
                        sprintf(error, "Syntax Error, ligne %d: \"%c\"%s", line, c, " n'est pas un début de phrase valide.");
                        custom_error(error, NULL, NULL);
                    }

                    // ajoute le caractère au texte
                    addToText(phraseActuelle, c);
                    buffer = c;

                    break;
            }
        }
        prec_c = c;
    }
    if (in_comment) {
        custom_error("Une parenthèse n'a pas été fermée", NULL, NULL);
    }
    if (mainPhrase != phraseActuelle) {
        // probablement à changer + essayer de trouver où est-ce qu'il manque un point
        char* err_mess = malloc((strlen(phraseActuelle->text) * 2 + 31) * sizeof(char));
        strcat(err_mess, "Syntax error on instruction: \"");
        strcat(err_mess, phraseActuelle->text);
        strcat(err_mess, "\"\n\t* \tMissing point here :  ");
        for (int i = 0; i < (int)strlen(phraseActuelle->text); i++) {
            strcat(err_mess, "~");
        }
        strcat(err_mess, "^");
        custom_error(err_mess, NULL, NULL);
    }

    Inst2->suivant = NULL;

    addToText(mainPhrase, '\0');
    return mainPhrase;
}
