# Documentation du language

## Avertissement

Le language a subi de nombreux tests, mais il reste certainement quelques bugs et contournements de syntaxe.

## Présentation générale et aspects spécifiques

L'objectif de ce language est de pouvoir écrire du code le plus clair possible.
Dans ce sens, toute instruction sera écrite dans un français correct avec des phrases claires (attention à ne pas oublier les accents :3).
Pro tip : Tout comme en français, si vous ne voulez pas avoir une phrase trop compliquée, ne la faites pas trop longue.



Première spécificité du langage : chaque phrase doit commencer par une majuscule et se terminer par un point ou point d'interrogation.
** /!\ ** Toute majuscule sera considérée comme le début d'une nouvelle phrase.  De même, un point ou un point d'interrogation sera considéré comme une fin de phrase.

La ponctuation parfaite avec de telles règles n'existe malheureusement pas. Il est donc possible que vous vous retrouviez avec plusieurs points ou points d'interrogation à la suite ou avec des phrases imbriquées dans d'autres...

Les phrases sont divisées en deux type :

* les instructions qui effectuent des actions (se terminent par un point)
* les expressions qui renvoient une valeur (se terminent par un point d'interrogation)

Vous devrez certainement écrire des nombres dans votre programme.
Les plus perspicaces l'auront peut-être deviné, il faudra les écrire en lettres, selon la règle de 1990 :

* tirets entre tous les nombres sauf autour de million et de milliard
* cent et vingt ne prennent de "s" au pluriel que s'ils ne sont pas suivis d'un nombre autre que million et milliard
* million et milliard prennent un "s" au pluriel
* mille est invariable

Les nombres à virgule devront être écrits avec tous les zéros et la virgule par exemple 2.00512 : "deux virgule zéro zéro cinq-cent-douze"

## Fonctionnement de la documentation

La syntaxes sera décrite de cette manière :

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
La présence des virgules entre les différentes expressions est à noter car celle-ci est obligatoire.

Lorsque `<mettre un truc ici>` apparaît, il faut mettre un élément (également sans les `<>`), souvent un nom de variable, de fonction ou un nombre, suivant ce qui est écrit à l'intérieur.

Les structures de données pourront vous paraître incompréhensible au premier abord mais des exemples seront donnés à la fin de la documentation.

## Les expressions de base

Les expressions de base sontcelles que vous utiliserez probablement le plus souvent
Il peut s'agir :

* D'un entier
  _expression_
  
  ```
  L'entier <nombre en toutes lettres>?
  ```
* D'un nombre à virgule (ou flottant)
  _expression_
  
  ```
  Le flottant <flottant en toutes lettres avec virgule>?
  ```
* D'un booléen
  _expression_
  
  ```
  Le booléen <vrai ou faux>?
  ```
* D'une chaîne de caractères
  _expression_
  
  ```
  La chaîne de caractères "<ce que vous voulez sauf " >"?
  ```
* De rien (ou non défini)
  le rien peut être utile dans certaines situations
  _expression_
  
  ```
  Rien?
  ```

## Les variables

Les variables sont indispensables pour stocker de l'information à réutiliser plus tard.

On peut définir une variable sans lui donner de valeur :
_instruction_

```
Soit <nom de la variable sans espace>.
```

Ou lui en assigner à sa création :
_instruction_

```
Soit <nom de la variable> {expression}.
```

Pour lui assigner une valeur une fois définie, on utilisera la syntaxe suivante qui est plus générale car elle est également utilisée pour d'autres structures de données décrites plus tard.
_instruction_

```
Que {expression: variable / liste / pointeur} devienne {expression}.
```

Pour accéder au contenu de la variable il suffit de faire
_expression_

```
La variable <nom de la variable>?
```

Exemple :

```
Que La variable x? devienne L'entier un?.
```

## Les listes

Une liste est stockée dans une variable. Le nom de cette variable devient donc le nom de la liste.

Il y a deux moyens de définir une liste :

* Comme une liste vide :
  _expression_
  
  ```
  Liste vide?
  ```
* Comme une liste d'éléments:
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

où `{expression: liste}` est souvent `La liste <nom de la liste>?`.

Plusieurs opérations sont possibles sur les listes :

* Ajouter un élément à la fin d'une liste :
  _instruction_
  
  ```
  Ajouter à {expression: liste} {expression}.
  ```

* Insérer un élément au milieu de la liste :
  _instruction_
  
  ```
  Insérer {expression} dans {expression: liste} à l'indice {expression: entier}.
  ```

* Supprimer un élément :
  _instruction_
  
  ```
  Retirer de {expression: liste} l'élément d'indice {expression: entier}.
  ```

* Remplacer un élément :
  _instruction_
  
  ```
  Remplacer l'élément de {expression: liste} à l'indice {expression: entier} par {expression}.
  ```

## Les opérateurs

Les opérateurs les plus courants sont disponibles dans ce langage, et la plupart d'entres-eux ne fonctionnent que sur les types numériques de base i.e. les entiers, les flottants et les booléens.
`{expression numérique}` désigne `{expression : entier / flottant / booléen}`

Parmi ces opérateurs, on retrouve

* La somme :
  _expression_
  
  ```
  La somme de {expression numérique} et de {expression numérique}?
  ```
* La différence :
  _expression_
  
  ```
  La différence de {expression numérique} et de {expression numérique}?
  ```
* Le produit :
  _expression_
  
  ```
  Le produit de {expression numérique} et de {expression numérique}?
  ```
* Le quotient :
  _expression_
  
  ```
  Le quotient de {expression numérique} par {expression numérique}?
  ```
* Le quotient entier :
  _expression_
  
  ```
  Le quotient entier de {expression numérique} par {expression numérique}?
  ```
* Le reste (ou modulo) :
  _expression_
  
  ```
  Le reste de {expression numérique} par {expression numérique}?
  ```
- La partie entière :
  _expression_

  ```
  La partie entière de {expression numérique}?
  ```

Il y a également quelques opérateurs booléens simples:

* La négation booléenne :
  _expression_
  
  ```
  La négation de {expression} est vérifiée?
  ```
* La conjonction booléenne :
  _expression_
  
  ```
  La conjonction de {expression} et de {expression} est vérifiée?
  ```
* La disjonction booléenne :
  _expression_
  
  ```
  La disjonction de {expression} et de {expression} est vérifiée?
  ```

## Comparateurs et structures conditionnelles

Pour vos programmes, vous aurez certainement besoin d'executer certains éléments de code seulement si une certaine condition est vérifiée.
Pour cela, vous pouvez choisir parmi deux structures conditionnelles :

* Si alors :
  _instruction_
  
  ```
  Si {expression} alors:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
  .
  ```
  
  ** /!\ ** Ne pas oublier le point à la fin de la condition.
  Note : La tabulation n'est pas obligatoire mais permet d'augmenter la lisibilité.

* Si alors sinon :
  _instruction_
  
  ```
  Si {expression} alors:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
  sinon:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
  .
  ```
  
  Note : Le "sinon" n'a pas de majuscule ! Faites attention.

Maintenant passons aux comparateurs.
Pour comparer, vous aurez à votre disposition :

* L'égalité :
  _expression_
  
  ```
  La valeur de {expression} est égale à la valeur de {expression}?
  ```
* La non égalité :
  _expression_
  
  ```
  La valeur de {expression} est différente de la valeur de {expression}?
  ```
* L'inégalité inférieure :
  _expression_
  
  ```
  La valeur de {expression} est plus petite que la valeur de {expression}?
  ```
* L'inégalité stricte inférieure :
  _expression_
  
  ```
  La valeur de {expression} est strictement plus petite que la valeur de {expression}?
  ```
* L'inégalité supérieure :
  _expression_
  
  ```
  La valeur de {expression} est plus grande que la valeur de {expression}?
  ```
* L'inégalité stricte supérieure :
  _expression_
  
  ```
  La valeur de {expression} est strictement plus grande que la valeur de {expression}?
  ```

## Boucles

Écrire peut être rapidement fatiguant, surtout s'il s'agit de lignes plutôt répétitives.
Pour régler ce problème, vous aurez plusieurs boucles à votre disposition :

* Tant que :
  _instruction_
  
  ```
  Tant que {expression}:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
  .
  ```
* Pour :
  _instruction_
  
  ```
  Pour {nom de la variable} allant de {expression numérique} jusqu'à {expression numérique (cette valeur ne sera pas prise)} faire:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
  .
  ```
* Pour avec pas :
  _instruction_
  
  ```
  Pour {nom de la variable} allant de {expression numérique} jusqu'à {expression numérique} en utilisant un pas de {expression numérique} faire:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
  .
  ```
  
  Vous pourrez également sortir d'une de ces boucles à tout moment avec l'instruction
  Quitter boucle :
  _instruction_
  
  ```
  Quitter la boucle.
  ```

## Interactions avec la console

En cas d'erreur dans votre code, il est pratique de pouvoir afficher les éléments qui peuvent poser problème.

Il est possible d'afficher une expression dans la console :
_instruction_

```
Afficher {expression1}, {expression2}, ... {expression n}.
```

Mais aussi sans retours à la ligne :
_instruction_

```
Afficher {expression1}, {expression2}, ... {expression n} sans retour à la ligne.
```

On peut également récupérer la taille d'une liste ou d'une chaîne de caractère :
_expression_

```
La taille de {expression : chaîne de caractère/liste}?
```

Pour récupérer le type de d'une expression sous forme de chaîne de caractère :
_expression_

```
Le type de {expression}?
```

Il est possible de récupérer des entrées de l'utilisateur sous différents types :

* Entier :
  _expression_
  
  ```
  Une entrée entière?
  ```

* Flottant :
  _expression_
  
  ```
  Une entrée flottante?
  ```

* Booléen :
  _expression_
  
  ```
  Une entrée booléenne?
  ```

* Chaîne de caractères :
  _expression_
  
  ```
  Une entrée?
  ```

## Aléatoire

Quoi de mieux qu'un peu d'aléatoire pour pimenter votre code ?
Vous avez accès à deux fonction manipulant l'aléatoire :

* Nombre aléatoire (de 0 jusqu'à très très grand) :
  _expression_
  
  ```
  Un nombre aléatoire?
  ```

* Seed :
  Vous pouvez mettre la seed à la valeur que vous voulez pour obtenir un résultat différent (la seed initiale est à 0)
  _instruction_
  
  ```
  Mettre la seed aléatoire à {expression : entier}.
  ```

## Conversion de types

La partie entière vous a déjà été introduite précédemment, ici vous pourrez convertir non seulement les types numériques mais également les chaînes de caractères en nombres ou les nombres en chaînes de caractères.
En cas d'échec de conversion, l'expression renvoyée est `Rien?` de type `undefined`.

* Conversion en entier :
  Si l'entrée est une chaîne, renvoie l'entier associé à l'entier écrit en lettres
  _expression_
  
  ```
  La conversion en entier de {expression : chaîne de caractères}?
  ```

* Conversion en flottant :
  Si l'entrée est une chaîne, renvoie le flottant associé au flottant écrit en lettres
  _expression_
  
  ```
  La conversion en flottant de {expression : chaîne de caractères}?
  ```

* Conversion en booléen :
  Si l'entrée est une chaîne, renvoie faux si la chaîne est "faux" ou si la chaîne est vide, vrai sinon
  _expression_
  
  ```
  La conversion en booléen de {expression}?
  ```

* Conversion en chaîne de caractères :
  _expression_
  
  ```
  La conversion en chaîne de caractères de {expression}?
  ```

## Pointeurs

Pour ceux qui voudraient optimiser leur programme, vous pouvez utiliser des pointeurs.
Par exemple lors du passage d'arguments volumineux dans des fonctions comme des grosses listes (ou juste pour le fun)

Pour créer un pointeur :
_expression_

```
Un pointeur vers {expression}?
```

Créer un pointeur c'est bien mais pouvoir accéder à sa valeur c'est mieux.
On peut accéder à la valeur d'un pointeur de deux manières différentes :

* la valeur pointée :
  _expression_
  
  ```
  La valeur pointée par {expression : pointeur}?
  ```
* la valeur finale pointée :
  _expression_
  
  ```
  La valeur finale pointée par {expression : pointeur}?
  ```
  
  Si a->b->c avec c = 2, la valeur pointée par a est un pointeur alors que la valeur finale pointée par a est 2.

Si vous vous souvenez, les pointeurs ont été abordés lors de la modification de valeurs.
En effet, la modification de la valeur pointée par un pointeur se fait avec "Que ... devienne ...".

Exemple :

```
Soit x L'entier un?.
Soit y Un pointeur vers La variable x??.
Que La valeur pointée par La variable y?? devienne L'entier deux?.
```

Permet de stocker la valeur 2 dans la variable x sans avoir à passer par son nom. 

## Fonctions

Les fonctions sont très utiles pour exécuter un morceau de programme utilisé régulièrement.
Une fonction se définit de la façon suivante :
_instruction_

```
Soit <nom de la fonction> une fonction qui lorsqu'elle appelée exécute:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
.
```

Elles peuvent également être définies avec des arguments :
_instruction_

```
Soit <nom de la fonction> une fonction qui lorsqu'elle appelée avec <nom de la variable 1>, ..., <nom de la variable n> exécute:
    {instruction 1}
    {instruction 2}
    ...
    {instruction n}
.
```

Pour exécuter une fonction :
_instruction_

```
Exécuter la fonction <nom de la fonction>.
```

Et avec des arguments :
_instruction_

```
Exécuter la fonction <nom de la fonction> avec les arguments {expression 1}, ..., {expression n}.
```

Il peut s'avérer utile de pouvoir renvoyer une valeur dans une fonction et de la récupérer.
Pour renvoyer une valeur :
_instruction_

```
Renvoyer {expression}.
```

Pour récupérer la valeur :
_expression_

```
Le résultat de la fonction <nom de la fonction>?
```

Et avec des arguments :
_expression_

```
Le résultat de la fonction <nom de la fonction> avec les arguments {expression 1}, ..., {expression n}?
```

## Commentaires

Les commentaires sont parfois utiles pour s'y retrouver.
Toute phrase écrite entre parenthèses sera ignoré.:

Exemple :

```
(Ceci est un commentaire)
```

## Exemples divers

Nous avons répertorié ici quelques exemples de codes simples pour que vous puissiez vous familiariser avec le langage en le lisant ou en l'exécutant.

Test pair/ impair

```
(Test pair / impair avec un si)
Soit x L'entier un?.
Si La valeur de Le reste de La variable x? par L'entier deux?? est égale à la valeur de L'entier zéro?? alors:
    Afficher La chaîne de caractères "Pair"?.
sinon:
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

Boucle tant que avec sortie forcée de boucle et assignation variable

```
Soit x L'entier un?.
(Code illégal mais il fonctionne)
Tant que Le booléen vrai?:
    Afficher La variable x?.
    Si La valeur de La variable x? est égale à la valeur de L'entier dix?? alors:
        Quitter la boucle.
    .
    Que La variable x? devienne La somme de La variable x? et de L'entier un??.
.
```

Fonctions, récursivité et renvoi de valeurs
exemple de la fonction factorielle

```
(implémentation de la fonction factorielle de manière récursive
/!\ La récursion est considérée comme infinie au delà de 10000 appels récursifs)
Soit factorielle la fonction qui lorsqu'elle est appelée avec n exécute:
    Si La valeur de La variable n? est plus petite que la valeur de L'entier zéro?? alors:
        Renvoyer L'entier un?.
    .
    Renvoyer Le produit de La variable n? et de Le résultat de la fonction factorielle avec les arguments La différence de La variable n? et de L'entier un????.
.

( 5! = 1x2x3x4x5 = 6x20 = 120 )
Afficher Le résultat de la fonction factorielle avec les arguments L'entier cinq??.
```

Stockage dans une liste de valeurs entrées par l'utilisateur

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
Soit y Un pointeur vers La variable x??.
Que La valeur pointée par La variable y?? devienne L'entier un?.
Afficher La variable x?.

(ne modifie pas la valeur pointée)
Soit a L'entier un?.
Soit b Un pointeur vers La variable a??.
Soit c La valeur pointée par La variable b??.
Que La variable c? devienne L'entier deux?.
Afficher La chaîne de caractères "a = "?, La variable a?. 
Afficher La chaîne de caractères "c = "?, La variable c?. 
```
