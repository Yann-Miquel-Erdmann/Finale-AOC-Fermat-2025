# Syntaxe
## Règle générale
- Il doit y avoir une majuscule en début de phrase (ligne) et un point à la fin de celle-ci  
- Mettre un point d'interrogation à la fin d'une expression qui doit renvoyer une  
valeur.
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

## expressions
les expressions sont terminées par un point d’interrogation car elles renvoient une valeur

(ou les expressions commencées par un point d'interrogation, il me parait plus facile de coder l'interpretation losqu'il est devant, nottament avec le flottant si tu considère qu'il sagit d'une unique expression)

### entier
```
L'entier {entier en toutes lettres}?
```
### flottant
```
Le flottant {entier en toutes lettres}? virgule {entier en toutes lettres}?
```
(ici, tu considère que les decux valeurs forment une seule expression?)
### booléen
```
Le booléen {Vrai ou Faux}?
```

### chaine de caractères
```
La chaîne de caractères "{chaîne de caractères}"?
```




## Structures de données
### Variable
#### création

```
Soit {nom de variable} la variable initialisée à {expression}.
```
Exemple:
```
Soit var la variable initialisée à L'entier cinq cent quatre-vingt-dix-neuf?.
```
(va-t-on être embettant avec le "à" + "le" qui devient "au" par exemple pour le flottant/booléen)
#### accession
```
La valeur de la variable {nom de la variable}?.
```

#### modification
```
Que la variable {nom de la variable} prenne la valeur {valeur}.
```


### liste
#### création 
```
Soit {nom de la liste} une liste vide.
```

#### accession
```
La valeur de l'élément de la liste {nom de la liste} à l'indice {indice}?.
```

#### modification
```
Que l'élément de la liste {nom de la variable} à l'indice {indice} devienne {expression}.
```

#### ajout
```
Ajouter à la liste {nom de la liste} {expression}.
```

#### retrait
```
Retirer de la liste {nom de la liste} l'élément à l'indice {indice}.
```
(tu considère un pop?, je pense qu'il serait plus agréable de pouvoir enlever n'importe quel élément de la liste au milieu ou non)

#### taille
```
La taille de la liste {nom de la liste}
```


## Opérateurs
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

### non
types en entrée: booléen  
types en sortie: booléen  
```
Non {expression}?
```

## Comparateurs
### égalité
types en entrée: (flottants et entiers) ou booléens ou  chaînes de caractères  
types en sortie: booléen  
```
{expression 1}? est égal à {expression 2}?
```
:warning: pour la majuscule en début d'expression

### plus grand que
types en entrée: flottants et entiers  
types en sortie: booléen  
```
{expression 1}? est plus grand que {expression 2}?
```
:warning: pour la majuscule en début d'expression

### plus petit que
types en entrée: flottants et entiers  
types en sortie: booléen  
```
{expression 1}? est plus petit que {expression 2}?
```
:warning: pour la majuscule en début d'expression

### strictement plus grand que
types en entrée: flottants et entiers  
types en sortie: booléen  
```
{expression 1}? est strictement plus grand que {expression 2}?
```
:warning: pour la majuscule en début d'expression

### strictement plus petit que
types en entrée: flottants et entiers  
types en sortie: booléen  
```
{expression 1}? est strictement plus petit que {expression 2}?
```
:warning: pour la majuscule en début d'expression

## Conditions
### Si ... alors
```
Si {condition} alors:
{instruction 1},
{instruction 2}
...
{instruction 3}.
```

### Si ... alors ... sinon
```
Si {condition} alors:
{instructions}
Sinon faire :
{instruction 1},
{instruction 2},
...
{instruction n}.
```

## Boucles
### utilisation globale
Chaque phrase doit être séparée d'une virgule ou d'un point virgule (à choisir, pourrait également s'appliquer au conditions en général).
Si une phrase termine par un point, c'est la fin de la boucle.

### Tant que
```
Tant que {condition} alors:
{instruction 1},
{instruction 2},
...
{instruction n}.
```

### Pour
```
Pour {definition variable} allant jusqu'à {expression}? faire:
{instruction 1},
{instruction 2},
...
{instruction n}.
```
Note: le pour remplace le soit de la definition de la variable
Exemple:
```
Pour i la variable initialisée à 0? allant jusqu'à 10? faire:
{instruction 1},
{instruction 2},
...
{instruction n}.
```
Note: équvalent à une boucle pour avec un pas de 1

### Pour avec un pas
```
Pour {definition variable} allant jusqu'à {expression 1}? en utilisant un pas de {expression 2}? faire:
{instruction 1},
{instruction 2},
...
{instruction n}.
```
Note: le pour remplace le soit de la definition de la variable
Exemple:
```
Pour i la variable initialisée à 0? allant jusqu'à 10? en utilisant un pas de 2? faire:
{instruction 1},
{instruction 2},
...
{instruction n}.
```

## affichages dans la console
### entiers
```
Affiche l'entier {entier}?.
```

### flottants
```
Affiche le flottant {flottant}?.
```

### chaine de caractères
```
Affiche le message {chaine de caractères}?.
```

### booléen
```
Affiche le booléen {booléen}?.
```

## Fonctions
### fonctionnement
Utilise la même syntaxe que les boucles et les conditions i.e. virgules après chaque phrases et un point à la fin de toutes le instructions

### définition
```
Soit {nom de la fonction} une fonction qui lorsqu'elle est appelée execute:
{instruction 1},
{instruction 2},
...
{instruction n}.
```

## mémoire
Tout sur le tas  
Une pile pour les appels récursifs

## Notes
J'ai un peu agrandi les syntaxes, elles me parraissent plus claires comme ça, il faudra voir comment on les mettera à la fin
J'ai remarqué que certaines expressions n'ont pas toujours de point d'interrogation à la fin (somme/différence.../comparaisons) est ce que c'est voulu?

