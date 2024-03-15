#include "syntax_convert.h"

#include "assert.h"
#include "custom_error.h"
#include "eval_numbers.h"
#include "function.h"

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

float log_10_entier(int a) {
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
        start = malloc(len * sizeof(char));
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
    printf("%s\n", text);
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
    if (!strcmp(text, MAIN_PHRASE_S)) {
        return MAIN_PHRASE;
    }
    return -1;
}

int value_type(phrase_t* p1, phrase_t* p2) {
    if (p1->valeur->type == FLOAT || p2->valeur->type == FLOAT) {
        return FLOAT;
    }
    return INT;
}

float return_value(phrase_t* p) {
    switch (p->valeur->type) {
        case INT:
            return (float)get_int(p->valeur);

        case FLOAT:
            return get_float(p->valeur);

        case BOOL:
            return (float)get_bool(p->valeur);

        default:
            return -1;
    }
}

void tokenise(phrase_t* phrase, function_t* function, function_list_t* func_list) {
    bool valid = true;

    switch (elem_liste(phrase->text)) {
        case MAIN_PHRASE:
            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list);
            }
            break;
        case SOMME:
            phrase->phraseId = SOMME;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                phrase->valeur = new_val();
                set_float(phrase->valeur, return_value(phrase->args[0]) + return_value(phrase->args[1]));
                if (!(phrase->args[0]->valeur->type == FLOAT && phrase->args[1]->valeur->type == FLOAT)) {
                    set_int(phrase->valeur, get_float(phrase->valeur));
                }
            }
            break;

        case DIFFERENCE:
            phrase->phraseId = DIFFERENCE;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                phrase->valeur = new_val();
                set_float(phrase->valeur, return_value(phrase->args[0]) - return_value(phrase->args[1]));
                if (!(phrase->args[0]->valeur->type == FLOAT && phrase->args[1]->valeur->type == FLOAT)) {
                    set_int(phrase->valeur, get_float(phrase->valeur));
                }
            }
            break;
        case PRODUIT:
            phrase->phraseId = PRODUIT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                phrase->valeur = new_val();
                set_float(phrase->valeur, return_value(phrase->args[0]) * return_value(phrase->args[1]));
                if (!(phrase->args[0]->valeur->type == FLOAT && phrase->args[1]->valeur->type == FLOAT)) {
                    set_int(phrase->valeur, get_float(phrase->valeur));
                }
            }
            break;
        case QUOTIENT:
            phrase->phraseId = QUOTIENT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                if (return_value(phrase->args[1]) == 0) {
                    phrase->error = true;
                    custom_error("Division par 0", phrase);
                }
                phrase->valeur = new_val();
                set_float(phrase->valeur, return_value(phrase->args[0]) / return_value(phrase->args[1]));
            }
            break;
        case QUOTIENT_ENTIER:
            phrase->phraseId = QUOTIENT_ENTIER;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                if (return_value(phrase->args[1]) == 0) {
                    phrase->error = true;
                    custom_error("Division par 0", phrase);
                }
                phrase->valeur = new_val();
                set_int(phrase->valeur, (int)(return_value(phrase->args[0]) / return_value(phrase->args[1])));
            }
            break;
        case RESTE:
            phrase->phraseId = RESTE;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                if (return_value(phrase->args[1]) == 0) {
                    phrase->error = true;
                    custom_error("Division par 0", phrase);
                }
                if (phrase->args[0]->valeur->type != INT || phrase->args[1]->valeur->type != INT) {
                    phrase->error = true;
                    custom_error("Les deux nombres doivent être entiers", phrase);
                }
                phrase->valeur = new_val();
                set_int(phrase->valeur, get_int(phrase->args[0]->valeur) % get_int(phrase->args[1]->valeur));
            }
            break;
        case NEGATION_BOOLEENNE:
            phrase->phraseId = NEGATION_BOOLEENNE;
            if (phrase->args[0]->phraseId <= 3 && phrase->args[0]->phraseId >= 1) {
                set_bool(phrase->valeur, !(bool)return_value(phrase->args[0]));
            }
            break;
        case EGALITE:
            phrase->phraseId = EGALITE;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                set_bool(phrase->valeur, return_value(phrase->args[0]) == return_value(phrase->args[1]));
            }
            break;
        case PLUS_GRAND:
            phrase->phraseId = PLUS_GRAND;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                set_bool(phrase->valeur, return_value(phrase->args[0]) >= return_value(phrase->args[1]));
            }
            break;
        case PLUS_PETIT:
            phrase->phraseId = PLUS_PETIT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                set_bool(phrase->valeur, return_value(phrase->args[0]) <= return_value(phrase->args[1]));
            }
            break;
        case STRICT_PLUS_GRAND:
            phrase->phraseId = STRICT_PLUS_GRAND;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                set_bool(phrase->valeur, return_value(phrase->args[0]) > return_value(phrase->args[1]));
            }
            break;
        case STRICT_PLUS_PETIT:
            phrase->phraseId = STRICT_PLUS_PETIT;
            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list);
                if (phrase->args[i]->phraseId > 3 || phrase->args[i]->phraseId < 1) {
                    valid = false;
                }
            }
            if (valid) {
                set_bool(phrase->valeur, return_value(phrase->args[0]) < return_value(phrase->args[1]));
            }
            break;
        default:
            if (test_expr_entier(phrase)){}
            else if (test_expr_flottant(phrase)){}
            else if (test_expr_booleen(phrase)){}
            else if (test_expr_chaine(phrase)){}
            else if (test_inst_var_init(phrase, function)){}
            else if (test_inst_create_var(phrase, function)){}
            else if (test_expr_access_var(phrase, function)){}
            else if (test_inst_modif_var(phrase, function)){}
            else if (test_inst_create_list(phrase, function)){}
            else if (test_expr_access_list(phrase, function)){}
            else if (test_inst_modif_list(phrase, function)){}
            else if (test_inst_modif_list(phrase, function)){}
            else if (test_inst_suppr_list(phrase, function)){}
            else if (test_expr_taille_list(phrase, function)){}
            else if (test_inst_def_func(phrase, func_list)){}
            else if (test_inst_exec_func(phrase, func_list)){}
            else if (test_expr_func_call(phrase, func_list)){}
            else if (test_inst_def_func_args(phrase, func_list)){}
            else if (test_inst_exec_func_args(phrase, func_list)){}
            else if (test_expr_func_call_args(phrase, func_list)){
                phrase->error = true;
                custom_error("Syntaxe Invalide", phrase);
            }

            for (int i = 0; i < phrase->argsLen; i++) {
                tokenise(phrase->args[i], function, func_list);
            }
            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list);
            }

            break;

    }
}

phrase_t* calculate_args(phrase_t* phrase) {
    return phrase;
}
