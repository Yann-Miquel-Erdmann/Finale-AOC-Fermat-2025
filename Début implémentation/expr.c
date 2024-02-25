#include "expr.h"

expr_t* new_expr(void){
    expr_t* expr = malloc(sizeof(expr_t));
    expr->text = malloc(2*sizeof(char));
    expr->len = 0;
    strcpy(expr->text, "\0");
    expr->expr_list = NULL;
    expr->list_len = -1;
    expr->value_type = -1;
    expr->operation_num = -1;
    return expr;
}

void free_expr(expr_t* expr){
    free(expr->text);
    free(expr->expr_list);
}

void print_expr_with_tab(expr_t* expr, int tab_num){
    if (expr == NULL){
        return;
    }
    for (int i = 0; i < tab_num; i++){
        printf("|  ");
    }
    printf("%s\n", expr->text);
    for (int i = 0; i < expr->list_len; i++){
        print_expr_with_tab(expr->expr_list[i], tab_num+1);
    }
}

void print_expr(expr_t* expr){
    print_expr_with_tab(expr, 0);
}

