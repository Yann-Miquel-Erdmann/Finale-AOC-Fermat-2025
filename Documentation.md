# Documentation du language

## Disclamer
Le language n'a pas encore été totalement testé, il reste surment des bugs et de petits contournements de syntaxe.
Il n'y a pas encore de 

## Présentation générale et aspects spécifiques

Le language a été créé dans le but d'avoir un code le plus clair possible.
Dans ce sens, tout sera écrit en français avec des phrases (attention à ne pas oublier les accents :3).
Pro tip: Comme en français, si vous ne voulez pas avoir une phrase trop compliquée, ne la faites pas trop longue.

Le language à d'abord une spécificité: toutes les phrases commencent une majuscule et se terminent par un point.
Si vous voulez récupérer une valeur, à la place d'un point à la fin, il faudra mettre un point d'interrogation comme si vous posiez une question.
/!\ toute majuscule sera considérée comme le début d'une nouvelle phrase, elles ne doivent donc avoir que cet usage. Même avertissement pour le point et le point virgule.
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
Les expressions base sont les expressions que vous utiliserez probablement le plus souvent
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
Le booléen {vrai/faux}
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

Plusieurs opérations sont possibles sur les listes:
* Ajouter des éléments à la fin de la liste
_instruction_
```
Ajouter à la liste {nom de la liste} {expression}.
```

* Insérer des éléments au milieu de la liste:
_instruction_
```
Insérer {expression} dans la liste {nom de la liste} à l'index {expression: entier}.
```

* Supprimer un élément
_instruction_
```
Retirer de la liste {nom de la liste} l'élément d'indice {expression: entier}.
```

* Remplacer un élément
_instruction_
```
Remplacer l'élément de la liste {nom de la liste} à l'indice {expression: entier} par {expression}.
```

On peut également accéder à un élément de la liste avec
_expression_
```
L'élément de la liste {nom de la liste} à l'indice {expression: entier}?
```

Finalement, on peut accéder à la liste en entier avec
_expression_
```
La liste {nom de la liste}?
```
