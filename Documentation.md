# Documentation du language

## Disclaimer
Le language a été beaucoup testé mais il reste sûrement des bugs et de petits contournements de syntaxe.

## Présentation générale et aspects spécifiques
Le language a été créé dans le but d'avoir un code le plus clair possible.
Dans ce sens, tout sera écrit en français avec des phrases (attention à ne pas oublier les accents :3).
Pro tip: Comme en français, si vous ne voulez pas avoir une phrase trop compliquée, ne la faites pas trop longue.

Le language à d'abord une spécificité: toutes les phrases commencent une majuscule et se terminent par un point.
Si vous voulez récupérer une valeur, à la place d'un point à la fin, il faudra mettre un point d'interrogation comme si vous posiez une question.
**/!\ **toute majuscule sera considérée comme le début d'une nouvelle phrase, elles ne doivent donc avoir que cet usage. Même avertissement pour le point et le point d'interrogation.
Malheureusement la ponctuation parfaite avec de telles règles n'existe pas, il est donc possible que vous vous retrouviez avec plusieurs points ou points d'interrogation d'affilés
ou des majuscules au milieu de phrases.

Les phrases sont divisées en deux type:
* les instructions qui effectuent des actions (se terminent par un point)
* les expressions qui renvoient une valeur (se terminent par un point d'interrogation)
Il sera précisé plus tard lorsqu'une phrase est une instruction où une expression

Vous aurez certainement à écrire des nombres dans votre programme.
Les plus perspicaces l'auront peut-être deviné, il faudra les écrire en lettre, selon la règle de 1990:
* tirets entre tous les nombres sauf autour de million et de milliard
* cent et vingt ne prennent de "s" au pluriel que s'ils ne sont pas suivi d'un nombre autre que million et milliard
* million et milliard prennent un "s" au pluriel
* mille est invariable

Les nombres à virgule devront être écrits avec tous les zéro et la virgule par exemple 2.00512: "deux virgule zéro zéro cinq-cent-douze"

## Fonctionnement de la documentation
Le syntaxes seront décrites de la manière:
```
Ceci est du code avec une {expression} puis parfois une {instruction}.
```
`{expression}` signifie que la syntaxe requiert une expression (sans les `{}`) et `{instruction}` requiert une instruction.
Si un type de base est présent aux côtés du mot expression, cela signifie que le type est à respecter.

Si 
```
{instruction 1}
{instruction 2}
...
{instruction n}
```
apparaît, cela veut dire qu'il faut mettre au moins une instruction mais qu'il est possible d'en mettre autant que l'on veut.

Dans le cas de
```
{expression 1}, {expression 2}, ..., {expression n}
```
il faut mettre au moins une expression mais il est à nouveau possible d'en mettre autant que l'on veut.
Il est à noter la présence des virgules entre les différentes expressions qui est obligatoire.

Lorsque `<mettre un truc ici>` apparaît, il faut mettre un élément (également sans les `<>`), souvent un nom de variable, de fonction ou un nombre,
en suivant ce qui est écrit à l'intérieur.

Les structures données pourrons vous paraître incompréhensible au premier abord mais des exemples seront donnés à la fin de la documentation.

## Les expression de base
Les expressions base sont les expressions que vous utiliserez probablement le plus souvent
Il peut s'agir:

* d'un entier
_instruction_
```
L'entier <nombre en toutes lettres>?
```
* d'un nombre à virgule (ou flottant)
_instruction_
```
Le flottant <flottant en toutes lettre avec virgule>?
```
* d'un booléen
_instruction_
```
Le booléen <vrai ou faux>?
```
* d'une chaîne de caractères
_instruction_
```
La chaîne de caractères "<ce que vous voulez sauf " >"?
```
* du rien (ou non définit)
le rien peut être utile dans certaine situation que vous pourrez trouver
_instruction_
```
Rien?
```

## Les variables
Les variables sont indispensables pour stocker de l'information à réutiliser plus tard.

On peut définir une variable sans lui donner de valeur:
_instruction_
```
Soit <nom de la variable sans espace>.
```

Ou lui en assigner à sa création:
_instruction_
```
Soit <nom de la variable> {expression}.
```

Pour lui assigner une valeur, on utilisera la syntaxe suivante.
Elle est plus générale car elle est également utilisée pour d'autres structures de données décrites plus tard.
_instruction_
```
Que {expression: variable / liste / pointeur} devienne {expression}.
```
exemple:
```
Que La variable x? devienne L'entier un?.
```

Pour accéder au contenu de la variable il suffit de faire
_expression_
```
La variable <nom de la variable>?
```

## Les liste
Les liste, un incontournable objet de la programmation que se soit pour stocker des valeurs, d'autres liste ou tous simplement pour les trier.
La liste est définie dans une variable.

Il y a deux moyens de définir une liste:
* comme une liste vide:
_expression_
```
Liste vide?
```
* comme une liste d'éléments:
_expression_
```
La liste des éléments {expression 1}, {expression 2}, ..., {expression n}.
```

Une fois stockée dans une variable, on peut y accéder avec
_expression_
```
La liste <nom de la liste>?
```

On peut accéder à un élément de la liste avec
_expression_
```
L'élément de {expression: liste} à l'indice {expression: entier}?
```
où `{expression: liste}` est souvent `La liste <nom de la liste>`.

Plusieurs opérations sont possibles sur les listes:
* Ajouter des éléments à la fin de la liste:
_instruction_
```
Ajouter à {expression: liste} {expression}.
```
utile a savoir, ici, `{expression: liste}` comme toutes celles des instructions précédentes et suivantes
peuvent être remplacés par `La liste <nom de la liste>` ou `L'élément de {expression: liste} à l'indice {expression: entier}?`
si celui-ci est une liste
exemple:
```
Ajouter à L'élément de La liste l? à l'indice L'entier un?? L'entier quatre?.
```
ajoute 4 au premier élément de la liste l.

* Insérer des éléments au milieu de la liste:
_instruction_
```
Insérer {expression} dans {expression: liste} à l'index {expression: entier}.
```

* Supprimer un élément:
_instruction_
```
Retirer de {expression: liste} l'élément d'indice {expression: entier}.
```

* Remplacer un élément:
_instruction_
```
Remplacer l'élément de {expression: liste} à l'indice {expression: entier} par {expression}.
```

## Les opérateurs
Il a a différents opérateurs qui vous permettrons d'effectuer toute sorte de calculs sur les types de bases
La plupart d'entre eux ne fonctionnent que sur les types numériques de base i.e. les entiers, les flottants et les booléens.
`{expression numérique}` désigne `{expression : entier / flottant / booléen}`

Parmi ces opérateurs, on retrouve
* la somme:
_expression_
```
La somme de {expression numérique} et de {expression numérique}?
```
* la différence:
_expression_
```
La différence de {expression numérique} et de {expression numérique}?
```
* le produit:
_expression_
```
Le produit de {expression numérique} et de {expression numérique}?
```
* le quotient:
_expression_
```
Le quotient de {expression numérique} par {expression numérique}?
```
* le quotient entier:
_expression_
```
Le quotient entier de {expression numérique} par {expression numérique}?
```
* Le reste (ou modulo):
_expression_
```
Le reste de {expression numérique} par {expression numérique}?
```

Il pourra vous être utile de pouvoir utiliser la partie entière pour arrondir des flottants:
_expression_
```
La partie entière de {expression numérique}?
```

Il y a également quelques opérateurs booléens simples:
* La négation booléenne:
_expression_
```
La négation booléenne de {expression}?
```
* Le Et booléen:
_expression_
```
On a {expression} et {expression}?
```
* Le Ou booléen:
_expression_
```
On a {expression} ou {expression}?
```

## Comparateurs et structures conditionnelles
Pour vos programmes, vous aurez certainement besoin d'executer certains éléments de code seulement si une certaine condition est vérifiée.
Pour cela, vous pouvez choisir parmi deux structures conditionnelles:
* Si alors:
_instruction_
```
Si {expression} alors faire:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
.
```
**/!\ **ne pas oublier le point à la fin de la condition.
Note: La tabulation n'est pas obligatoire mais permet d'augmenter la lisibilité.

* Si alors sinon:
_instruction_
```
Si {expression} alors faire:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
sinon faire:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
.
```
Note: vous porterez une attention particulière au sinon qui n'a pas de majuscule.

Les comparateurs vous seront utile, vous l'aurez deviné, pour comparer.
Pour comparer, vous aurez à votre disposition:
* L'égalité:
_expression_
```
La valeur de {expression} est égale à la valeur de {expression}?
```
* La non égalité:
_expression_
```
La valeur de {expression} est différente de la valeur de {expression}?
```
* L'inégalité inférieur:
_expression_
```
La valeur de {expression} est plus petite que la valeur de {expression}?
```
* L'inégalité strict inférieur:
_expression_
```
La valeur de {expression} est strictement plus petite que la valeur de {expression}?
```
* L'inégalité supérieur:
_expression_
```
La valeur de {expression} est plus grande que la valeur de {expression}?
```
* L'inégalité strict supérieur:
_expression_
```
La valeur de {expression} est strictement plus grande que la valeur de {expression}?
```

## Boucles
Écrire peut être rapidement fatiguant, surtout s'il s'agit de lignes plutôt répétitives.
Pour régler ce problème, vous aurez plusieurs boucles à votre disposition:
* Tant que:
_instruction_
```
Tant que {expression} faire:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
.
```
* Pour:
_instruction_
```
Pour <nom de la variable> allant de {expression numérique} jusqu'à {expression numérique} faire:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
.
```
* Pour avec pas:
_instruction_
```
Pour <nom de la variable> allant de {expression numérique} jusqu'à {expression numérique} en utilisant un pas de {expression numérique} faire:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
.
```
Avec ces boucles, vous pourrez également en sortir à tout moment avec l'instruction
Quitter boucle:
_instruction_
```
Quitter la boucle.
```

## Interactions avec la console
Il pourra en cas d'erreur dans votre code être pratique de pouvoir afficher les éléments qui pourraient poser problème.

On peut tout d'abord afficher toute expression dans la console:
_instruction_
```
Afficher {expression1}, {expression2}, ... {expression n}.
```
Mais aussi sans retours à la ligne:
_instruction_
```
Afficher {expression1}, {expression2}, ... {expression n} sans retour à la ligne.
```

On peut également récupérer la taille d'une liste ou d'une chaîne de caractère:
_expression_
```
La taille de {expression : chaîne de caractère/liste}?
```
On peut également récupérer le type de d'une expression sous forme de chaîne de caractère:
_expression_
```
Le type de {expression}?
```

On peut également récupérer des entrées de l'utilisateur sous différents types:
* Entier:
_expression_
```
Une entrée entière?
```
* Flottant:
_expression_
```
Une entrée flottante?
```

* Booléen:
_expression_
```
Une entrée booléenne?
```

* Chaîne de caractères:
_expression_
```
Une entrée?
```

## Aléatoire
Quoi de mieux que d'un peu d'aléatoire pour pimenter votre code?
Vous avez accès à deux fonction pour manipuler l'aléatoire:

* Nombre aléatoire:
_expression_
```
Un nombre aléatoire?
```

* Seed:
Vous pouvez mettre la seed a la valeur que vous voulez pour obtenir un résultat différent (seed initiale est a 0)
_instruction_
```
Mettre la seed aléatoire à {expression : entier}.
```

## Conversion de types
La partie entière vous a déjà été introduite précédemment, ici vous pourrez convertir non seulement les types numériques mais également
les chaînes de caractères en nombre ou les nombres en chaînes de caractères.
En cas d'échec de conversion, l'expression renvoyée est `Rien ?` de type `undefined`.

* Conversion en entier:
Si l'entrée est une chaîne, renvoie l'entier associé au nombre en lettres
_expression_
```
La conversion en entier de {expression}?
```

* Conversion en flottant:
Si l'entrée est une chaîne, renvoie le flottant associé au nombre en lettres
_expression_
```
La conversion en flottant de {expression}?
```

* Conversion en booléen:
Si l'entrée est une chaîne, renvoie faux si la chaîne est "faux" ou si la chaîne est vide, vrai sinon
_expression_
```
La conversion en booléen de {expression}?
```

* Conversion en chaîne de caractères:
_expression_
```
La conversion en chaîne de caractères de {expression}?
```

## Pointeurs
Pour ceux qui voudraient optimiser leur programme, vous pourrez utiliser des pointeurs.
(du moins lors du passage d'arguments volumineux dans des fonction comme des grosses liste ou juste pour le fun)

Pour créer un pointeur:
_expression_
```
Un pointeur vers {expression}?
```

Créer un pointeur c'est bien mais pouvoir accéder à sa valeur c'est mieux.
On peut accéder à la valeur d'un pointeur de deux manières différentes:
* la valeur pointée:
_expression_
```
La valeur pointée par {expression : pointeur}?
```
* la valeur finale pointée:
_expression_
```
La valeur finale pointée par {expression : pointeur}?
```
Si a->b->c avec c = 2, la valeur pointée par a est un pointeur alors que la valeur finale pointée par a est 2.

Si vous vous souvenez, les pointeurs ont été abordés lors de la modification de valeur.
En effet, la manière de modifier la valeur pointée par le pointeur se fait avec la modification.
Exemple:
```
Soit x L'entier un?.
Soit y Un pointeur vers La variable x??.
Que La valeur pointée par La variable y?? devienne L'entier deux?.
```
Permet de stocker la valeur 2 dans la variable x sans avoir à passer par son nom. 

## Fonctions
Les fonctions sont très utiles pour exécuter un morceau de programme souvent réutilisé à différents endroits du votre code.
Une fonction se définit de la manière suivante:
_instruction_
```
Soit <nom de la fonction> la fonction qui lorsqu'elle appelée exécute:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
.
```
Elles peuvent être également définies avec des arguments:
_instruction_
```
Soit <nom de la fonction> la fonction qui lorsqu'elle appelée avec <nom de la variable 1>, ..., <nom de la variable n> exécute:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
.
```

Pour exécuter une fonction:
_instruction_
```
Exécuter la fonction <nom de la fonction>.
```
Et avec des arguments:
_instruction_
```
Exécuter la fonction <nom de la fonction> avec les arguments {expression 1}, ..., {expression n}.
```

Il peut s'avérer utile de pouvoir renvoyer une valeur dans une fonction et de pouvoir la récupérer.
Pour renvoyer une valeur:
_instruction_
```
Renvoyer {expression}.
```
Pour récupérer la valeur:
_expression_
```
Le résultat de la fonction <nom de la fonction>?
```
Et avec des arguments:
_expression_
```
Le résultat de la fonction <nom de la fonction> avec les arguments {expression 1}, ..., {expression n}?
```

## Exemples
Nous avons répertorié ici quelques exemples de codes simples pour que vous puissiez comprendre le code en le lisant ou en l'exécutant.

Test pair/ impair:
```
(Test pair / impair avec un si)
Soit x L'entier un?.
Si La valeur de Le reste de La variable x? par L'entier deux?? est égale à la valeur de L'entier zéro?? alors faire:
    Afficher La chaîne de caractères "Pair"?.
sinon faire:
    Afficher La chaîne de caractères "Impair"?.
.
```

Afficher plusieurs éléments sur la même ligne et parcourir une liste avec un pour
```
Soit l La liste des éléments L'entier zéro?, L'entier un?, L'entier deux?, L'entier trois??.

(parcours de la liste)
Pour i allant de L'entier zéro? jusqu'à La taille de La liste l?? faire:
    Afficher L'élément de La liste l? à l'indice La variable i??, La chaîne de caractères " "? sans retour à la ligne.
.
Afficher La chaîne de caractères ""?.

(ou alors)
Afficher L'entier zéro?, L'entier un?, L'entier deux?, L'entier trois?.
```

Boucle tant que et quitter la boucle et assignation variable
```
Soit x L'entier un?.
( pas bien mais contrôlé ici)
Tant que Le booléen vrai? faire:
    Afficher La variable x?.
    Si La valeur de La variable x? est égale à la valeur de L'entier dix?? alors faire:
        Quitter la boucle.
    .
    Que La variable x? devienne La somme de La variable x? et de L'entier un??.
.
```

Fonctions, récursivité et renvoi de valeurs
exemple de la fonction factorielle
```
(implémentation de la fonction factorielle de manière récursive
/!\ La réccursion est considérée comme infinie au dessus de 10000 de profondeur)
Soit factorielle la fonction qui lorsqu'elle est appelée avec n exécute:
    Si La valeur de La variable n? est plus petite que la valeur de L'entier zéro?? alors faire:
        Renvoyer L'entier un?.
    .
    Renvoyer Le produit de La variable n? et de Le résultat de la fonction factorielle avec les arguments La différence de La variable n? et de L'entier un????.
.

( 5! = 1x2x3x4x5 = 6x20 = 120 )
Afficher Le résultat de la fonction factorielle avec les arguments L'entier cinq??.
```

Pour traiter les entées d'un programme qui prendrait un nombre d'entrées puis stocke ces entrées dans une liste pour traitement ultérieur
```
Soit nb_entrées Une entrée entière?.
Soit entrées La liste vide?.
Pour i allant de L'entier zéro? jusqu'à La variable nb_entrées? faire:
    Ajouter à La liste entrées? Une entrée entière?.
.

Afficher La liste entrées?.
```
Avec l'entrée
```
cinq
un
deux
trois
quatre
cinq
```
le programme renvoie
```
[un, deux, trois, quatre, cinq]
```

Exemple avec des pointeurs
```
(modifie la valeur pointée)
Soit x L'entier zéro?.
Soit y Un pointeur vers La variable x?.
Que La valeur pointée par La variable y?? devienne L'entier un?.
Afficher La variable x?.

(ne modifie pas la valeur pointée)
Soit a L'entier un?.
Soit b Un pointeur vers la variable a?.
Soit c La valeur pointée par La variable b??.
Que La variable c? devienne L'entier deux?.
Afficher La chaîne de caractères "a = "?, La variable a?. 
Afficher La chaîne de caractères "c = "?, La variable c?. 
```
