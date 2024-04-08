// constantes structures phrase_t
#define DEFAULT_PHRASE_TEXT_SIZE 128
#define DEFAULT_PHRASE_ARGS 10
#define DEFAULT_PHRASE_INNER 20

// constantes structures liste_t
#define DEFAULT_VALEURS_LIST_SIZE 128

// constantes structures chaine_t
#define DEFAULT_CHAINE_CHARS_SIZE 128

// constantes structures environnement_t
#define DEFAULT_VARIABLES_LIST_SIZE 64
#define DEFAULT_LISTES_LIST_SIZE 64

// constantes structures function_t
#define DEFAULT_FUNCTION_LIST_SIZE 64

// val_t type
#define UNDEFINED -1
#define INT 1
#define FLOAT 2
#define BOOL 3
#define LISTE 4
#define CHAINE_DE_CHAR 5

// constantes pour l'interpréteur
#define MAX_RECUSION_DEPTH 10000

// constantes pour split args
#define DEFAULT_RES_SIZE 10
#define DEFAULT_CURR_SIZE 20

#define MAIN_PHRASE 0


// expressions
#define EXPR_ENTIER 1
#define EXPR_FLOTTANT 2
#define EXPR_BOOLEEN 3
#define EXPR_CHAINE 4

// structures de données
//  * variable
#define DEFINITION_VARIABLE_AVEC_INIT 5
#define DEFINITION_VARIABLE_SANS_INIT 6
#define ACCESSION_VARIABLE 7
#define MODIFICATION_VARIABLE 8

//  * liste
#define CREATION_LISTE 9
#define ACCESSION_LISTE 10
#define MODIFICATION_LISTE 11
#define AJOUT_LISTE 12
#define SUPPRESSION_LISTE 13
#define TAILLE_LISTE 14
#define INSERTION_LISTE 41

// opérateurs
#define SOMME 15
#define DIFFERENCE 16
#define PRODUIT 17
#define QUOTIENT 18
#define QUOTIENT_ENTIER 19
#define RESTE 20
#define NEGATION_BOOLEENNE 21

// comparateurs

#define EGALITE 22
#define PLUS_GRAND 23
#define PLUS_PETIT 24
#define STRICT_PLUS_GRAND 25
#define STRICT_PLUS_PETIT 26

// conditions
#define SI_ALORS 27
#define SINON 28

// boucles
#define TANT_QUE 29
#define POUR_SANS_PAS 30
#define POUR_AVEC_PAS 31

// affichage console
#define AFFICHER_EXPR 32
#define AFFICHER_STR 33

// fonctions
#define DEFINITION_FONCTION 34
#define EXECUTION_FONCTION 35
#define RENVOI_FONCTION 36
#define APPEL_VALEUR_FONCTION 37
#define DEFINITION_FONCTION_ARGUMENT 38
#define EXECUTION_FONCTION_ARGUMENT 39
#define APPEL_VALEUR_FONCTION_ARGUMENT 40

// définitions de syntaxe
#define MAIN_PHRASE_S "*"  // fait

// expressions
#define EXPR_ENTIER_S "L'entier $?"                 // non fait
// #define EXPR_FLOTTANT_S "Le flottant $ virgule $?"  // non fait => cas particuler deux $ à récupérer
#define EXPR_FLOTTANT_S "Le flottant $?"            // workaround pour le moment
#define EXPR_BOOLEEN_S "Le booléen $?"              // fait
#define EXPR_CHAINE_S "La chaîne de caractères $?"  // non fait

// structures de données
//  * variable (fait)
#define DEFINITION_VARIABLE_AVEC_INIT_S "Soit $ *." // fait
#define DEFINITION_VARIABLE_SANS_INIT_S "Soit $."   // fait
#define ACCESSION_VARIABLE_S "La variable $?"       // fait
#define MODIFICATION_VARIABLE_S "Que $ devienne *." // fait

//  * liste (fait)
#define CREATION_LISTE_S "Soit $ une liste vide."                                     // fait
#define ACCESSION_LISTE_S "L'élément de la liste $ à l'indice *?"                     // fait
#define MODIFICATION_LISTE_S "Remplacer l'élément de la liste $ à l'indice * par *."  // fait
#define AJOUT_LISTE_S "Ajouter à la liste $ *."                                       // fait
#define SUPPRESSION_LISTE_S "Retirer de la liste $ l'élément d'indice *."             // fait (syntaxe à modifier)
#define TAILLE_LISTE_S "La taille de la liste $?"                                     // non fait
#define INSERTION_LISTE_S "Insérer l'élément * dans la liste $ à l'indice *."         // non fait


// opérateurs 
#define SOMME_S "La somme de * et de *?"                    // fait
#define DIFFERENCE_S "La différence de * et de *?"          // fait
#define PRODUIT_S "Le produit de * et de *?"                // fait
#define QUOTIENT_S "Le quotient de * par *?"                // fait
#define QUOTIENT_ENTIER_S "Le quotient entier de * par *?"  // fait
#define RESTE_S "Le reste de * par *?"                      // fait
#define NEGATION_BOOLEENNE_S "La négation booléenne de *?"  // fait

// comparateurs
#define EGALITE_S "La valeur de * est égale à la valeur de *?"                                // fait
#define PLUS_GRAND_S "La valeur de * est plus grande que la valeur de *?"                     // fait
#define PLUS_PETIT_S "La valeur de * est plus petite que la valeur de *?"                     // fait
#define STRICT_PLUS_GRAND_S "La valeur de * est strictement plus grande que la valeur de *?"  // fait
#define STRICT_PLUS_PETIT_S "La valeur de * est strictement plus petite que la valeur de *?"  // fait

// conditions
#define SI_ALORS_S "Si * alors faire:*."                        // fait
#define SINON_S "Sinon faire:*."                                // fait
#define SI_ALORS_SINON_S "Si * alors faire:* Sinon faire:*."    // à implémenter pour remplacer SINON_S

// boucles
#define TANT_QUE_S "Tant que * faire:*."  // non fait

#define POUR_SANS_PAS_S "Pour * allant de * jusqu'à * faire:*."                             // fait
#define POUR_AVEC_PAS_S "Pour * allant de * jusqu'à * en utilisant un pas de * faire:*."    // fait

// affichage console
#define AFFICHER_EXPR_S "Afficher *."            // fait
#define AFFICHER_STR_S "Afficher le message *."  // fait => à remplacer par un type de chaine de carractère pour afficher et seulement avoir AFFICHER_EXPR

// fonctions
#define DEFINITION_FONCTION_S "Soit $ une fonction qui lorsqu'elle est appelée execute:*."  // non fait
#define EXECUTION_FONCTION_S "Execute la fonction $."                                       // non fait
#define RENVOI_FONCTION_S "Renvoie *?"                                                      // fait
#define APPEL_VALEUR_FONCTION_S "La valeur renvoyée par la fonction $?"                     // non fait

#define DEFINITION_FONCTION_ARGUMENT_S "Soit $ une fonction qui lorsqu'elle est appelée avec * execute:*."  // non fait
#define EXECUTION_FONCTION_ARGUMENT_S "Execute la fonction $ avec les arguments *."                         // non fait
#define APPEL_VALEUR_FONCTION_ARGUMENT_S "La valeur renvoyée par la fonction $ avec les arguments *?"       // non fait
