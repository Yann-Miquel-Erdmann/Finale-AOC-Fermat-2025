# Syntaxe
## Règle générale
- Il doit y avoir une majuscule en début de phrase (ligne) et un point à la fin de celle-ci  
- Mettre un point d'interrogation à la fin d'une expression qui doit renvoyer une  
valeur.
- Les mots de liaison doivent être compté avec le mot qui suit ex: "l'entier" compte comme un mot, tout comme "le flottant"  
- Les nombres doivent être écrits en toutes lettres comme [ceci](https://fr.wikipedia.org/wiki/**Rectifications_orthographiques_du_fran**%C3%A7ais_en_1990#D%C3%A9tails)
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
Le booléen {Vrai ou Faux}?
```

### booléen
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
#### accession
```
La variable {nom de la variable}?
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
La liste {nom de la liste} à l'indice {indice}?
```

#### modification
```
Que la liste {nom de la variable} à l'indice {indice} prenne {expression}.
```

#### ajout
```
Ajouter à la liste {nom de la liste} {expression}.
```

#### retrait
```
Retirer de la liste {nom de la liste}?
```

#### taille
```
La taille de la liste {nom de la liste}?
```


## Opérateurs
### somme
types en entrée: flottants et entiers  
types en sortie: flottants et entiers  
```
La somme de {expression 1} et {expression 2}?
```

### différence
types en entrée: flottants et entiers  
types en sortie: flottants et entiers  
```
La différence de {expression 1} et {expression 2}?
```
### produit
types en entrée: flottants et entiers  
types en sortie: flottants et entiers  
```
Le produit de {expression 1} et {expression 2}?
```

### quotient
types en entrée: flottants et entiers  
types en sortie: flottants et entiers  
```
Le quotient de {expression 1} et {expression 2}?
```

### quotient entier
types en entrée: flottants et entiers  
types en sortie: entiers  
```
Le quotient entier de {expression 1} et {expression 2}?
```

### reste
types en entrée: flottants et entiers  
types en sortie: flottants et entiers  

```
Le reste de {expression 1} et {expression 2}?
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
{expression 1} égal à {expression 2}?
```
:warning: pour la majuscule en début d'expression

### plus grand que
types en entrée: flottants et entiers  
types en sortie: booléen  
```
{expression 1} plus grand que {expression 2}?
```
:warning: pour la majuscule en début d'expression

### plus petit que
types en entrée: flottants et entiers  
types en sortie: booléen  
```
{expression 1} plus petit que {expression 2}?
```
:warning: pour la majuscule en début d'expression

### strictement plus grand que
types en entrée: flottants et entiers  
types en sortie: booléen  
```
{expression 1} strictement plus grand que {expression 2}?
```
:warning: pour la majuscule en début d'expression

### strictement plus petit que
types en entrée: flottants et entiers  
types en sortie: booléen  
```
{expression 1} strictement plus petit que {expression 2}?
```
:warning: pour la majuscule en début d'expression






## mémoire
Tout sur le tas  
Une pile pour les appels récursifs


