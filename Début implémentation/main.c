#include <stdio.h>
#include "split_expr.h"
#include "eval_numbers.h"

int main(void){
    char* instruction = "On a E{expression 1}? qui est plus grand que E{expression 2}?";
    expr_t* expr = new_expr();
    expr->len = (int)strlen(instruction);
    expr->text = realloc(expr->text, expr->len);
    strcpy(expr->text, instruction);
    split_expr(expr);
    print_expr(expr);
    free_expr(expr);
    
    char* s = "trois-cent-vingt-sept millions deux-cent-quatre-vingt-douze mille six-cent-trente-huit";
    int* result = eval_number(s, (int)strlen(s));
    
    if (result[0] == 1){
        printf("%d\n", result[1]);
    }else{
        printf("%s is not a valid number\n", s);
    }
    
    return 0;
}
