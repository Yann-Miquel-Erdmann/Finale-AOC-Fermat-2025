#include "syntax_convert.h"

#include <assert.h>

#include "custom_error.h"
#include "eval_numbers.h"
#include "expressions/comparateurs.h"
#include "expressions/operateurs.h"
#include "structures/function.h"

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
    // printf("%s\n", text);
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
    if (!strcmp(text, SI_ALORS_SINON_S)) {
        return SI_ALORS_SINON;
    }
    if (!strcmp(text, TANT_QUE_S)) {
        return TANT_QUE;
    }
    if (!strcmp(text, QUITTER_BOUCLE_S)){
        return QUITTER_BOUCLE;
    }
    if (!strcmp(text, RENVOI_FONCTION_S)) {
        return RENVOI_FONCTION;
    }
    if (!strcmp(text, MAIN_PHRASE_S)) {
        return MAIN_PHRASE;
    }
    
    if (!strcmp(text, EGALITE_S)) {
        return EGALITE;
    }
    if (!strcmp(text, INEGALITE_S)) {
        return INEGALITE;
    }
    if (!strcmp(text, PLUS_GRAND_S)) {
        return PLUS_GRAND;
    }
    if (!strcmp(text, STRICT_PLUS_GRAND_S)) {
        return STRICT_PLUS_GRAND;
    }
    if (!strcmp(text, PLUS_PETIT_S)) {
        return PLUS_PETIT;
    }
    if (!strcmp(text, STRICT_PLUS_PETIT_S)) {
        return STRICT_PLUS_PETIT;
    }
    if (!strcmp(text, ET_S)) {
        return ET;
    }
    if (!strcmp(text, OU_S)) {
        return OU;
    }

    if (!strcmp(text, EXPR_LISTE_VIDE_S)) {
        return EXPR_LISTE_VIDE;
    }
    if (!strcmp(text, AJOUT_LISTE_S)) {
        return AJOUT_LISTE;
    }
    if (!strcmp(text, ACCESSION_LISTE_S)) {
        return ACCESSION_LISTE;
    }
    if (!strcmp(text, MODIFICATION_LISTE_S)) {
        return MODIFICATION_LISTE;
    }
    if (!strcmp(text, SUPPRESSION_LISTE_S)) {
        return SUPPRESSION_LISTE;
    }
    if (!strcmp(text, INSERTION_LISTE_S)) {
        return INSERTION_LISTE;
    }
    if (!strcmp(text, EXPR_LISTE_ELEM_S)) {
        return EXPR_LISTE_ELEM;
    }

    if (!strcmp(text, TYPE_EXPR_S)) {
        return TYPE_EXPR;
    }
    if (!strcmp(text, EXPR_RIEN_S)) {
        return EXPR_RIEN;
    }

    if (!strcmp(text, TAILLE_S)) {
        return TAILLE;
    }
    if (!strcmp(text, AFFICHER_EXPR_S)) {
        return AFFICHER_EXPR;
    }
    if (!strcmp(text, AFFICHER_EXPR_NO_RETURN_S)){
        return AFFICHER_EXPR_NO_RETURN;
    }
    return -1;
}

int value_type(phrase_t* p1, phrase_t* p2) {
    if (p1->valeur->type == FLOAT || p2->valeur->type == FLOAT) {
        return FLOAT;
    }
    return INT;
}

