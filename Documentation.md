# Documentation du language

## Disclamer
Le language n'a pas encore été totalement testé, il reste surement des bugs et de petits contournements de syntaxe.

## Présentation générale et aspects spécifiques

Le language a été créé dans le but d'avoir un code le plus clair possible.
Dans ce sens, tout sera écrit en français avec des phrases (attention à ne pas oublier les accents :3).
Pro tip: Comme en français, si vous ne voulez pas avoir une phrase trop compliquée, ne la faites pas trop longue.

Le language à d'abord une spécificité: toutes les phrases commencent une majuscule et se terminent par un point.
Si vous voulez récupérer une valeur, à la place d'un point à la fin, il faudra mettre un point d'interrogation comme si vous posiez une question.
/!\ toute majuscule sera considérée comme le début d'une nouvelle phrase, elles ne doivent donc avoir que cet usage. Même avertissement pour le point et le point d'interrogation.
Malheureusement la ponctuation parfaite avec de telles règles n'existe pas, il est donc possible que vous vous retrouviez avec plusieurs points ou points d'interrogation d'affilés
ou des majuscules au milieu de phrases.

Les phrases sont divisées en deux type:
* les instructions qui effectuent des actions (se terminent par un point)
* les expressions qui renvoient une valeur (se terminent par un point d'interrogation)
Il sera précisé plus tard lorsq'une phrase est une instruction où une expression

Vous aurez certainement à écrire des nombres dans votre programme.
Les plus perspicaces l'auront peut-être deviné, il faudra les écrire en lettre, selon la règle de 1990:
* tirets entre tous les nombres sauf autour de millions et de milliards
* cent et vingt ne prennent de "s" au pluriel que s'ils ne sont pas suivi d'un nombre autre que million et milliard
* mille est invariable

Les nombres à virgule devront être écrits par exemple 2.005: "deux virgule zéro zéro cinq"

## Fonctionnement de la documentation
Le syntaxes seront décrites de la manière:
```
Ceci est du code avec {expression} puis parfois {instruction}.
```
{expression} signifie que la syntaxe requiert une expression et {instruction} requiert une instruction.
Si un type de base est présent aux côtés du mot expression, cela signifie que le type est à respecter.

Si 
```
{instruction 1}.
{instruction 2}.
...
{instruction n}.
```
apparait, cela veut dire qu'il faut mettre au moins une instruction mais qu'il est possible d'en mettre autant que l'on veut.

Dans le cas de
```
{expression 1}, {expression 2}, ..., {expression n}
```
il faut mettre au moins une expression mais il est à nouveau possible d'en mettre autant que l'on veut.
Il est à noter la présence des virgules entre les différentes expressions qui est obligatoire.

Finalement si aucun des cas suivants n'est entre les {}, il suffit de suivre ce qui est écrit à l'intérieur.

## Les expression de base
Les expressions base sont les expressions que vous utiliserez probablement le plus souvent\
Il peut s'agir:

* d'un entier
```
L'entier {nombre en toutes lettres}?
```
* d'un nombre à virgule (ou flottant)
```
Le flottant {flottant en toutes lettre avec virgule}?
```
* d'un booléen
```
Le booléen {vrai/faux}?
```
* d'une chaîne de carractères
```
La chaîne de caractères "{ce que vous voulez sauf "}"?
```
* du rien (ou non définit)
le rien peut être utile dans certaine situation que vous pourrez trouver
```
Rien?
```

## Les variables
Les variables sont indispensables pour stocker de l'information à réutiliser plus tard.

On peut définir une variable sans lui donner de valeur:
_instruction_
```
Soit {nom de la variable sans espace}.
```

Ou avec une valeur
_instruction_
```
Soit {nom de la variable} {expression}.
```

Pour lui assigner une valeur,
_instruction_
```
Que {nom de la variable} devienne {expression}.
```

Pour accéder au contenu de la variable il suffit de faire
_expression_
```
La variable {nom de la variable}?
```

## Les liste
Les liste, un incontournable objet de la programmation que se soit pour stocker des valeurs, d'autres liste ou tous simplement pour les trier.
La liste est définie dans une variable.

Il y a deux moyens de définir une liste:
* comme une liste vide:\
_expression_
```
Liste vide?
```
* comme une liste d'éléments:\
_expression_
```
La liste des éléments {expression 1}, {expression 2}, ..., {expression n}.
```

Plusieurs opérations sont possibles sur les listes:
* Ajouter des éléments à la fin de la liste:\
_instruction_
```
Ajouter à {expression: liste} {expression}.
```

* Insérer des éléments au milieu de la liste:\
_instruction_
```
Insérer {expression} dans {expression: liste} à l'index {expression: entier}.
```

* Supprimer un élément:\
_instruction_
```
Retirer de {expression: liste} l'élément d'indice {expression: entier}.
```

* Remplacer un élément:\
_instruction_
```
Remplacer l'élément de {expression: liste} à l'indice {expression: entier} par {expression}.
```

On peut également accéder à un élément de la liste avec\
_expression_
```
L'élément de {expression: liste} à l'indice {expression: entier}?
```

Finalement, on peut accéder à la liste en entier avec\
_expression_
```
La liste {nom de la liste}?
```

## Les opérateurs
Il a a différents opérateurs qui vous permetterons d'effectuer toute sorte de calculs sur les types de bases
La plupart d'entre eux ne fonctionnent que sur les types numériques de base i.e. les entiers, les flottants et les booléens.

Parmis ces opérateurs, on retrouve
* la somme:\
_expression_
```
La somme de {expression numérique} et de {expression numérique}?
```
* la différence:\
_expression_
```
La différence de {expression numérique} et de {expression numérique}?
```
* le produit:\
_expression_
```
Le produit de {expression numérique} et de {expression numérique}?
```
* le quotient:\
_expression_
```
Le quotient de {expression numérique} par {expression numérique}?
```
* le quotient entier:\
_expression_
```
Le quotient entier de {expression numérique} par {expression numérique}?
```
* Le reste (ou modulo):\
_expression_
```
Le reste de {expression numérique} par {expression numérique}?
```
Il y a également quelques opérateurs booléens simples:
* La négation booléenne:\
_expression_
```
La négation booléenne de {expression}?
```
* Le Et booléen:\
_expression_
```
On a {expression} et {expression}?
```
* Le Ou booléen:\
_expression_
```
On a {expression} ou {expression}?
```

## Comparateurs et structures conditionnelles
Pour vos programmes, vous aurez certainement besoin d'executer certains éléments de code seulement si une certaine condition est vérifiée.
Pour cela, vous pouvez choisir parmis deux structures conditionnelles:
* Si alors:\
_instruction_
```
Si {expression} alors faire:
    {instruction 1}.
    {instruction 2}.
    ...
    {instruction n}.
.
```
/!\ ne pas oublier le point à la fin de la condition.
Note: La tabulation n'est pas obligatoire mais permet d'augmenter la lisibilité.
* Si alors sinon:\
_instruction_
```
Si {expression} alors faire:
    {instruction 1}.
    {instruction 2}.
    ...
    {instruction n}.
sinon faire:
    {instruction 1}.
    {instruction 2}.
    ...
    {instruction n}.
.
```
Note: vous porterez une attention particulière au sinon qui n'a pas de majuscule.

Les comparateurs vous seront utile, vous l'aurez deviné, pour comparer.
Pour comparer, vous aurez à votre disposition:
* L'égalité:\
_expression_
```
La valeur de {expression} est égale à la valeur de {expression}?
```
* L'inégalité inférieur:\
_expression_
```
La valeur de {expression} est plus petite que la valeur de {expression}?
```
* L'ingalité stricte inférieur:\
_expression_
```
La valeur de {expression} est strictement plus petite que la valeur de {expression}?
```
* L'inégalité supérieur:
_expression_
```
La valeur de {expression} est plus grande que la valeur de {expression}?
```
* L'inégalité stricte supérieur:
_expression_
```
La valeur de {expression} est strictement plus grande que la valeur de {expression}?
```

## Boucles
Écrire peut être rapidement fatiguant, surtout s'il sagit de lignes plutôt répétitives.
Pour régler ce problème, vous aurez plusieurs boucles à votre disposition:
* Tant que:\
_instruction_
```
Tant que {expression} faire:
    {instruction 1}.
    {instruction 2}.
    ...
    {instruction n}.
.
```
* Pour:\
_instruction_
```
Pour {nom de la variable} allant de {expression numérique} jusqu'à {expression numérique} faire:
    {instruction 1}.
    {instruction 2}.
    ...
    {instruction n}.
.
```
* Pour avec pas:
_instruction_
```
Pour {nom de la variable} alland de {expression numérique} jusqu'à {expression numérique} en utilisant un pas de {expression numérique} faire:
    {instruction 1}.
    {instruction 2}.
    ...
    {instruction n}.
.
```

## Affichages et debug
Il pourra en cas d'erreur dans votre code être pratique de pouvoir afficher les éléments qui pourraient poser problème.

On peut tout d'abord afficher toute expression dans la console:\
_instruction_
```
Afficher {expression}.
```
On peut également récupérer la taille d'une liste ou d'une chaine de caractère:\
_expression_
```
La taille de {chaîne de caractère/liste}?
```
Enfin, on peut récupérer le type de d'une expression sous forme de chaine de caractère:\
_expression_
```
Le type de {expression}?
```

## Fonctions
Les fonctions sont très utiles pour exécuter un morceau de programme souvent réutilisé à différents endroits du votre code.
Une focntion se définit de la manière suivante:\
_instruction_
```
Soit {nom de la fonction} une fonction qui lorsqu'elle appelée exécute:
    {instruction 1}.
    {instruction 2}.
    ...
    {instruction n}.
.
```
Elles peuvent être également définies avec des arguments:\
_instruction_
```
Soit {nom de la fonction} une fonction qui lorsqu'elle appelée avec {nom de la variable 1}, ..., {nom de la variable n} exécute:
    {instruction 1}.
    {instruction 2}.
    ...
    {instruction n}.
.
```

Pour exécuter une fonction:\
_instruction_
```
Exécuter la fonction f.
```
Et avec des arguments:\
_instruction_
```
Exécuter la fonction f avec les arguments {expression 1}, ..., {expression n}.
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
Le résultat de la fonction {nom de la fonction}?
```
Et avec des arguments:\
_expression_
```
Le résultat de la fonction {nom de la fonction} avec les arguments {expression 1}, ..., {expression n}?
```
