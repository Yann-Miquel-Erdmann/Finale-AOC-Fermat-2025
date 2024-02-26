#include "split_expr.h"

bool is_uppercase(char c){
    if (c < 91 && c > 64){
        return true;
    }
    return false;
}

int split_expr(expr_t* expr){
    if (expr->list_len == -1){
        expr->list_len = 0;
        expr->expr_list = NULL;
        int ind_str = 0;
        int len = 2;
        char* text = malloc(2*sizeof(char));
        int index = 0;
        for (int i = 0; i<expr->len; i++){
            if (is_uppercase(expr->text[i]) && i != 0){
                if (expr->list_len == 0){
                    expr->list_len = 1;
                    expr->expr_list = malloc(expr->list_len*sizeof(expr_t*));
                }
                if (index == expr->list_len){
                    expr->list_len *= 2;
                    expr->expr_list = realloc(expr->expr_list, expr->list_len*sizeof(expr_t*));
                }
                expr->expr_list[index] = new_expr();
                expr->expr_list[index]->len = expr->len - i;
                expr->expr_list[index]->text = realloc(expr->expr_list[index]->text, expr->expr_list[index]->len*sizeof(expr_t*));
                
                for (int j = 0; j<expr->len - i; j++){
                    expr->expr_list[index]->text[j] = expr->text[i+j];
                }
                
                i = i + split_expr(expr->expr_list[index]);
                index++ ;
                
            }else if (expr->text[i] == '?'){
                free(expr->text);
                expr->text = text;
                expr->len = ind_str+1;
                expr->text = realloc(expr->text = text, expr->len*sizeof(expr_t*));
                expr->text[ind_str] = '\0';
                return i;
            }else{
                if (ind_str+1 == len){
                    len *= 2;
                    text = realloc(text, len*sizeof(char));
                }
                text[ind_str] = expr->text[i];
                ind_str ++;
            }
        }
        free(expr->text);
        expr->text = text;
        expr->len = ind_str+1;
        expr->text = realloc(expr->text = text, expr->len*sizeof(expr_t*));
        expr->text[expr->len] = '\0';
        return expr->len;
    }
    return -1;
}
