#include "syntax_convert.h"

#include <assert.h>

#include "custom_error.h"
#include "eval_numbers.h"
#include "structures/function.h"
#include "expressions/comparateurs.h"
#include "expressions/operateurs.h"

void free_pointers(char** ptr) {
    free(ptr[0]);
    free(ptr[2]);
    free(ptr);
}

char* get_first_n(char* s, int n) {
    char* s2 = malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    s2[n] = '\0';
    return s2;
}

int log_10_entier(int a) {
    float i = 0;
    while (a > 0) {
        a /= 10;
        i += 1;
    }
    return i;
}

int puiss10(int a) {
    float i = 1;
    while (a > 0) {
        a /= 10;
        i *= 10;
    }
    return i;
}

char** cut_a_b(char* s, int a, int b) {
    int len = (int)strlen(s);
    char** l = malloc(3 * sizeof(char*));
    char* start;
    char* middle;
    char* end;
    if (a + b > len) {
        start = malloc(sizeof(char));
        middle = malloc(sizeof(char));
        end = malloc(sizeof(char));
        strcpy(start, "");
        strcpy(middle, "");
        strcpy(end, "");
    } else {
        start = malloc((len + 1) * sizeof(char));
        middle = malloc((len - (a + b) + 1) * sizeof(char));
        end = malloc((b + 1) * sizeof(char));
        int index = 0;

        for (int i = 0; index < a; i++) {
            start[i] = s[index];
            index++;
        }
        start[a] = '*';
        start[a + 1] = '\0';

        for (int i = 0; index < len - b; i++) {
            middle[i] = s[index];
            index++;
        }
        middle[len - (a + b)] = '\0';

        for (int i = 0; index < len; i++) {
            end[i] = s[index];
            index++;
        }
        end[b] = '\0';
    }

    l[0] = start;
    l[1] = middle;
    l[2] = end;

    return l;
}

char** split_word(char* str, char* separator) {
    int len = (int)strlen(str);
    char** l = malloc(2 * sizeof(char*));

    int sep_len = (int)strlen(separator);

    char* str1 = malloc((len + 1) * sizeof(char));
    char* str2 = malloc((len + 1) * sizeof(char));
    int num = 1;
    int index = 0;

    for (int i = 0; i < len; i++) {
        bool broken = false;
        if (i < len - sep_len && str[i] == ' ' && str[i + sep_len + 1] == ' ') {
            for (int j = 0; j < sep_len; j++) {
                if (str[i + 1 + j] != separator[j]) {
                    broken = true;
                    break;
                }
            }
            if (!broken) {
                str1[index] = '\0';
                num = 2;
                i += sep_len + 1;
                index = 0;
            } else {
                if (num == 1) {
                    str1[index] = str[i];
                    index++;
                } else {
                    str2[index] = str[i];
                    index++;
                }
            }
        } else {
            if (num == 1) {
                str1[index] = str[i];
                index++;
            } else {
                str2[index] = str[i];
                index++;
            }
        }
    }
    str2[index] = '\0';
    if (num == 1) {
        str2[0] = '\0';
    }
    l[0] = str1;
    l[1] = str2;
    return l;
}

