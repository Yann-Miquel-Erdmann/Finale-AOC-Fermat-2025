#include "split_expr.h"

bool is_uppercase(char c){
    if (c < 91 && c > 64){
        return true;
    }
    return false;
}

int split_expr(expr_t* expr){
    if (expr->list_len == -1){
        expr->expr_list = malloc(sizeof(expr_t*));;
        expr->list_len = 1;
        int index = 0;
        for (int i = 0; i<expr->len; i++){
            if (is_uppercase(expr->text[i]) && i != 0){
                if (index == expr->list_len){
                    expr->list_len *= 2;
                    expr->expr_list = realloc(expr->expr_list, expr->list_len);
                }
                expr->expr_list[index] = new_expr();
                expr->expr_list[index]->len = expr->len - i;
                expr->expr_list[index]->text = realloc(expr->expr_list[index]->text, expr->expr_list[index]->len);
                
                for (int j = 0; j<expr->len - i; j++){
                    expr->expr_list[index]->text[j] = expr->text[i+j];
                }
                
                i = i + split_expr(expr->expr_list[index]);
                index++ ;
                
            }else if (expr->text[i] == '?'){
                expr->len = i;
                expr->text = realloc(expr->text, expr->len);
                return i;
            }
        }
        return expr->len;
    }
    return -1;
}
