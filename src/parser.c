#include "parser.h"

#include "constants.h"
#include "stdlib.h"
#include "val.h"
#include "custom_error.h"
#include "string.h"
#include "syntax_convert.h"

char* add_number_str(char* str, int n){
    char* final = malloc((strlen(str)+log_10_entier(n)+1)*sizeof(char));
    strcpy(final, str);
    char* num = malloc((log_10_entier(n)+1)*sizeof(char));
    int index = log_10_entier(n)-1;
    while (n > 0){
        num[index] = (n%10)+48;
        n /= 10;
        index --;
    }
    strcat(final, num);
    free(num);
    return final;
}

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
    char buffer = '\0';
    int missing_point = -1;
    int line = 0;
    
    char c = '\0';
    while (fscanf(f, "%c", &c) != EOF) {
        if (is_uppercase(c)) {
            if (phraseActuelle->textLen > 0 && phraseActuelle->text[phraseActuelle->textLen-1] != '*'){
                addToText(phraseActuelle, '*');
            }
            addToArg(phraseActuelle, new_phrase(phraseActuelle));

            phraseActuelle = phraseActuelle->args[phraseActuelle->argsLen - 1];
            addToText(phraseActuelle, c);

        } else {
            switch (c) {
                case '.':

                    addToText(phraseActuelle, c);
                    addToText(phraseActuelle, '\0');
                    phraseActuelle->inst = true;
                    phraseActuelle->expr = false;

                    phraseActuelle = phraseActuelle->parentPhrase;
                    
                    if (phraseActuelle == NULL){
                        custom_error(add_number_str("Il y a un point de trop à la ligne ", line+1), NULL);
                    }

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
                    phraseActuelle->inst = false;
                    
                    
                    phraseActuelle->valeur = new_val();
                    set_undefined(phraseActuelle->valeur);
                    
                    
                    phraseActuelle = phraseActuelle->parentPhrase;
                    break;

                default:
                    if (c == '\n'){
                        line++;
                    }
                    // n'ajoute pas la virgule et l'espace entre les différents arguments
                    if ((c == ',' && phraseActuelle->text[phraseActuelle->textLen-1] == '*') || (c == ' ' && buffer == ',')){
                        break;
                    }
                    // ignore les sauts de lignes et les tabulations
                    if ((c == '\n' && (buffer == '.' || buffer == ':')) || c == '\t') {
                        break;
                    }else if (c == '\n'){
                        // erreur manque de point en fin de ligne
                        
                        custom_error(add_number_str("Il manque un point à la fin de la ligne ", line), NULL);
                        missing_point = 1;
                        break;
                    }
                    
                    

                    // n'ajoute pas les espaces en debut de ligne ou après un espace
                    if (c == ' ' && (phraseActuelle->textLen == 0 || phraseActuelle->text[phraseActuelle->textLen - 1] == ' ')) {
                        break;
                    }

                    // ajoute le caractère au texte
                    addToText(phraseActuelle, c);
                    break;
            }
            if (missing_point != -1){
                break;
            }
        }
        if (c != '\n' || buffer == ':'){
            buffer = c;
        }
    }
    if (mainPhrase != phraseActuelle){
        // probablement à changer + essayer de trouver où est-ce qu'il manque un point
        char* err_mess = malloc((strlen(phraseActuelle->text)*2+31)*sizeof(char));
        strcat(err_mess, "Syntax error on instruction: \"");
        strcat(err_mess, phraseActuelle->text);
        strcat(err_mess, "\"\n\t* \tMissing point here :  ");
        for (int i = 0; i< (int) strlen(phraseActuelle->text); i++){
            strcat(err_mess, "~");
        }
        strcat(err_mess, "^");
        custom_error(err_mess, false);
    }
    addToText(mainPhrase, '\0');
    return mainPhrase;
}
