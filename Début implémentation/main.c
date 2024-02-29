#include <stdio.h>
#include "split_expr.h"
#include "eval_numbers.h"

int main(void){
    char* instruction = "Soit x la variable initialisée à La somme de La somme de L'entier 0? et de L'entier 1?? et de La somme de L'entier 2? et de L'entier 3???.";
    //instruction = "L'entier 3.";
    expr_t* expr = new_expr();
    expr->len = (int)strlen(instruction)+1;
    expr->text = realloc(expr->text, expr->len);
    strcpy(expr->text, instruction);
    split_expr(expr);
    print_expr(expr);
    free_expr(expr);
    
    char* s = "moins trois-cent-vingt-sept millions deux-cent-quatre-vingt-douze mille six-cent-trente-huit";
    s = "quatre-vingts";
    int* result = eval_number(s, (int)strlen(s));
    
    if (result[0] == 1){
        printf("%d\n", result[1]);
    }else{
        printf("\"%s\" is not a valid number\n", s);
    }
    free(result);
    return 0;
}
