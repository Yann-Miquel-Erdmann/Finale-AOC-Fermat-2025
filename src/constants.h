#ifndef CONSTANTS_H
#define CONSTANTS_H

// constantes structures phrase_t
#define DEFAULT_PHRASE_TEXT_SIZE 128
#define DEFAULT_PHRASE_ARGS 10
#define DEFAULT_PHRASE_INNER 20

// constantes structures liste_t
#define DEFAULT_VALEURS_LIST_SIZE 128

// constantes structures chaine_t
#define DEFAULT_CHAINE_CHARS_SIZE 8

// constantes structures environnement_t
#define DEFAULT_VARIABLES_LIST_SIZE 64
#define DEFAULT_LISTES_LIST_SIZE 64

// constantes structures function_t
#define DEFAULT_FUNCTION_LIST_SIZE 64

// val_t type
typedef enum valType_e {
    UNDEFINED,
    INT,
    FLOAT,
    BOOL,
    LISTE,
    CHAINE_DE_CHAR,
    POINTEUR
} valType;

// constantes pour l'interpréteur
#define MAX_RECUSION_DEPTH 10000

// constantes pour split args
#define DEFAULT_RES_SIZE 10
#define DEFAULT_CURR_SIZE 20

typedef enum phraseType_e {
    NO_ID,
    MAIN_PHRASE,
    
    // expressions
    EXPR_ENTIER,
    EXPR_FLOTTANT,
    EXPR_BOOLEEN,
    EXPR_CHAINE,
    EXPR_RIEN,
    
    // structures de données
    //  * variable
    DEFINITION_VARIABLE_AVEC_INIT,
    DEFINITION_VARIABLE_SANS_INIT,
    ACCESSION_VARIABLE,
    MODIFICATION_VARIABLE,
    
    //  * pointeurs
    POINTEUR_VERS_VALEUR,
    VALEUR_POINTEE,
    VALEUR_FINALE_POINTEE,
    
    //  * liste
    EXPR_LISTE_VIDE,
    ACCESSION_LISTE,
    MODIFICATION_LISTE,
    AJOUT_LISTE,
    SUPPRESSION_LISTE,
    TAILLE,
    INSERTION_LISTE,
    EXPR_LISTE,
    EXPR_LISTE_ELEM,
    
    // opérateurs
    SOMME,
    DIFFERENCE,
    PRODUIT,
    QUOTIENT,
    QUOTIENT_ENTIER,
    RESTE,
    PARTIE_ENTIERE,
    MOINS,
    
    // opérateurs booléens
    NEGATION_BOOLEENNE,
    ET,
    OU,
    
    // comparateurs
    EGALITE,
    INEGALITE,
    PLUS_GRAND,
    PLUS_PETIT,
    STRICT_PLUS_GRAND,
    STRICT_PLUS_PETIT,
    
    // conditions
    SI_ALORS,
    SI_ALORS_SINON,
    
    // boucles
    TANT_QUE,
    POUR_SANS_PAS,
    POUR_AVEC_PAS,
    QUITTER_BOUCLE,
    
    // interactions console
    AFFICHER_EXPR,
    AFFICHER_EXPR_NO_RETURN,
    TYPE_EXPR,
    INPUT_INT,
    INPUT_FLOAT,
    INPUT_BOOL,
    INPUT,
    
    // conversions de types
    CONVERT_TO_INT,
    CONVERT_TO_FLOAT,
    CONVERT_TO_BOOL,
    CONVERT_TO_CHAR,
    
    // aléatoire
    DEFINIR_SEED,
    NOMBRE_ALEATOIRE,
    
    // fonctions
    DEFINITION_FONCTION,
    EXECUTION_FONCTION,
    RENVOI_FONCTION,
    APPEL_VALEUR_FONCTION,
    DEFINITION_FONCTION_ARGUMENT,
    EXECUTION_FONCTION_ARGUMENT,
    APPEL_VALEUR_FONCTION_ARGUMENT
} phraseType;

#define DEFAULT_SEPARATOR "?,. "
#define STRING_SEPARATOR "\""
#define NUMBER_SEPARATOR "?,."

// définitions de syntaxe
#define MAIN_PHRASE_S "*"  // fait

// expressions
#define EXPR_ENTIER_S "L'entier $?"                 // fait + doc
#define EXPR_FLOTTANT_S "Le flottant $?"            // fait + doc
#define EXPR_BOOLEEN_S "Le booléen $?"              // fait + doc
#define EXPR_CHAINE_S "La chaîne de caractères $?"  // fait + doc
#define EXPR_RIEN_S "Rien?"                         // fait + doc

// structures de données
//  * variable
#define DEFINITION_VARIABLE_AVEC_INIT_S "Soit $ *."  // fait + doc
#define DEFINITION_VARIABLE_SANS_INIT_S "Soit $."    // fait + doc
#define ACCESSION_VARIABLE_S "La variable $?"        // fait + doc
#define MODIFICATION_VARIABLE_S "Que * devienne *."  // fait + doc

//  * pointeur
#define POINTEUR_VERS_VALEUR_S "Un pointeur vers *?"               // fait + doc
#define VALEUR_POINTEE_S "La valeur pointée par *?"                // fait + doc
#define VALEUR_FINALE_POINTEE_S "La valeur finale pointée par *?"  // fait + doc