int elem_liste(char* text) {
    if (!strcmp(text, SOMME_S)) {
        return SOMME;
    }
    if (!strcmp(text, DIFFERENCE_S)) {
        return DIFFERENCE;
    }
    if (!strcmp(text, PRODUIT_S)) {
        return PRODUIT;
    }
    if (!strcmp(text, QUOTIENT_S)) {
        return QUOTIENT;
    }
    if (!strcmp(text, QUOTIENT_ENTIER_S)) {
        return QUOTIENT_ENTIER;
    }
    if (!strcmp(text, RESTE_S)) {
        return RESTE;
    }
    if (!strcmp(text, NEGATION_BOOLEENNE_S)) {
        return NEGATION_BOOLEENNE;
    }
    if (!strcmp(text, SI_ALORS_S)) {
        return SI_ALORS;
    }
    if (!strcmp(text, SINON_S)) {
        return SINON;
    }
    if (!strcmp(text, TANT_QUE_S)) {
        return TANT_QUE;
    }
    if (!strcmp(text, POUR_SANS_PAS_S)) {
        return POUR_SANS_PAS;
    }
    if (!strcmp(text, POUR_AVEC_PAS_S)) {
        return POUR_AVEC_PAS;
    }
    if (!strcmp(text, AFFICHE_EXPR_S)) {
        return AFFICHE_EXPR;
    }
    if (!strcmp(text, AFFICHE_STR_S)) {
        return AFFICHE_STR;
    }
    if (!strcmp(text, RENVOI_FONCTION_S)) {
        return RENVOI_FONCTION;
    }
    if (!strcmp(text, MAIN_PHRASE_S)) {
        return MAIN_PHRASE;
    }
    if (!strcmp(text, EGALITE_S)){
        return EGALITE;
    }
    if (!strcmp(text, PLUS_GRAND_S)){
        return PLUS_GRAND;
    }
    if (!strcmp(text, STRICT_PLUS_GRAND_S)){
        return STRICT_PLUS_GRAND;
    }
    if (!strcmp(text, PLUS_PETIT_S)){
        return PLUS_PETIT;
    }
    if (!strcmp(text, STRICT_PLUS_PETIT_S)){
        return STRICT_PLUS_PETIT;
    }
    return -1;
}

int value_type(phrase_t* p1, phrase_t* p2) {
    if (p1->valeur->type == FLOAT || p2->valeur->type == FLOAT) {
        return FLOAT;
    }
    return INT;
}

