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
#define UNDEFINED 6
#define INT 1
#define FLOAT 2
#define BOOL 3
#define LISTE 4
#define CHAINE_DE_CHAR 5
// type pour les pointeurs
#define POINTEUR 7

// constantes pour l'interpréteur
#define MAX_RECUSION_DEPTH 10000

// constantes pour split args
#define DEFAULT_RES_SIZE 10
#define DEFAULT_CURR_SIZE 20

#define NO_ID -1
#define MAIN_PHRASE 0

// expressions
#define EXPR_ENTIER 1
#define EXPR_FLOTTANT 2
#define EXPR_BOOLEEN 3
#define EXPR_CHAINE 4
#define EXPR_RIEN 46

// structures de données
//  * variable
#define DEFINITION_VARIABLE_AVEC_INIT 5
#define DEFINITION_VARIABLE_SANS_INIT 6
#define ACCESSION_VARIABLE 7
#define MODIFICATION_VARIABLE 8

//  * pointeurs
#define POINTEUR_VERS_VALEUR 53
#define VALEUR_POINTEE 57
#define VALEUR_FINALE_POINTEE 58

//  * liste
#define EXPR_LISTE_VIDE 9
#define ACCESSION_LISTE 10
#define MODIFICATION_LISTE 11
#define AJOUT_LISTE 12
#define SUPPRESSION_LISTE 13
#define TAILLE 14
#define INSERTION_LISTE 41
#define EXPR_LISTE 42
#define EXPR_LISTE_ELEM 47

// opérateurs
#define SOMME 15
#define DIFFERENCE 16
#define PRODUIT 17
#define QUOTIENT 18
#define QUOTIENT_ENTIER 19
#define RESTE 20
#define PARTIE_ENTIERE 52

// opérateurs booléens
#define NEGATION_BOOLEENNE 21
#define OU 44
#define ET 45

// comparateurs

#define EGALITE 22
#define INEGALITE 48
#define PLUS_GRAND 23
#define PLUS_PETIT 24
#define STRICT_PLUS_GRAND 25
#define STRICT_PLUS_PETIT 26

// conditions
#define SI_ALORS 27
#define SI_ALORS_SINON 28

// boucles
#define TANT_QUE 29
#define POUR_SANS_PAS 30
#define POUR_AVEC_PAS 31
#define QUITTER_BOUCLE 49

// interractions console
#define AFFICHER_EXPR 32
#define AFFICHER_EXPR_NO_RETURN 33
#define TYPE_EXPR 43
#define INPUT_INT 54
#define INPUT_FLOAT 55
#define INPUT_BOOL 56
#define INPUT 59

// conversions de types
#define CONVERT_TO_INT 60
#define CONVERT_TO_FLOAT 61
#define CONVERT_TO_BOOL 62
#define CONVERT_TO_CHAR 63

// aléatoire
#define DEFINIR_SEED 50
#define NOMBRE_ALEATOIRE 51

// fonctions
#define DEFINITION_FONCTION 34
#define EXECUTION_FONCTION 35
#define RENVOI_FONCTION 36
#define APPEL_VALEUR_FONCTION 37
#define DEFINITION_FONCTION_ARGUMENT 38
#define EXECUTION_FONCTION_ARGUMENT 39
#define APPEL_VALEUR_FONCTION_ARGUMENT 40

// current next element: 64

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

// opérateur booléens
#define NEGATION_BOOLEENNE_S "La négation booléenne de *?"  // fait + doc
#define OU_S "On a * ou *?"                                 // fait + doc
#define ET_S "On a * et *?"                                 // fait + doc

// comparateurs
#define EGALITE_S "La valeur de * est égale à la valeur de *?"                                // fait + doc
#define INEGALITE_S "La valeur de * est différente de la valeur de *?"                        // fait + doc
#define PLUS_GRAND_S "La valeur de * est plus grande que la valeur de *?"                     // fait + doc
#define PLUS_PETIT_S "La valeur de * est plus petite que la valeur de *?"                     // fait + doc
#define STRICT_PLUS_GRAND_S "La valeur de * est strictement plus grande que la valeur de *?"  // fait + doc
#define STRICT_PLUS_PETIT_S "La valeur de * est strictement plus petite que la valeur de *?"  // fait + doc

// conditions
#define SI_ALORS_S "Si * alors faire:*."                     // fait + doc
#define SI_ALORS_SINON_S "Si * alors faire:*sinon faire:*."  // fait + doc

// boucles
#define TANT_QUE_S "Tant que * faire:*."                                                  // fait + doc
#define POUR_SANS_PAS_S "Pour $ allant de * jusqu'à * faire:*."                           // fait + doc
#define POUR_AVEC_PAS_S "Pour $ allant de * jusqu'à * en utilisant un pas de * faire:*."  // fait + doc
#define QUITTER_BOUCLE_S "Quitter la boucle."                                             // fait + doc

// interractions console
#define AFFICHER_EXPR_S "Afficher *."                                   // fait + doc
#define AFFICHER_EXPR_NO_RETURN_S "Afficher * sans retour à la ligne."  // fait + doc
#define TYPE_EXPR_S "Le type de *?"                                     // fait + doc
#define TAILLE_S "La taille de *?"                                      // fait + doc
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
#define DEFINIR_SEED_S "Mettre la seed aléatoire à *."  // fait + doc
#define NOMBRE_ALEATOIRE_S "Un nombre aléatoire?"       // fait + doc

// fonctions
#define DEFINITION_FONCTION_S "Soit $ une fonction qui lorsqu'elle est appelée exécute:*."  // fait
#define EXECUTION_FONCTION_S "Exécuter la fonction $."                                      // fait
#define RENVOI_FONCTION_S "Renvoyer *."                                                     // fait
#define APPEL_VALEUR_FONCTION_S "Le résultat de la fonction $?"                             // fait

#define DEFINITION_FONCTION_ARGUMENT_S "Soit $ une fonction qui lorsqu'elle est appelée avec $ exécute:*."  // fait
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
