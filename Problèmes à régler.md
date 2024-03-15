#  Problèmes à régler

## ~~si imbriqué~~ => résolution: aucune, on laisse comme ça
avec la syntaxe actuelle, on a:
```
Si on a La valeur de la variable x? qui plus petit que L'entier trois? alors:
    Si on a La valeur de la variable x? qui est plus grand que L'entier zero? alors:
        {instruction},
        ...,
        {instruction}.
    ,
    Si on a La valeur de la variable x? qui est plus grand que L'entier un? alors:
        {instruction},
        ...,
        {instruction}.
    .
```
ce qui n'est pas agréable à voir avec la ponctuation actuelle.


Il faudrait avoir un mot à la fin du si

Si Exp? alors:
    Inst.
    Inst.
    Inst.
.