void tokenise(phrase_t* phrase, function_t* function, function_list_t* func_list) {
    bool valid = true;
    // printf("tokenise %s\n", phrase->text);
    if (phrase->phraseId != -1) {
        return;
    }

    switch (elem_liste(phrase->text)) {
        case MAIN_PHRASE:
            phrase->phraseId = MAIN_PHRASE;
            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list);
            }
            for (int i = 0; i<func_list->function_list_len; i++){
                func_list->function_list[i]->ast->phraseId = MAIN_PHRASE;
                addToText(func_list->function_list[i]->ast, '#');
            }
            break;
        case SOMME:
            phrase->phraseId = SOMME;
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, la somme prend 2 arguments", phrase);
            }
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                somme(phrase,true);
            }
            break;

        case DIFFERENCE:
            phrase->phraseId = DIFFERENCE;
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, la différence prend 2 arguments", phrase);
            }
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                difference(phrase,true);
            }
            break;
        case PRODUIT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, le produit prend 2 arguments", phrase);
            }
            phrase->phraseId = PRODUIT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                produit(phrase,true);
            }
            break;

        case QUOTIENT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, quotient prend 2 arguments", phrase);
            }
            phrase->phraseId = QUOTIENT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                quotient(phrase,true);
            }
            break;

        case QUOTIENT_ENTIER:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, le quotient entier prend 2 arguments", phrase);
            }
            phrase->phraseId = QUOTIENT_ENTIER;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                quotient_entier(phrase,true);
            }
            break;

        case RESTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, le reste prend 2 arguments", phrase);
            }
            phrase->phraseId = RESTE;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                reste(phrase,true);
            }

            break;
        case NEGATION_BOOLEENNE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 1) {
                custom_error("Invalid Syntax, la négation booléenne prend 1 argument", phrase);
            }
            phrase->phraseId = NEGATION_BOOLEENNE;
            if (phrase->args[0]->phraseId <= 3 && phrase->args[0]->phraseId >= 1) {
                negation_booleenne(phrase,true);   
            }

            break;
        case EGALITE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, l'égalité prend 2 arguments", phrase);
            }
            phrase->phraseId = EGALITE;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                egalite(phrase, true);
            }
            break;
        case PLUS_GRAND:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, la comparaison prend 2 arguments", phrase);
            }
            phrase->phraseId = PLUS_GRAND;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                plus_grand(phrase,true);
            }
            break;
        case PLUS_PETIT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, la comparaison prend 2 arguments", phrase);
            }
            phrase->phraseId = PLUS_PETIT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                plus_petit(phrase, true);
            }
            break;
        case STRICT_PLUS_GRAND:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, la comparaison prend 2 arguments", phrase);
            }
            phrase->phraseId = STRICT_PLUS_GRAND;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                strict_plus_grand(phrase,true);
            }
            break;
        case STRICT_PLUS_PETIT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Invalid Syntax, la comparaison prend 2 arguments", phrase);
            }
            phrase->phraseId = STRICT_PLUS_PETIT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                strict_plus_petit(phrase,true);
            }
            break;

            break;
        case AFFICHE_EXPR:
            if (phrase->argsLen != 1 || phrase->innerPhraseLen > 0) {
                custom_error("Invalid Syntax, affiche expression prend un arguments", phrase);
            }
            phrase->phraseId = AFFICHE_EXPR;
            tokenise(phrase->args[0], function, func_list);
            break;
        case AFFICHE_STR:
            if (phrase->argsLen != 1 || phrase->innerPhraseLen > 0) {
                custom_error("Invalid Syntax, affiche message prend un arguments", phrase);
            }
            if (phrase->args[0]->phraseId != EXPR_CHAINE) {
                custom_error("Invalid Syntax, affiche message prend un message", phrase);
            }
            phrase->phraseId = AFFICHE_STR;
            tokenise(phrase->args[0], function, func_list);
            break;
        case RENVOI_FONCTION:
            if (phrase->argsLen != 1 || phrase->innerPhraseLen > 0) {
                custom_error("Invalid Syntax, renvoi prend un arguments", phrase);
            }
            phrase->phraseId = RENVOI_FONCTION;
            tokenise(phrase->args[0], function, func_list);
            break;
        case SI_ALORS:
            if (phrase->argsLen != 1) {
                custom_error("Invalid Syntax, si alors prend 1 arguments", phrase);
            }
            if (phrase->innerPhraseLen == 0){
                custom_error("Invalid Syntax, si alors prend au moins 1 instruction", phrase);
            }
            phrase->phraseId = SI_ALORS;
            tokenise(phrase->args[0], function, func_list);
            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list);
            }
            break;
        case SINON:
            if (phrase->innerPhraseLen == 0){
                custom_error("Invalid Syntax, sinon prend au moins 1 instruction", phrase);
            }
            phrase->phraseId = SINON;
            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list);
            }
            break;

        default:
            if (test_expr_entier(phrase)) {
            } else if (test_expr_flottant(phrase)) {
            } else if (test_expr_booleen(phrase)) {
            } else if (test_inst_var_init(phrase, function)) {
            } else if (test_inst_create_var(phrase, function)) {
            } else if (test_expr_access_var(phrase, function)) {
            } else if (test_inst_modif_var(phrase, function)) {
            } else if (test_inst_create_list(phrase, function)) {
            } else if (test_expr_access_list(phrase, function)) {
            } else if (test_inst_modif_list(phrase, function)) {
            } else if (test_inst_suppr_list(phrase, function)) {
            } else if (test_expr_taille_list(phrase, function)) {
            } else if (test_inst_exec_func(phrase, func_list)) {
            } else if (test_expr_func_call(phrase, func_list)) {
            } else if (test_inst_def_func_args(phrase, func_list)) {
            } else if (test_inst_def_func(phrase, func_list)) {
            } else if (test_inst_exec_func_args(phrase, func_list)) {
            } else if (test_expr_func_call_args(phrase, func_list)) {
            } else if (test_inst_affiche_message(phrase)) {
            } else {
                custom_error("Syntaxe Invalide", phrase);
            }

            if (phrase->phraseId == DEFINITION_FONCTION || phrase->phraseId == DEFINITION_FONCTION_ARGUMENT) {
                for (int i = 0; i < phrase->innerPhraseLen; i++) {
                    tokenise(phrase->innerPhrase[i], phrase->function, func_list);
                }

            } else {
                for (int i = 0; i < phrase->argsLen; i++) {
                    tokenise(phrase->args[i], function, func_list);
                }
                for (int i = 0; i < phrase->innerPhraseLen; i++) {
                    tokenise(phrase->innerPhrase[i], function, func_list);
                }
            }

            break;
    }
}

phrase_t* calculate_args(phrase_t* phrase) {
    return phrase;
}
// checks the essential syntax (number of arguments, if can have inners, if the else ius well placed ...)
void check_syntax(phrase_t* phrase) {
    if (phrase->phraseId == -1) {
        custom_error("Syntaxe Invalide", phrase);
    }
    return;
}
