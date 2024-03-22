#ifndef eval_numbers_h
#define eval_numbers_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* renvoie une liste de deux entier sous la forme [x, y]
   * x est un entier 0 ou 1 qui indique le succès ou non de la conversion
   * y est l'entier renvoyé par la fonction si x = 1
*/
int* eval_number(char* str_num, int len);


/* renvoie un entier du nombre num en lettre
   par nombre simple, con considère tout nombre inférieur à un million
   qui s'écrit comme un seul mot sans tiret
   with_s indique si l'argument demandé est au pluriel
   (uniquement utile pour vingt et cent car les seuls variables)
*/
int match_num(char* num, bool with_s);

char* str_from_int(int n);
char* str_from_float(float n);

#endif
