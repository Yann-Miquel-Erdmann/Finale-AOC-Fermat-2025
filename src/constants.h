// constantes structures phrase_t
#define DEFAULT_PHRASE_TEXT_LEN 128
#define DEFAULT_PHRASE_ARGS 10
#define DEFAULT_PHRASE_INNER 20

// val_t type
#define INT 1
#define FLOAT 2
#define BOOL 3

// expressions
#define EXPR_ENTIER   1
#define EXPR_FLOTTANT 2
#define EXPR_BOOLEEN  3
#define EXPR_CHAINE   4

// structures de données
//  * variable
#define DEFINITION_VARIABLE_AVEC_INIT 5
#define CREATION_VARIABLE_SANS_INIT   6
#define ACCESSION_VARIABLE            7
#define MODIFICATION_VARIABLE         8

//  * liste
#define CREATION_LISTE     9
#define ACCESSION_LISTE    10
#define MODIFICATION_LISTE 11
#define AJOUT_LISTE        12
#define SUPPRESSION_LISTE  13
#define TAILLE_LISTE       14

// opérateurs
#define SOMME              15
#define DIFFERENCE         16
#define PRODUIT            17
#define QUOTIENT           18
#define QUOTIENT_ENTIER    19
#define RESTE              20
#define NEGATION_BOOLEENNE 21

// comparateurs

#define EGALITE           22
#define PLUS_GRAND        23
#define PLUS_PETIT        24
#define STRICT_PLUS_GRAND 25
#define STRICT_PLUS_PETIT 26

// conditions
#define SI_ALORS       27
#define SI_ALORS_SINON 28

// boucles
#define TANT_QUE      29
#define POUR_SANS_PAS 30
#define POUR_AVEC_PAS 31

// affichage console
#define AFFICHE_EXPR 32
#define AFFICHE_STR  33

// fonctions
#define DEFINITION_FONCTION          34
#define EXECUTION_FONCTION           35
#define RENVOI_FONCTION              36
#define APPEL_VALEUR_FONCTION        37
#define DEFINITION_FONCTION_ARGUMENT 38


// définitions de syntaxe
// expressions
#define EXPR_ENTIER_S   "L'entier *?"
#define EXPR_FLOTTANT_S "Le flottant * virgule *?"
#define EXPR_BOOLEEN_S  "Le booléen *?"
#define EXPR_CHAINE_S   "La chaîne de caractères *?"

// structures de données
//  * variable (fait)
#define DEFINITION_VARIABLE_AVEC_INIT_S "Soit * la variable initialisée à *." // -> nom de variable
#define CREATION_VARIABLE_SANS_INIT_S   "Soit * une variable." // -> nom de variable
#define ACCESSION_VARIABLE_S            "La variable *?" // -> nom de variable
#define MODIFICATION_VARIABLE_S         "Que la variable * devienne *." // -> nom de variable

//  * liste (fait)
#define CREATION_LISTE_S     "Soit * une liste vide." // -> nom de variable
#define ACCESSION_LISTE_S    "La valeur de l'élément de la liste * à l'indice *?" // -> nom de variable
#define MODIFICATION_LISTE_S "Remplacer l'élément de la liste * à l'indice * par *." // -> nom de variable
#define AJOUT_LISTE_S        "Ajouter à la liste * *." // -> nom de variable
#define SUPPRESSION_LISTE_S  "Retirer de la liste * l'élément d'indice *." // -> nom de variable
#define TAILLE_LISTE_S       "La taille de la liste *?" // -> nom de variable

// opérateurs
#define SOMME_S              15
#define DIFFERENCE_S         16
#define PRODUIT_S            17
#define QUOTIENT_S           18
#define QUOTIENT_ENTIER_S    19
#define RESTE_S              20
#define NEGATION_BOOLEENNE_S 21

// comparateurs

#define EGALITE_S           22
#define PLUS_GRAND_S        23
#define PLUS_PETIT_S        24
#define STRICT_PLUS_GRAND_S 25
#define STRICT_PLUS_PETIT_S 26

// conditions
#define SI_ALORS_S       27
#define SI_ALORS_SINON_S 28

// boucles
#define TANT_QUE_S      29
#define POUR_SANS_PAS_S 30
#define POUR_AVEC_PAS_S 31

// affichage console
#define AFFICHE_EXPR_S 32
#define AFFICHE_STR_S  33

// fonctions
#define DEFINITION_FONCTION_S               "Soit * une fonction qui lorsqu'elle est appelée execute:" // -> nom de variable
#define EXECUTION_FONCTION_S                "Execute la fonction *." // -> nom de variable
#define RENVOI_FONCTION_S                   "Renvoie *?"
#define APPEL_VALEUR_FONCTION_S             "La valeur renvoyée par la fonction *?" // -> nom de variable

// vont être compliqué avec le nombre variable d'arguments
#define DEFINITION_FONCTION_ARGUMENT_S      "Execute la fonction * avec les arguments *, ... *." // -> nom de variable
#define EXECUTION_FONCTION_ARGUMENT_S       "La valeur valeur renvoyée par la fonction * avec les arguments *, ..., *?" // -> nom variable
#define APPEL_VALEUR_FONCTION_ARGULENT_S    "Soit * une fonction qui lorsqu'elle est appelée avec *, ..., * execute:" // -> nom de variable

