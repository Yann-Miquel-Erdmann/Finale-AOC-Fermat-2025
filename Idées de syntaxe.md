# Syntaxe
## Règle générale
- Il doit y avoir une majuscule en début de phrase (ligne) et un point à la fin de celle-ci  
- Mettre un point d'interrogation à la fin d'une expression qui doit renvoyer une valeur.
- Les mots de liaison doivent être compté avec le mot qui suit ex: "l'entier" compte comme un mot, tout comme "le flottant"  
- Les nombres doivent être écrits en toutes lettres comme [ceci](https://fr.wikipedia.org/wiki/Rectifications_orthographiques_du_fran%C3%A7ais_en_1990#D%C3%A9tails)
- Les opérateurs doivent êtres écrits en toutes lettres  
- Les noms de variables doivent être uniques et en un seul mot  
- Les types doivent être uniques et en un seul mot   

## Types
- le booléen
- l'entier (signé)
- le flottant (signé)
- la chaîne de caractères (peut-être)

## instructions
les instructions sont terminées par un point

## expressions
Les expressions commencent par une majuscule et sont terminées par un point d’interrogation car elles renvoient une valeur

### entier
```
L'entier {entier en toutes lettres}?
```
### flottant
```
Le flottant {entier en toutes lettres} virgule {entier en toutes lettres}?
```
### booléen
```
Le booléen {vrai ou faux}?
```

### chaîne de caractères
```
La chaîne de caractères "{chaîne de caractères}"?
```

## Structures de données
### Variable
#### création
type: instruction
```
Soit {nom de variable} la variable initialisée à {expression}.
```
Exemple:
```
Soit var la variable initialisée à L'entier cinq cent quatre-vingt-dix-neuf?.
```

#### création sans initialisation
type: 
  
```
Soit {nom de la variable} une variable.
```

#### accession
type: expression

```
La variable {nom de la variable}?
```

#### modification
type: instruction

```
Que la variable {nom de la variable} devienne {valeur}.
```


### **liste**
#### création 
type: instruction

```
Soit {nom de la liste} une liste vide.
```

#### accession
type: expression

```
La valeur de l'élément de la liste {nom de la liste} à l'indice {indice}?
```

#### modification
type: instruction

```
Remplacer l'élément de la liste {nom de la liste} à l'indice {indice} par {expression}.
```

#### ajout
type: instruction

```
Ajouter à la liste {nom de la liste} {expression}.
```

#### suppression
type: instruction

```
Retirer de la liste {nom de la liste} l'élément d'indice {indice}?
```

#### taille
type: expression

```
La taille de la liste {nom de la liste}?
```

## Opérateurs
tous les opérateurs sont de type expression

### somme
types en entrée: flottants et entiers  
types en sortie: flottants et entiers  

```
La somme de {expression 1}? et de {expression 2}?
```

### différence
types en entrée: flottants et entiers  
types en sortie: flottants et entiers

```
La différence de {expression 1}? et de {expression 2}?
```
### produit
types en entrée: flottants et entiers  
types en sortie: flottants et entiers  

```
Le produit de {expression 1}? et de {expression 2}?
```

### quotient
types en entrée: flottants et entiers  
types en sortie: flottants et entiers  

```
Le quotient de {expression 1}? par {expression 2}?
```

### quotient entier
types en entrée: flottants et entiers  
types en sortie: entiers  

```
Le quotient entier de {expression 1}? par {expression 2}?
```

### reste
types en entrée: flottants et entiers  
types en sortie: flottants et entiers  

```
Le reste de {expression 1}? par {expression 2}?
```

### la négation booléenne
types en entrée: booléen  
types en sortie: booléen  

```
La négation de {expression}?
```

## Comparateurs:
tous les comparateurs sont de type expression

### égalité
types en entrée: (flottants et entiers) ou booléens ou  chaînes de caractères  
types en sortie: booléen  

```
On a {expression 1}? qui est égal à {expression 2}?
```

### plus grand que
types en entrée: flottants et entiers  
types en sortie: booléen  

```
On a {expression 1}? qui est plus grand que {expression 2}?
```

### plus petit que
types en entrée: flottants et entiers  
types en sortie: booléen  

```
La valeur de {expression 1}? est plus petite que la valeur de {expression 2}??
```

### strictement plus grand que
types en entrée: flottants et entiers  
types en sortie: booléen  

```
On a {expression 1}? qui est strictement plus grand que {expression 2}?
```

### strictement plus petit que
types en entrée: flottants et entiers  
types en sortie: booléen  

```
On a {expression 1}? qui est strictement plus petit que {expression 2}?
```

## Conditions
### Utilisation générale
Chaque phrase doit être séparée d'une virgule.
Si une phrase se termine par un point, c'est la fin de la condition.

### Si ... alors
```
Si {condition} alors:
{instruction 1}.
{instruction 2}.
...
{instruction n}.
.
```


### Si ... alors ... sinon
```
Si {condition} alors faire:
{instruction 1}.
{instruction 2}.
...
{instruction n}.
.
Sinon faire:
{instruction 1}.
{instruction 2}.
...
{instruction n}.
.
.
```

## Boucles
### utilisation globale
Chaque phrase doit être séparée d'une virgule.
Si une phrase se termine par un point, c'est la fin de la boucle.

### Tant que
```
Tant que {condition} alors faire:
{instruction 1}.
{instruction 2}.
...
{instruction n}.
.
.
```

### Pour
```
Pour {definition variable} allant jusqu'à {expression} faire:
{instruction 1}.
{instruction 2}.
...
{instruction n}.
.
```
Note: le "Pour" remplace le "Soit" de la definition de la variable
Exemple:
```
Pour i la variable initialisée à L'entier zero? allant jusqu'à L'entier dix? faire:
{instruction 1}.
{instruction 2}.
...
{instruction n}.
.
```
Note: équivalent à une boucle pour avec un pas de 1

### Pour avec un pas
```
Pour {definition variable} allant jusqu'à {expression 1} en utilisant un pas égal à {expression 2} faire:
{instruction 1}.
{instruction 2}.
...
{instruction n}.
.
```
Exemple:
```
Soit liste une liste vide.
Pour i la variable initialisée à L'entier zero? allant jusqu'à L'entier dix? en utilisant un pas égal à L'entier deux? faire:
Ajouter à la liste liste La valeur de la variable i?.
```

## affichages dans la console
```
Affiche {expression}.
```
Exception chaîne de caractères:
```
Affiche le message {chaîne de caractères}.
```

## Fonctions
### fonctionnement global
Utilise la même syntaxe que les boucles et les conditions i.e. virgules après chaque phrases et un point à la fin de toutes le instructions

### définition
:warning: Il va falloir que l'on trouve où mettre le type de ce que la fonction renvoie.
```
Soit {nom de la fonction} une fonction qui lorsqu'elle est appelée execute:
{instruction 1}.
{instruction 2}.
...
{instruction n}.
.
```

Pour appeler une fonction qui ne renvoie rien, on écrit:
type: instruction
```
Execute la fonction {nom}( prenant les arguments{arg1}. ..., {argn}).
```

Pour renvoyer une valeur, on écrit à la fin
type: instruction
```
Renvoie {expression}?
```
Pour récupérer cette expression renvoyée, on écrit:
type: expression
```
La valeur renvoyée par la fonction {nom}( prenant les arguments {arg1}, ..., {argn})?
```
On pourrait alors avoir:
```
Soit x un entier
Que la variable x devienne La valeur renvoyée par la fonction f?.
```

## Fonction avec des arguments
### fonctionnement
Même écriture que la fonction avec quelques ajouts
Il faut mettre devant les variables locales définies soit en argument soit dans la fonction le mot "locale" comme dans l'exemple.

### définition
```
Soit {nom de la fonction} une fonction qui lorsqu'elle est appelée avec {nom variable 1}, ..., {nom variable n} execute:
{instruction 1}.
{instruction 2}.
...
{instruction n}.
.
```

### exemple
```
Soit x une variable.
Soit f une fonction qui lorsqu'elle est appelée avec x, y execute:
Renvoie La somme de La variable locale x? et de La variable locale y??.
Que x devienne La valeur renvoyée par la fonction f avec les arguments L'entier douze?, L'entier trois??.
```
## mémoire
Tout sur le tas  
Une pile pour les appels récursifs
