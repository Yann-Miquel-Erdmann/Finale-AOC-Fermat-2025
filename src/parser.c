#include "parser.h"

#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "custom_error.h"
#include "structures/val.h"
#include "syntax_convert.h"
#include "safe_alloc.h"

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
    bool encountered_uppercase = false;
    
    char buffer = '.';
    int line = 1;
    
    bool in_string = false;
    int in_comment = 0;
    char c = '\0';
    char prec_c = '\0';
    bool escape = false;
    while (fscanf(f, "%c", &c) != EOF) {
        if (in_string) {
            if (c == '"' && !escape) {
                in_string = !in_string;
            }
            if (c == '\\' && !escape){
                escape = true;
                continue;
            }
            if (escape){
                switch (c) {
                    case 'n':
                        addToText(phraseActuelle, '\n');
                        break;
                    case 't':
                        for (int i = 0; i< 4; i++){
                            addToText(phraseActuelle, ' ');
                        }
                        break;
                    case '"':
                        addToText(phraseActuelle, '\\');
                        addToText(phraseActuelle, '"');
                        break;
                    case '\\':
                        addToText(phraseActuelle,  '\\');
                        break;
                    default:{
                        char* errorphrase = safe_alloc(NULL, 100*sizeof(char));
                        sprintf(errorphrase, "\\%c n'est pas un caractère valide", c);
                        custom_error(errorphrase, phraseActuelle, NULL);
                        break;
                    }
                }
            }
            // ajoute le caractère au texte
            if (escape){
                escape = false;
            }else{
                addToText(phraseActuelle, c);
            }
        } else if (in_comment) {
            if (c == '\n'){
                line++;
            }
            if (c == ')') {
                in_comment -= 1;
            }
            if (c == '(') {
                in_comment += 1;
            }
        } else if (is_uppercase(c)) {
            encountered_uppercase = true;
            if (phraseActuelle->textLen > 0 && phraseActuelle->text[phraseActuelle->textLen - 1] != '*') {
                addToText(phraseActuelle, '*');
            }
            phrase_t* n = new_phrase(phraseActuelle);
            n->line_number = line;
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
            // check si l'écriture est valide i.e. pas directement dans la mainPhrase
            if (!encountered_uppercase && c != '(' && c != '\n'){
                char* error = safe_alloc(NULL, 100 * sizeof(char));
                sprintf(error, "Erreur de syntaxe ligne %d: \"%c\"%s", line, c, " n'est pas un début de phrase valide.");
                custom_error(error, NULL, NULL);
            }
            switch (c) {
                case '.':
                    if (buffer == ' ') {  // pour enlever les espaces avant les points (éviter quelques erreurs difficiles à trouver)
                        phraseActuelle->text[phraseActuelle->textLen - 1] = c;
                    } else {
                        addToText(phraseActuelle, c);
                    }
                    addToText(phraseActuelle, '\0');
                    phraseActuelle->expr = false;
                    
                    Inst1->suivant = Prec;
                    
                    phraseActuelle = phraseActuelle->parentPhrase;
                    
                    if (phraseActuelle == NULL) {
                        char* err_mess = safe_alloc(NULL, 100 * sizeof(char));
                        sprintf(err_mess, "Erreur de syntaxe: Il y a un point de trop à la ligne %d", line + 1);
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
                    }
                    //                    else if (c == '\n' && !in_comment) {
                    //                        char* err_mess = safe_alloc(NULL, 100 * sizeof(char));
                    //                        sprintf(err_mess, "Syntax Error: Il manque un point à la fin de la ligne %d", line);
                    //                        custom_error(err_mess, NULL, NULL);
                    //                        break;
                    //                    }
                    
                    // n'ajoute pas les espaces en debut de ligne ou après un espace
                    if (c == ' ' && (phraseActuelle->textLen == 0 || phraseActuelle->text[phraseActuelle->textLen - 1] == ' ')) {
                        break;
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
        char* error = safe_alloc(NULL, (64+strlen(phraseActuelle->text)) * sizeof(char));
        sprintf(error, "Erreur de syntaxe à la ligne %d : \"%s\" \nIl manque un point à la fin de la ligne.", phraseActuelle->line_number, phraseActuelle->text);
        
        custom_error(error, NULL, NULL);
    }
    
    Inst2->suivant = NULL;
    
    addToText(mainPhrase, '\0');
    
    /*phrase_t* p = mainPhrase;
    while (p != NULL){
        printf("%s ->\n", p->text);
        p = p->suivant;
    }
    printf("================\n\n");*/
    
    return mainPhrase;
}