//  * liste
#define EXPR_LISTE_VIDE_S "La liste vide?"                                   // fait + doc
#define ACCESSION_LISTE_S "L'élément de * à l'indice *?"                     // fait + doc
#define MODIFICATION_LISTE_S "Remplacer l'élément de * à l'indice * par *."  // fait + doc
#define AJOUT_LISTE_S "Ajouter à * *."                                       // fait + doc
#define SUPPRESSION_LISTE_S "Retirer l'élément de * à l'indice *."           // fait + doc
#define INSERTION_LISTE_S "Insérer * dans * à l'indice *."                   // fait + doc
#define EXPR_LISTE_S "La liste $?"                                           // fait + doc
#define EXPR_LISTE_ELEM_S "La liste des éléments *?"                         // fait + doc

// opérateurs
#define SOMME_S "La somme de * et de *?"                    // fait + doc
#define DIFFERENCE_S "La différence de * et de *?"          // fait + doc
#define PRODUIT_S "Le produit de * et de *?"                // fait + doc
#define QUOTIENT_S "Le quotient de * par *?"                // fait + doc
#define QUOTIENT_ENTIER_S "Le quotient entier de * par *?"  // fait + doc
#define RESTE_S "Le reste de * par *?"                      // fait + doc
#define PARTIE_ENTIERE_S "La partie entière de *?"          // fait + doc
#define MOINS_S "Moins *?"

// opérateur booléens
#define NEGATION_BOOLEENNE_S "La négation de * est vérifiée?"  // fait + doc
#define OU_S "La disjonction de * et de * est vérifiée?"       // fait + doc
#define ET_S "La conjonction de * et de * est vérifiée?"       // fait + doc

// comparateurs
#define EGALITE_S "La valeur de * est égale à la valeur de *?"                                // fait + doc
#define INEGALITE_S "La valeur de * est différente de la valeur de *?"                        // fait + doc
#define PLUS_GRAND_S "La valeur de * est plus grande que la valeur de *?"                     // fait + doc
#define PLUS_PETIT_S "La valeur de * est plus petite que la valeur de *?"                     // fait + doc
#define STRICT_PLUS_GRAND_S "La valeur de * est strictement plus grande que la valeur de *?"  // fait + doc
#define STRICT_PLUS_PETIT_S "La valeur de * est strictement plus petite que la valeur de *?"  // fait + doc

// conditions
#define SI_ALORS_S "Si * alors:*."               // fait + doc
#define SI_ALORS_SINON_S "Si * alors:*sinon:*."  // fait + doc

// boucles
#define TANT_QUE_S "Tant que *:*."                                                        // fait + doc
#define POUR_SANS_PAS_S "Pour $ allant de * jusqu'à * faire:*."                           // fait + doc
#define POUR_AVEC_PAS_S "Pour $ allant de * jusqu'à * en utilisant un pas de * faire:*."  // fait + doc
#define QUITTER_BOUCLE_S "Quitter la boucle."                                             // fait + doc

// interactions console
#define AFFICHER_EXPR_S "Afficher *."                                   // fait + doc
#define AFFICHER_EXPR_NO_RETURN_S "Afficher * sans retour à la ligne."  // fait + doc
#define TYPE_EXPR_S "Le type de *?"                                     // fait + doc
#define TAILLE_S "La longueur de *?"                                      // fait + doc
#define INPUT_INT_S "Une entrée entière?"                               // fait + doc
#define INPUT_FLOAT_S "Une entrée flottante?"                           // fait + doc
#define INPUT_BOOL_S "Une entrée booléenne?"                            // fait + doc
#define INPUT_S "Une entrée?"                                           // fait + doc

// conversions de types
#define CONVERT_TO_INT_S "La conversion en entier de *?"                 // fait + doc
#define CONVERT_TO_FLOAT_S "La conversion en flottant de *?"             // fait + doc
#define CONVERT_TO_BOOL_S "La conversion en booléen de *?"               // fait + doc
#define CONVERT_TO_CHAR_S "La conversion en chaîne de caractères de *?"  // fait + doc

// aléatoire
#define DEFINIR_SEED_S "Mettre la graine aléatoire à *."  // fait + doc
#define NOMBRE_ALEATOIRE_S "Un nombre aléatoire?"       // fait + doc

// fonctions
#define DEFINITION_FONCTION_S "Soit $ la fonction qui lorsqu'elle est appelée exécute:*."   // fait
#define EXECUTION_FONCTION_S "Exécuter la fonction $."                                      // fait
#define RENVOI_FONCTION_S "Renvoyer *."                                                     // fait
#define APPEL_VALEUR_FONCTION_S "Le résultat de la fonction $?"                             // fait

#define DEFINITION_FONCTION_ARGUMENT_S "Soit $ la fonction qui lorsqu'elle est appelée avec $ exécute:*."   // fait
#define EXECUTION_FONCTION_ARGUMENT_S "Exécuter la fonction $ avec les arguments *."                        // fait
#define APPEL_VALEUR_FONCTION_ARGUMENT_S "Le résultat de la fonction $ avec les arguments *?"               // fait

// current next error : 6

#ifndef __APPLE__
#define _Nullable
#define _Nonnull __attribute__((returns_nonnull))
#define __dead2 __attribute__((noreturn))
#define __result_use_check __attribute__((warn_unused_result))
#define __alloc_size(m) __attribute__((alloc_size(m)))
#endif

#endif /* CONSTANTS_H */