void tokenise(phrase_t* phrase, function_t* function, function_list_t* func_list, function_list_t* func_call_list) {
    if (phrase->phraseId != -1) {
        return;
    }
    bool constant = true;
    switch (elem_liste(phrase->text)) {
        case MAIN_PHRASE:
            if (phrase->argsLen > 0){
                custom_error("La phrase principale ne prend pas d'arguments", NULL);
            }
            phrase->phraseId = MAIN_PHRASE;
            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list, func_call_list);
            }

            // links the function calls to their respective functions
            link_function_to_call(func_list, func_call_list);
            // isolates each function's environment
            isolate_func_envs(func_list);

            for (int i = 0; i < func_list->function_list_len; i++) {
                func_list->function_list[i]->ast->phraseId = MAIN_PHRASE;
                addToText(func_list->function_list[i]->ast, '#');
            }
            break;
        case SOMME:
            phrase->phraseId = SOMME;
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la somme prend 2 arguments", phrase);
            }
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                somme(phrase, true);
            }
            break;

        case DIFFERENCE:
            phrase->phraseId = DIFFERENCE;
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la différence prend 2 arguments", phrase);
            }
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                difference(phrase, true);
            }
            break;
        case PRODUIT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, le produit prend 2 arguments", phrase);
            }
            phrase->phraseId = PRODUIT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                produit(phrase, true);
            }
            break;

        case QUOTIENT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, quotient prend 2 arguments", phrase);
            }
            phrase->phraseId = QUOTIENT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                quotient(phrase, true);
            }
            break;

        case QUOTIENT_ENTIER:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, le quotient entier prend 2 arguments", phrase);
            }
            phrase->phraseId = QUOTIENT_ENTIER;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                quotient_entier(phrase, true);
            }
            break;

        case RESTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, le reste prend 2 arguments", phrase);
            }
            phrase->phraseId = RESTE;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                reste(phrase, true);
            }

            break;
        case NEGATION_BOOLEENNE:

            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, la négation booléenne prend 1 argument", phrase);
            }
            phrase->phraseId = NEGATION_BOOLEENNE;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            if (phrase->args[0]->phraseId <= 3 && phrase->args[0]->phraseId >= 1) {
                negation_booleenne(phrase, true);
            }
            break;

        case EGALITE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, l'égalité prend 2 arguments", phrase);
            }
            phrase->phraseId = EGALITE;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                egalite(phrase, true);
            }
            break;

        case INEGALITE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, l'égalité prend 2 arguments", phrase);
            }
            phrase->phraseId = INEGALITE;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                inegalite(phrase, true);
            }
            break;

        case PLUS_GRAND:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la comparaison prend 2 arguments", phrase);
            }
            phrase->phraseId = PLUS_GRAND;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                plus_grand(phrase, true);
            }
            break;
        case PLUS_PETIT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la comparaison prend 2 arguments", phrase);
            }
            phrase->phraseId = PLUS_PETIT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                plus_petit(phrase, true);
            }
            break;
        case STRICT_PLUS_GRAND:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la comparaison prend 2 arguments", phrase);
            }
            phrase->phraseId = STRICT_PLUS_GRAND;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                strict_plus_grand(phrase, true);
            }
            break;
        case STRICT_PLUS_PETIT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la comparaison prend 2 arguments", phrase);
            }
            phrase->phraseId = STRICT_PLUS_PETIT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
                if (phrase->args[i]->phraseId > 4 || phrase->args[i]->phraseId < 1) {
                    constant = false;
                }
            }
            if (constant) {
                strict_plus_petit(phrase, true);
            }
            break;

            break;
        case AFFICHER_EXPR:
            if (phrase->argsLen == 0 || phrase->innerPhraseLen > 0) {
                custom_error("Syntaxe invalide, affiche expression prend au moins un arguments", phrase);
            }
            phrase->phraseId = AFFICHER_EXPR;
            for (int i = 0; i<phrase->argsLen; i++){
                tokenise(phrase->args[i], function, func_list, func_call_list);
            }
            
            break;
        case AFFICHER_EXPR_NO_RETURN:
            if (phrase->argsLen == 0 || phrase->innerPhraseLen > 0) {
                custom_error("Syntaxe invalide, affiche expression sans retour prend au moins un arguments", phrase);
            }
            phrase->phraseId = AFFICHER_EXPR_NO_RETURN;
            for (int i = 0; i<phrase->argsLen; i++){
                tokenise(phrase->args[i], function, func_list, func_call_list);
            }
            break;
        case RENVOI_FONCTION:
            if (phrase->argsLen != 1 || phrase->innerPhraseLen > 0) {
                custom_error("Syntaxe invalide, renvoi prend un arguments", phrase);
            }
            phrase->phraseId = RENVOI_FONCTION;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            break;
        case SI_ALORS:
            if (phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, si alors prend 1 arguments", phrase);
            }
            if (phrase->innerPhraseLen == 0) {
                custom_error("Syntaxe invalide, si alors prend au moins 1 instruction", phrase);
            }
            phrase->phraseId = SI_ALORS;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list, func_call_list);
            }
            break;
        case SI_ALORS_SINON:
            if (phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, 'si alors sinon' prend 1 arguments", phrase);
            }
            if (phrase->innerSeparator == -1) {
                custom_error("Syntaxe invalide, 'si alors sinon' prend au moins 1 instruction dans le si", phrase);
            }
            if (phrase->innerSeparator >= phrase->innerPhraseLen - 1) {
                custom_error("Syntaxe invalide, 'si alors sinon' prend au moins 1 instruction dans le sinon", phrase);
            }

            phrase->phraseId = SI_ALORS_SINON;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list, func_call_list);
            }
            break;
        case TANT_QUE:
            if (phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, tant que prend 1 arguments", phrase);
            }
            if (phrase->innerPhraseLen == 0) {
                custom_error("Syntaxe invalide, tant que prend au moins 1 instruction", phrase);
            }
            phrase->phraseId = TANT_QUE;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list, func_call_list);
            }
            break;
        case QUITTER_BOUCLE:
            if (phrase->argsLen != 0 || phrase->innerPhraseLen != 0) {
                custom_error("Syntaxe invalide, quitter boucle ne prend pas d'arguments", phrase);
            }
            phrase_t* p = phrase->parentPhrase;
            while (p->phraseId != TANT_QUE && p->phraseId != POUR_SANS_PAS && p->phraseId != POUR_AVEC_PAS) {
                if (p->parentPhrase == NULL) {
                    custom_error("Syntaxe invalide, quitter boucle doit être dans une boucle", phrase);
                }
                p = p->parentPhrase;
            }
            addToInner(phrase, p);  // quitter boucle prend en argument la boucle (tant que, pour sans pas, pour avec pas

            phrase->phraseId = QUITTER_BOUCLE;
            break;

        case EXPR_LISTE_VIDE:
            phrase->phraseId = EXPR_LISTE_VIDE;
            phrase->valeur->type = LISTE;
            phrase->valeur->liste = new_liste_t();
            phrase->valeur->to_free_list = true;
            phrase->constant = true;
            break;
        case EXPR_LISTE_ELEM:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen == 0) {
                custom_error("Syntaxe invalide, liste d'éléments au moins prend 1 arguments", phrase);
            }
            phrase->phraseId = EXPR_LISTE_ELEM;
            for (int i = 0; i < phrase->argsLen; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list);
            }
            break;
        case AJOUT_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, ajout liste prend 2 arguments", phrase);
            }
            phrase->phraseId = AJOUT_LISTE;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            tokenise(phrase->args[1], function, func_list, func_call_list);
            break;
        case ACCESSION_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, accès liste prend 2 arguments", phrase);
            }
            phrase->phraseId = ACCESSION_LISTE;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            tokenise(phrase->args[1], function, func_list, func_call_list);
            break;
        case MODIFICATION_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 3) {
                custom_error("Syntaxe invalide, modification liste prend 3 arguments", phrase);
            }
            phrase->phraseId = MODIFICATION_LISTE;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            tokenise(phrase->args[1], function, func_list, func_call_list);
            tokenise(phrase->args[2], function, func_list, func_call_list);
            break;
        case SUPPRESSION_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, suppression liste prend 2 arguments", phrase);
            }
            phrase->phraseId = SUPPRESSION_LISTE;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            tokenise(phrase->args[1], function, func_list, func_call_list);
            break;
        case INSERTION_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 3) {
                custom_error("Syntaxe invalide, insertion liste prend 3 arguments", phrase);
            }
            phrase->phraseId = INSERTION_LISTE;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            tokenise(phrase->args[1], function, func_list, func_call_list);
            tokenise(phrase->args[2], function, func_list, func_call_list);
            break;
        case TYPE_EXPR:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, type prend 1 arguments", phrase);
            }
            phrase->phraseId = TYPE_EXPR;
            phrase->valeur->type = CHAINE_DE_CHAR;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            break;
        case ET:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, et prend 2 arguments", phrase);
            }
            phrase->phraseId = ET;
            phrase->valeur->type = BOOL;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            tokenise(phrase->args[1], function, func_list, func_call_list);
            break;
        case OU:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, ou prend 2 arguments", phrase);
            }
            phrase->phraseId = OU;
            phrase->valeur->type = BOOL;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            tokenise(phrase->args[1], function, func_list, func_call_list);
            break;
        case EXPR_RIEN:
            phrase->phraseId = EXPR_RIEN;
            phrase->valeur->type = UNDEFINED;
            break;
        case TAILLE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, taille prend 1 arguments", phrase);
            }
            phrase->phraseId = TAILLE;
            phrase->valeur->type = INT;
            tokenise(phrase->args[0], function, func_list, func_call_list);
            break;

        default:
            if (test_expr_entier(phrase)) {
            } else if (test_expr_flottant(phrase)) {
            } else if (test_expr_booleen(phrase)) {
            } else if (test_expr_chaine(phrase)) {
                // variable
            } else if (test_inst_var_init(phrase, function)) {
            } else if (test_inst_create_var(phrase, function)) {
            } else if (test_expr_access_var(phrase, function)) {
            } else if (test_inst_modif_var(phrase, function)) {
                // liste
            } else if (test_expr_list(phrase, function)) {
                // fonction
            } else if (test_inst_def_func_args(phrase, func_list)) {
            } else if (test_inst_exec_func_args(phrase, func_list)) {
            } else if (test_expr_func_call_args(phrase, func_list)) {
            } else if (test_inst_def_func(phrase, func_list)) {
            } else if (test_inst_exec_func(phrase, func_list)) {
            } else if (test_expr_func_call(phrase, func_list)) {
                // boucle
            } else if (test_inst_for_loop(phrase, function)) {
            } else if (test_inst_for_loop_step(phrase, function)) {
            } else {
                custom_error("Syntaxe Invalide", phrase);
            }

            if (phrase->phraseId == DEFINITION_FONCTION || phrase->phraseId == DEFINITION_FONCTION_ARGUMENT) {
                for (int i = 0; i < phrase->innerPhraseLen; i++) {
                    tokenise(phrase->innerPhrase[i], phrase->function, func_list, func_call_list);
                }

            } else {
                for (int i = 0; i < phrase->argsLen; i++) {
                    tokenise(phrase->args[i], function, func_list, func_call_list);
                }
                for (int i = 0; i < phrase->innerPhraseLen; i++) {
                    tokenise(phrase->innerPhrase[i], function, func_list, func_call_list);
                }
            }

            if (phrase->phraseId == EXECUTION_FONCTION || phrase->phraseId == EXECUTION_FONCTION_ARGUMENT || phrase->phraseId == APPEL_VALEUR_FONCTION || phrase->phraseId == APPEL_VALEUR_FONCTION_ARGUMENT) {
                addToFunctionList(func_call_list, phrase->function);
            }

            break;
    }
}

void link_function_to_call(function_list_t* func_list, function_list_t* func_call_list) {
    for (int i = 0; i < func_call_list->function_list_len; i++) {
        function_t* f = func_call_list->function_list[i];

        f->ast->function = getFunction(func_list, f->nom);
        if (f->ast->function == NULL) {
            custom_error("Fonction non définie", f->ast);
        }

        free_environnement(f->env);
        free(f->nom);
        free(f);
    }

    free(func_call_list->function_list);
    free(func_call_list);
}

void isolate_func_envs(function_list_t* func_list) {
    for (int i = 0; i < func_list->function_list_len; i++) {
        function_t* f = func_list->function_list[i];
        if (f->ast->phraseId != MAIN_PHRASE) {
            f->ast = copy_phrase(f->ast, NULL, f->env);
        }
    }
}
