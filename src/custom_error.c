#include "custom_error.h"

#include <stdio.h>
#include <stdlib.h>

bool is_instruction(phrase_t* p){
    switch (p->phraseId) {
        case MAIN_PHRASE:
        case DEFINITION_VARIABLE_AVEC_INIT:
        case DEFINITION_VARIABLE_SANS_INIT:
        case MODIFICATION_VARIABLE:
        case MODIFICATION_LISTE:
        case AJOUT_LISTE:
        case SUPPRESSION_LISTE:
        case INSERTION_LISTE:
        case SI_ALORS:
        case SI_ALORS_SINON:
        case TANT_QUE:
        case POUR_SANS_PAS:
        case POUR_AVEC_PAS:
        case QUITTER_BOUCLE:
        case AFFICHER_EXPR:
        case AFFICHER_EXPR_NO_RETURN:
        case DEFINITION_FONCTION:
        case DEFINIR_SEED:
        case EXECUTION_FONCTION:
        case RENVOI_FONCTION:
        case DEFINITION_FONCTION_ARGUMENT:
        case EXECUTION_FONCTION_ARGUMENT:
            return true;
            break;
        case EXPR_FLOTTANT:
        case EXPR_ENTIER:
        case EXPR_BOOLEEN:
        case EXPR_CHAINE:
        case EXPR_RIEN:
        case ACCESSION_VARIABLE:
        case POINTEUR_VERS_VALEUR:
        case VALEUR_POINTEE:
        case VALEUR_FINALE_POINTEE:
        case EXPR_LISTE_VIDE:
        case ACCESSION_LISTE:
        case EXPR_LISTE:
        case EXPR_LISTE_ELEM:
        case SOMME:
        case DIFFERENCE:
        case PRODUIT:
        case QUOTIENT:
        case QUOTIENT_ENTIER:
        case RESTE:
        case PARTIE_ENTIERE:
        case NEGATION_BOOLEENNE:
        case OU:
        case ET:
        case EGALITE:
        case INEGALITE:
        case PLUS_GRAND:
        case PLUS_PETIT:
        case STRICT_PLUS_GRAND:
        case STRICT_PLUS_PETIT:
        case TYPE_EXPR:
        case TAILLE:
        case INPUT_INT:
        case INPUT_FLOAT:
        case INPUT_BOOL:
        case INPUT:
        case CONVERT_TO_INT:
        case CONVERT_TO_FLOAT:
        case CONVERT_TO_BOOL:
        case CONVERT_TO_CHAR:
        case NOMBRE_ALEATOIRE:
        case APPEL_VALEUR_FONCTION:
        case APPEL_VALEUR_FONCTION_ARGUMENT:
            return false;
            break;
        default:
            return p->text[p->textLen-2] == '.';
            
    }
}

bool ignore_errors = false;

void set_ignore(void){
    ignore_errors = true;
}

void custom_error(char* err_message, phrase_t* phrase, environnement_t* env) {
    int ligne;
    if (ignore_errors){
        printf("\n\n========== ERREUR ===========\n\n");
        printf("Une erreur est survenue avec le message suivant:\n%s\n\n", err_message);
    }else{
        fprintf(stderr, "\n\n========== ERREUR ===========\n\n");
        fprintf(stderr, "Une erreur est survenue avec le message suivant:\n%s\n\n", err_message);
    }

    if (phrase != NULL) {
        phrase->error = true;
        while (phrase->parentPhrase != NULL && !is_instruction(phrase)) {
            phrase = phrase->parentPhrase;
        }
        ligne = phrase->line_number;
        if (ignore_errors){
            printf("À la ligne %d: \n", ligne);
        }else{
            fprintf(stderr, "À la ligne %d: \n", ligne);
        }
        if (env != NULL){
            printPhrase(phrase, env);
        }else{
            printPhrase(phrase, NULL);
        }
    }
    exit((int)!ignore_errors);
}
