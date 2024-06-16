#ifndef eval_numbers_h
#define eval_numbers_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* renvoie l'entier associé à la chaine str_num de longueur len
   stocke si le nombre est valide dans valid */
int eval_number(char* str_num, int len, bool* valid);

/* renvoie le flottant associé à la chaine str_num de longueur len
   stocke si le nombre est valide dans valid */
float eval_float(char* str_num, int len, bool* valid);


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
