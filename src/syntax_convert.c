#include "syntax_convert.h"

#include <assert.h>

#include "custom_error.h"
#include "eval_numbers.h"
#include "expressions/comparateurs.h"
#include "expressions/operateurs.h"
#include "structures/function.h"

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
    if (!strcmp(text, QUITTER_BOUCLE_S)) {
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
    if (!strcmp(text, AFFICHER_EXPR_NO_RETURN_S)) {
        return AFFICHER_EXPR_NO_RETURN;
    }
    if (!strcmp(text, DEFINIR_SEED_S)) {
        return DEFINIR_SEED;
    }
    if (!strcmp(text, NOMBRE_ALEATOIRE_S)) {
        return NOMBRE_ALEATOIRE;
    }
    if (!strcmp(text, PARTIE_ENTIERE_S)){
        return PARTIE_ENTIERE;
    }
    return -1;
}

void tokenise(phrase_t* phrase, function_t* function, function_list_t* func_list, function_list_t* func_call_list, int* uniqueId, phrase_t* parent_loop, bool inLoopSuivant, phrase_t* inLoopSuivantPointer) {
    if (phrase->phraseId != -1) {
        return;
    }

    // donne l'identifiant unique au expressions
    if (phrase->expr) {
        phrase->uniqueId = *uniqueId;
        (*uniqueId)++;
        linkValeur(function->env);
    }

    bool constant = true;
    // printf("text: %s -> ", phrase->text);
    // fflush(stdout);
    // if (phrase->suivant != NULL) {
    //     printf("%s\n\n", phrase->suivant->text);
    // } else {
    //     printf("\n\n");
    // }
    switch (elem_liste(phrase->text)) {
        case MAIN_PHRASE:
            if (phrase->argsLen > 0) {
                custom_error("La phrase principale ne prend pas d'arguments", NULL, NULL);
            }

            phrase->phraseId = MAIN_PHRASE;
            phrase->suivantInner1 = phrase->suivant;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            phrase->suivant = NULL;

            for (int i = 0; i < phrase->innerPhraseLen; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            }

            // printf("remove consts\n");
            // exit(1);
            removeConstants(phrase);
            // exit(1);

            // links the function calls to their respective functions
            link_function_to_call(func_list, func_call_list, function->env);

            for (int i = 0; i < func_list->function_list_len; i++) {
                func_list->function_list[i]->ast->phraseId = MAIN_PHRASE;
                addToText(func_list->function_list[i]->ast, '#');
            }
            break;
        case SOMME:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la somme prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = SOMME;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                somme(phrase, function->env);
            }
            break;

        case DIFFERENCE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la différence prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = DIFFERENCE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                difference(phrase, function->env);
            }
            break;
        case PRODUIT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, le produit prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = PRODUIT;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                produit(phrase, function->env);
            }
            break;

        case QUOTIENT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, quotient prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = QUOTIENT;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                quotient(phrase, function->env);
            }
            break;

        case QUOTIENT_ENTIER:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, le quotient entier prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = QUOTIENT_ENTIER;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                quotient_entier(phrase, function->env);
            }
            break;

        case RESTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, le reste prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = RESTE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                reste(phrase, function->env);
            }

            break;
        case NEGATION_BOOLEENNE:

            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, la négation booléenne prend 1 argument", phrase, function->env);
            }
            phrase->phraseId = NEGATION_BOOLEENNE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            if (phrase->args[0]->constant) {
                negation_booleenne(phrase, function->env);
                phrase->constant = true;
            }
            break;

        case EGALITE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, l'égalité prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = EGALITE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                egalite(phrase, function->env);
            }
            break;

        case INEGALITE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, l'égalité prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = INEGALITE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                inegalite(phrase, function->env);
            }
            break;

        case PLUS_GRAND:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la comparaison prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = PLUS_GRAND;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                plus_grand(phrase, function->env);
            }
            break;
        case PLUS_PETIT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la comparaison prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = PLUS_PETIT;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                plus_petit(phrase, function->env);
            }
            break;
        case STRICT_PLUS_GRAND:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la comparaison prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = STRICT_PLUS_GRAND;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                strict_plus_grand(phrase, function->env);
            }
            break;
        case STRICT_PLUS_PETIT:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, la comparaison prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = STRICT_PLUS_PETIT;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < 2; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                if (!phrase->args[i]->constant) {
                    constant = false;
                }
            }
            if (constant) {
                phrase->constant = true;
                strict_plus_petit(phrase, function->env);
            }
            break;

            break;
        case AFFICHER_EXPR:
            if (phrase->argsLen == 0 || phrase->innerPhraseLen > 0) {
                custom_error("Syntaxe invalide, affiche expression prend au moins un arguments", phrase, function->env);
            }
            phrase->phraseId = AFFICHER_EXPR;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < phrase->argsLen; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            }

            break;
        case AFFICHER_EXPR_NO_RETURN:
            if (phrase->argsLen == 0 || phrase->innerPhraseLen > 0) {
                custom_error("Syntaxe invalide, affiche expression sans retour prend au moins un arguments", phrase, function->env);
            }
            phrase->phraseId = AFFICHER_EXPR_NO_RETURN;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < phrase->argsLen; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            }
            break;
        case RENVOI_FONCTION:
            if (phrase->argsLen != 1 || phrase->innerPhraseLen > 0) {
                custom_error("Syntaxe invalide, renvoi prend un arguments", phrase, function->env);
            }
            phrase->phraseId = RENVOI_FONCTION;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            break;
        case SI_ALORS:
            if (phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, si alors prend 1 arguments", phrase, function->env);
            }
            if (phrase->innerPhraseLen == 0) {
                custom_error("Syntaxe invalide, si alors prend au moins 1 instruction", phrase, function->env);
            }
            phrase->phraseId = SI_ALORS;

            // linéarisation
            phrase->suivantInner1 = phrase->suivant;
            phrase->suivant = phrase->innerPhrase[phrase->innerPhraseLen - 1]->suivant;
            phrase->innerPhrase[phrase->innerPhraseLen - 1]->suivant = phrase->suivant;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            // printf("%s\n", phrase->text);

            // printf("suivant inner1: %s\n", phrase->suivantInner1->text);
            // printf("suivant: %s\n", phrase->suivant->text);

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            for (int i = 0; i < phrase->innerPhraseLen - 1; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            }
            tokenise(phrase->innerPhrase[phrase->innerPhraseLen - 1], function, func_list, func_call_list, uniqueId, parent_loop, true, phrase->suivant);

            break;
        case SI_ALORS_SINON:
            if (phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, 'si alors sinon' prend 1 arguments", phrase, function->env);
            }
            if (phrase->innerSeparator == -1) {
                custom_error("Syntaxe invalide, 'si alors sinon' prend au moins 1 instruction dans le si", phrase, function->env);
            }
            if (phrase->innerSeparator >= phrase->innerPhraseLen - 1) {
                custom_error("Syntaxe invalide, 'si alors sinon' prend au moins 1 instruction dans le sinon", phrase, function->env);
            }

            phrase->phraseId = SI_ALORS_SINON;

            // linéarisation
            phrase->suivantInner1 = phrase->suivant;
            phrase->suivantInner2 = phrase->innerPhrase[phrase->innerSeparator]->suivant;
            phrase->suivant = phrase->innerPhrase[phrase->innerPhraseLen - 1]->suivant;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            // printf("suivant inner1: %s\n", phrase->suivantInner1->text);
            // printf("suivant inner2: %s\n", phrase->suivantInner2->text);
            // printf("suivant: %s\n", phrase->text);

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            for (int i = 0; i < phrase->innerSeparator; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            }
            tokenise(phrase->innerPhrase[phrase->innerSeparator], function, func_list, func_call_list, uniqueId, parent_loop, true, phrase->suivant);

            for (int i = phrase->innerSeparator + 1; i < phrase->innerPhraseLen - 1; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            }
            tokenise(phrase->innerPhrase[phrase->innerPhraseLen - 1], function, func_list, func_call_list, uniqueId, parent_loop, true, phrase->suivant);

            break;
        case TANT_QUE:
            if (phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, tant que prend 1 arguments", phrase, function->env);
            }
            if (phrase->innerPhraseLen == 0) {
                custom_error("Syntaxe invalide, tant que prend au moins 1 instruction", phrase, function->env);
            }
            phrase->phraseId = TANT_QUE;

            // linéarisation
            phrase->suivantInner1 = phrase->suivant;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            } else {
                phrase->suivant = recLastInner(phrase)->suivant;
            }

            // printf("suivant inner1: %s\n", phrase->suivantInner1->text);
            // printf("suivant: %s\n", phrase->suivant->text);

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, phrase, false, NULL);
            for (int i = 0; i < phrase->innerPhraseLen - 1; i++) {
                tokenise(phrase->innerPhrase[i], function, func_list, func_call_list, uniqueId, phrase, false, NULL);
            }
            tokenise(phrase->innerPhrase[phrase->innerPhraseLen - 1], function, func_list, func_call_list, uniqueId, phrase, true, recLastArg(phrase));

            // printf("last tant que: %s %s\n", phrase->innerPhrase[phrase->innerPhraseLen - 1]->text, phrase->innerPhrase[phrase->innerPhraseLen - 1]->suivant->text);
            break;
        case QUITTER_BOUCLE:
            if (phrase->argsLen != 0 || phrase->innerPhraseLen != 0) {
                custom_error("Syntaxe invalide, quitter boucle ne prend pas d'arguments", phrase, function->env);
            }
            phrase->phraseId = QUITTER_BOUCLE;

            if (parent_loop == NULL) {
                custom_error("Il l'y a pas de boucles à quitter", phrase, function->env);
            }
            phrase->suivant = parent_loop;
            break;

        case EXPR_LISTE_VIDE:
            phrase->phraseId = EXPR_LISTE_VIDE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            function->env->phraseValeurs[phrase->uniqueId]->type = LISTE;
            function->env->phraseValeurs[phrase->uniqueId]->value.liste = new_liste_t();
            phrase->constant = true;
            break;
        case EXPR_LISTE_ELEM:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen == 0) {
                custom_error("Syntaxe invalide, liste d'éléments au moins prend 1 arguments", phrase, function->env);
            }
            phrase->phraseId = EXPR_LISTE_ELEM;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            for (int i = 0; i < phrase->argsLen; i++) {
                tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            }
            break;
        case AJOUT_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, ajout liste prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = AJOUT_LISTE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            tokenise(phrase->args[1], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            break;
        case ACCESSION_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, accès liste prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = ACCESSION_LISTE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            tokenise(phrase->args[1], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            break;
        case MODIFICATION_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 3) {
                custom_error("Syntaxe invalide, modification liste prend 3 arguments", phrase, function->env);
            }
            phrase->phraseId = MODIFICATION_LISTE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            tokenise(phrase->args[1], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            tokenise(phrase->args[2], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            break;
        case SUPPRESSION_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, suppression liste prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = SUPPRESSION_LISTE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            tokenise(phrase->args[1], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            break;
        case INSERTION_LISTE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 3) {
                custom_error("Syntaxe invalide, insertion liste prend 3 arguments", phrase, function->env);
            }
            phrase->phraseId = INSERTION_LISTE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            tokenise(phrase->args[1], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            tokenise(phrase->args[2], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            break;
        case TYPE_EXPR:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, type prend 1 arguments", phrase, function->env);
            }
            phrase->phraseId = TYPE_EXPR;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            function->env->phraseValeurs[phrase->uniqueId]->type = CHAINE_DE_CHAR;
            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            if (phrase->args[0]->constant) {
                phrase->constant = true;
                function->env->phraseValeurs[phrase->uniqueId]->type = CHAINE_DE_CHAR;
                function->env->phraseValeurs[phrase->uniqueId]->value.chaine = new_chaine_t(str_type(function->env->phraseValeurs[phrase->args[0]->uniqueId]));
            }

            break;
        case ET:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, et prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = ET;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            function->env->phraseValeurs[phrase->uniqueId]->type = BOOL;
            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            tokenise(phrase->args[1], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);

            if (phrase->args[0]->constant && phrase->args[1]->constant) {
                et_booleen(phrase, function->env);
            }

            break;
        case OU:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 2) {
                custom_error("Syntaxe invalide, ou prend 2 arguments", phrase, function->env);
            }
            phrase->phraseId = OU;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            function->env->phraseValeurs[phrase->uniqueId]->type = BOOL;
            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            tokenise(phrase->args[1], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);

            if (phrase->args[0]->constant && phrase->args[1]->constant) {
                ou_booleen(phrase, function->env);
            }
            break;
        case EXPR_RIEN:
            phrase->phraseId = EXPR_RIEN;
            phrase->constant = true;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            function->env->phraseValeurs[phrase->uniqueId]->type = UNDEFINED;
            break;
        case TAILLE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, taille prend 1 arguments", phrase, function->env);
            }
            phrase->phraseId = TAILLE;

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            function->env->phraseValeurs[phrase->uniqueId]->type = INT;
            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            if (phrase->args[0]->constant) {
                taille(phrase, function->env);
                phrase->constant = true;
            }
            break;
        case DEFINIR_SEED:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, definition seed prend 1 arguments", phrase, function->env);
            }
            phrase->phraseId = DEFINIR_SEED;
            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            break;
        case NOMBRE_ALEATOIRE:
            phrase->phraseId = NOMBRE_ALEATOIRE;
            function->env->phraseValeurs[phrase->uniqueId]->type = FLOAT;
            break;
        case PARTIE_ENTIERE:
            if (phrase->innerPhraseLen > 0 || phrase->argsLen != 1) {
                custom_error("Syntaxe invalide, partie entière prend 1 arguments", phrase, function->env);
            }
            phrase->phraseId = PARTIE_ENTIERE;
            tokenise(phrase->args[0], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
            break;
        default: {
            if (test_expr_entier(phrase, function->env)) {
            } else if (test_expr_flottant(phrase, function->env)) {
            } else if (test_expr_booleen(phrase, function->env)) {
            } else if (test_expr_chaine(phrase, function->env)) {
                // variable
            } else if (test_inst_var_init(phrase, function)) {
            } else if (test_inst_create_var(phrase, function)) {
            } else if (test_expr_access_var(phrase, function)) {
            } else if (test_inst_modif_var(phrase, function)) {
                // liste
            } else if (test_expr_list(phrase, function)) {
                // fonction
            } else if (test_inst_def_func_args(phrase, func_list)) {
            } else if (test_inst_exec_func_args(phrase, func_list, function->env)) {
            } else if (test_expr_func_call_args(phrase, func_list, function->env)) {
            } else if (test_inst_def_func(phrase, func_list, function->env)) {
            } else if (test_inst_exec_func(phrase, func_list, function->env)) {
            } else if (test_expr_func_call(phrase, func_list, function->env)) {
                // boucle
            } else if (test_inst_for_loop(phrase, function)) {
            } else if (test_inst_for_loop_step(phrase, function)) {
            } else {
                custom_error("Syntaxe Invalide", phrase, function->env);
            }

            if (phrase->phraseId == DEFINITION_FONCTION || phrase->phraseId == DEFINITION_FONCTION_ARGUMENT) {
                phrase->suivantInner1 = phrase->suivant;
                phrase->suivant = recLastInner(phrase)->suivant;
                int count = 0;
                for (int i = 0; i < phrase->innerPhraseLen - 1; i++) {
                    tokenise(phrase->innerPhrase[i], phrase->function, func_list, func_call_list, &count, NULL, false, NULL);
                }
                tokenise(phrase->innerPhrase[phrase->innerPhraseLen - 1], phrase->function, func_list, func_call_list, &count, NULL, true, NULL);

                // printf("remove consts\n");
                // removeConstants(phrase);
                // printf("done\n");

            } else if (phrase->phraseId == POUR_AVEC_PAS || phrase->phraseId == POUR_SANS_PAS) {
                parent_loop = phrase;
                // linéarisation
                phrase->suivantInner1 = phrase->suivant;
                phrase->suivant = recLastInner(phrase)->suivant;

                // printf("suivant inner1: %s\n", phrase->suivantInner1->text);
                // printf("suivant: %s\n", phrase->suivant->text);
                // exit(1);
                for (int i = 0; i < phrase->argsLen; i++) {
                    tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                }
                for (int i = 0; i < phrase->innerPhraseLen - 1; i++) {
                    tokenise(phrase->innerPhrase[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                }
                tokenise(phrase->innerPhrase[phrase->innerPhraseLen - 1], function, func_list, func_call_list, uniqueId, parent_loop, true, phrase);

            } else {
                for (int i = 0; i < phrase->argsLen; i++) {
                    tokenise(phrase->args[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                }
                for (int i = 0; i < phrase->innerPhraseLen; i++) {
                    tokenise(phrase->innerPhrase[i], function, func_list, func_call_list, uniqueId, parent_loop, false, NULL);
                }
            }

            if (inLoopSuivant) {
                phrase->suivant = inLoopSuivantPointer;
            }

            if (phrase->phraseId == EXECUTION_FONCTION || phrase->phraseId == EXECUTION_FONCTION_ARGUMENT || phrase->phraseId == APPEL_VALEUR_FONCTION || phrase->phraseId == APPEL_VALEUR_FONCTION_ARGUMENT) {
                addToFunctionList(func_call_list, phrase->function);
            }

            break;
        }
    }
}

void link_function_to_call(function_list_t* func_list, function_list_t* func_call_list, environnement_t* env) {
    for (int i = 0; i < func_call_list->function_list_len; i++) {
        function_t* f = func_call_list->function_list[i];

        f->ast->function = getFunction(func_list, f->nom);
        if (f->ast->function == NULL) {
            custom_error("Fonction non définie", f->ast, env);
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

void removeConstants(phrase_t* phrase) {
    phrase_t** phrasesWithInner = malloc(sizeof(phrase_t*) * DEFAULT_PHRASE_INNER);
    int phrasesWithInnerLen = 0;
    int phrasesWithInnerSize = DEFAULT_PHRASE_INNER;
    phrase_t* phraseActuelle = phrase;

    while (phraseActuelle != NULL) {
        if (phraseActuelle->innerPhraseLen > 0) {
            if (phrasesWithInnerLen == phrasesWithInnerSize) {
                phrasesWithInnerSize *= 2;
                phrasesWithInner = realloc(phrasesWithInner, sizeof(phrase_t*) * phrasesWithInnerSize);
            }
            phrasesWithInner[phrasesWithInnerLen] = phraseActuelle;
            phrasesWithInnerLen++;
        }

        if (phraseActuelle->suivant == NULL) {
            break;
        }

        if (phraseActuelle->phraseId == QUITTER_BOUCLE) {
            // printf("quitter boucle  %s\n", phraseActuelle->suivant->text);
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

    // printf("phrases with inner len: %d\n", phrasesWithInnerLen);

    int i = 0;
    while (i < phrasesWithInnerLen) {
        while (phrasesWithInner[i]->suivantInner1 != NULL && (phrasesWithInner[i]->suivantInner1->constant || phrasesWithInner[i]->suivantInner1->phraseId == DEFINITION_FONCTION || phrasesWithInner[i]->suivantInner1->phraseId == DEFINITION_FONCTION_ARGUMENT)) {
            if (phrasesWithInner[i]->suivantInner1->phraseId == DEFINITION_FONCTION || phrasesWithInner[i]->suivantInner1->phraseId == DEFINITION_FONCTION_ARGUMENT) {
                if (phrasesWithInnerLen == phrasesWithInnerSize) {
                    phrasesWithInnerSize *= 2;
                    phrasesWithInner = realloc(phrasesWithInner, sizeof(phrase_t*) * phrasesWithInnerSize);
                }
                phrasesWithInner[phrasesWithInnerLen] = phrasesWithInner[i]->suivantInner1;
                phrasesWithInnerLen++;
            }

            phrasesWithInner[i]->suivantInner1 = phrasesWithInner[i]->suivantInner1->suivant;
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
            while (phrasesWithInner[i]->suivantInner2 != NULL && phrasesWithInner[i]->suivantInner2->constant) {
                if (phrasesWithInner[i]->suivantInner2->phraseId == DEFINITION_FONCTION || phrasesWithInner[i]->suivantInner2->phraseId == DEFINITION_FONCTION_ARGUMENT) {
                    if (phrasesWithInnerLen == phrasesWithInnerSize) {
                        phrasesWithInnerSize *= 2;
                        phrasesWithInner = realloc(phrasesWithInner, sizeof(phrase_t*) * phrasesWithInnerSize);
                    }
                    phrasesWithInner[phrasesWithInnerLen] = phrasesWithInner[i]->suivantInner2;
                    phrasesWithInnerLen++;
                }

                // printf("const %s %s\n", phrasesWithInner[i]->text, phrasesWithInner[i]->suivantInner2->text);
                phrasesWithInner[i]->suivantInner2 = phrasesWithInner[i]->suivantInner2->suivant;
            }
            // printf("inner2 '%s' -> '%s'\n", phrasesWithInner[i]->text, phrasesWithInner[i]->suivantInner2->text);
            removeConstants(phrasesWithInner[i]->suivantInner2);

            // exit(1);
        }

        i++;
    }

    free(phrasesWithInner);
}

phrase_t* recLastArg(phrase_t* phrase) {
    for (int i = phrase->argsLen - 1; i >= 0; i--) {
        if (!phrase->args[i]->constant) {
            return recLastArg(phrase->args[i]);
        }
    }
    return phrase;
}

phrase_t* recLastInner(phrase_t* phrase) {
    // printf("recGetLastInner %s\n", phrase->text);
    if (phrase->innerPhraseLen == 0) {
        return phrase;
    } else {
        return recLastInner(phrase->innerPhrase[phrase->innerPhraseLen - 1]);
    }
}
