## valeurs
structure avec:
- un char sui représente le type de la valeur
- un pointeur vers un entier
- un pointeur vers un flottant
- un pointeur vers un booléen
- un pointeur vers une chaîne de caractères
  
  
il serait intéressant de ne stocker qu'un seul pointeur


## variables locales
dans une pile pour éviter de faire un dictionnaire
pointeur vers une valeur

## listes
soit:
- pile
- tableau redimensionnable
  
## stack frames
structure:
- char représentant la fonction (on donnera un id à chaque fonction avec #define)
- pointeur vers la valeur à retourner
- pointeur vers les variables locales (pile ou dictionnaire) 