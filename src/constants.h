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
// type pour une copie de pointeur
#define LISTE_P 7
#define CHAINE_DE_CHAR_P 8
// type pour les pointeurs
#define POINTEUR 9

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
#define POINTEUR_VARIABLE 53
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

// aléatoire
#define DEFINIR_SEED 50
#define NOMBRE_ALEATOIRE 51

// fonctions mathématiques
#define PARTIE_ENTIERE 52

// fonctions
#define DEFINITION_FONCTION 34
#define EXECUTION_FONCTION 35
#define RENVOI_FONCTION 36
#define APPEL_VALEUR_FONCTION 37
#define DEFINITION_FONCTION_ARGUMENT 38
#define EXECUTION_FONCTION_ARGUMENT 39
#define APPEL_VALEUR_FONCTION_ARGUMENT 40


// current next element: 59

#define DEFAULT_SEPARATOR "?,. "
#define STRING_SEPARATOR  "\""
#define NUMBER_SEPARATOR  "?,."

// définitions de syntaxe
#define MAIN_PHRASE_S "*"  // fait

// expressions
#define EXPR_ENTIER_S "L'entier $?"                 // fait
#define EXPR_FLOTTANT_S "Le flottant $?"            // fait
#define EXPR_BOOLEEN_S "Le booléen $?"              // fait
#define EXPR_CHAINE_S "La chaîne de caractères $?"  // fait
#define EXPR_RIEN_S "Rien?"                         // fait

// structures de données
//  * variable
#define DEFINITION_VARIABLE_AVEC_INIT_S "Soit $ *."  // fait
#define DEFINITION_VARIABLE_SANS_INIT_S "Soit $."    // fait
#define ACCESSION_VARIABLE_S "La variable $?"        // fait
#define MODIFICATION_VARIABLE_S "Que * devienne *."  // fait

//  * pointeur
#define POINTEUR_VARIABLE_S "Un pointeur vers *?"    // fait
#define VALEUR_POINTEE_S "La valeur pointée par *?"
#define VALEUR_FINALE_POINTEE_S "La valeur finale pointée par *?"

//  * liste
#define EXPR_LISTE_VIDE_S "La liste vide?"                                      // fait
#define ACCESSION_LISTE_S "L'élément de * à l'indice *?"                        // fait
#define MODIFICATION_LISTE_S "Remplacer l'élément de * à l'indice * par *."     // fait
#define AJOUT_LISTE_S "Ajouter à * *."                                          // fait
#define SUPPRESSION_LISTE_S "Retirer l'élément de * à l'indice *."              // fait
#define INSERTION_LISTE_S "Insérer * dans * à l'indice *."                      // fait
#define EXPR_LISTE_S "La liste $?"                                              // fait
#define EXPR_LISTE_ELEM_S "La liste des éléments *?"                            // fait

// conversions de types
#define CONVERT_TO_INT_S "La conversion en entier de *?"
#define CONVERT_TO_FLOAT_S "La conversion en flottant de *?"
#define CONVERT_TO_BOOL_S "La conversion en booléen de *?"
#define CONVERT_TO_CHAR_S "La conversion en chaîne de caractères de *?"

// opérateurs
#define SOMME_S "La somme de * et de *?"                    // fait
#define DIFFERENCE_S "La différence de * et de *?"          // fait
#define PRODUIT_S "Le produit de * et de *?"                // fait
#define QUOTIENT_S "Le quotient de * par *?"                // fait
#define QUOTIENT_ENTIER_S "Le quotient entier de * par *?"  // fait
#define RESTE_S "Le reste de * par *?"                      // fait

// opérateur booléens
#define NEGATION_BOOLEENNE_S "La négation booléenne de *?"  // fait
#define OU_S "On a * ou *?"                                 // fait
#define ET_S "On a * et *?"                                 // fait

// comparateurs
#define EGALITE_S "La valeur de * est égale à la valeur de *?"                                // fait
#define INEGALITE_S "La valeur de * est différente de la valeur de *?"                        // fait
#define PLUS_GRAND_S "La valeur de * est plus grande que la valeur de *?"                     // fait
#define PLUS_PETIT_S "La valeur de * est plus petite que la valeur de *?"                     // fait
#define STRICT_PLUS_GRAND_S "La valeur de * est strictement plus grande que la valeur de *?"  // fait
#define STRICT_PLUS_PETIT_S "La valeur de * est strictement plus petite que la valeur de *?"  // fait

// conditions
#define SI_ALORS_S "Si * alors faire:*."                      // fait
#define SI_ALORS_SINON_S "Si * alors faire:*sinon faire:*."   // fait
                         
// boucles
#define TANT_QUE_S "Tant que * faire:*."                                                  // fait
#define POUR_SANS_PAS_S "Pour $ allant de * jusqu'à * faire:*."                           // fait
#define POUR_AVEC_PAS_S "Pour $ allant de * jusqu'à * en utilisant un pas de * faire:*."  // fait
#define QUITTER_BOUCLE_S "Quitter la boucle."                                             // fait


// interractions console
#define AFFICHER_EXPR_S "Afficher *."                                           // fait
#define AFFICHER_EXPR_NO_RETURN_S "Afficher * sans retour à la ligne."          // fait
#define TYPE_EXPR_S "Le type de *?"                                             // fait
#define TAILLE_S "La taille de *?"                                              // fait
#define INPUT_INT_S "Une entrée entière?"
#define INPUT_FLOAT_S "Une entrée flottante?"
#define INPUT_BOOL_S "Une entrée booléenne?"

// aléatoire
#define DEFINIR_SEED_S "Mettre la seed aléatoire à *."  // fait
#define NOMBRE_ALEATOIRE_S "Un nombre aléatoire?"       // fait

// fonctions mathématiques
#define PARTIE_ENTIERE_S "La partie entière de *?"  // fait

// fonctions
#define DEFINITION_FONCTION_S "Soit $ une fonction qui lorsqu'elle est appelée exécute:*."    // fait
#define EXECUTION_FONCTION_S "Exécuter la fonction $."                                        // fait
#define RENVOI_FONCTION_S "Renvoyer *."                                                       // fait
#define APPEL_VALEUR_FONCTION_S "Le résultat de la fonction $?"                               // fait

#define DEFINITION_FONCTION_ARGUMENT_S "Soit $ une fonction qui lorsqu'elle est appelée avec $ exécute:*."   // fait
#define EXECUTION_FONCTION_ARGUMENT_S "Exécuter la fonction $ avec les arguments *."                         // fait
#define APPEL_VALEUR_FONCTION_ARGUMENT_S "Le résultat de la fonction $ avec les arguments *?"                // fait

#define TRY_EXCEPT_S ""

// current next error : 6

#ifndef __APPLE__
#define _Nullable
#define _Nonnull __attribute__((returns_nonnull))
#define __dead2 __attribute__((noreturn))
#define __result_use_check __attribute__((warn_unused_result))
#define __alloc_size(m) __attribute__((alloc_size(m)))
#endif

