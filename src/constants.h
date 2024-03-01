// constantes structures phrase_t
#define MAX_PHRASE_TEXT_LEN  100
#define MAX_PHRASE_ARGS      10
#define DEFAULT_PHRASE_INNER 20

// expressions
#define EXPR_ENTIER   1
#define EXPR_FLOTTANT 2
#define EXPR_BOOLEEN  3
#define EXPR_CHAINE   4

// structures de donées
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
#define SUPRESSION_LISTE   13
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
#define AFFOCHE_STR  33

// fonctions
#define DEFINITION_FONCTION          34
#define EXECUTION_FONCTION           35
#define RENVOI_FONCTION              36
#define APPEL_VALEUR_FONCTION        37
#define DEFINITION_FONCTION_ARGUMENT 38
