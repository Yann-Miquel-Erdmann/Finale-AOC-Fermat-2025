#include <stdio.h>
#include "split_expr.h"

int main(void){
    char* instruction = "On a E{expression 1}? qui est plus grand que E{expression 2}?";
    expr_t* expr = new_expr();
    expr->len = (int)strlen(instruction);
    expr->text = realloc(expr->text, expr->len);
    strcpy(expr->text, instruction);
    split_expr(expr);
    print_expr(expr);
    free_expr(expr);
    return 0;
}
