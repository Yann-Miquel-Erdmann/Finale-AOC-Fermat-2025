#include "eval_numbers.h"

// first version without checking the order nor the nonsense like "deux mille mille" qui donnerais 3000 ou "un mille"

int match_num(char* num){
    if (!strcmp(num, "un")){
        return 1;
    }else if (!strcmp(num, "deux")){
        return 2;
    }else if (!strcmp(num, "trois")){
        return 3;
    }else if (!strcmp(num, "quatre")){
        return 4;
    }else if (!strcmp(num, "cinq")){
        return 5;
    }else if (!strcmp(num, "six")){
        return 6;
    }else if (!strcmp(num, "sept")){
        return 7;
    }else if (!strcmp(num, "huit")){
        return 8;
    }else if (!strcmp(num, "neuf")){
        return 9;
    }else if (!strcmp(num, "zero")){
        return 0;
    }else if (!strcmp(num, "dix")){
        return 10;
    }else if (!strcmp(num, "onze")){
        return 11;
    }else if (!strcmp(num, "douze")){
        return 12;
    }else if (!strcmp(num, "treize")){
        return 13;
    }else if (!strcmp(num, "quatorze")){
        return 14;
    }else if (!strcmp(num, "quinze")){
        return 15;
    }else if (!strcmp(num, "seize")){
        return 16;
    }else if (!strcmp(num, "vingt")){
        return 20;
    }else if (!strcmp(num, "trente")){
        return 30;
    }else if (!strcmp(num, "quarante")){
        return 40;
    }else if (!strcmp(num, "cinquante")){
        return 50;
    }else if (!strcmp(num, "soixante")){
        return 60;
    }else if (!strcmp(num, "cent")){
        return 100;
    }else{
        return -1;
    }
}

int* eval_number(char* str_num, int len){
    int n = 0;
    int tmp = 0;
    int str_len = 2;
    char* str = malloc(str_len*sizeof(char));
    int index = 0;
    for (int i = 0; i<=len; i++){
        if (str_num[i] == ' ' || i == len){
            if (!strcmp(str, "cent") || !strcmp(str, "cents")){
                if (tmp == 0){
                    n += 100;
                }else{
                    tmp = tmp*100;
                }
            }else if (!strcmp(str, "mille")){
                if (tmp == 0){
                    n += 1000;
                }else{
                    n += tmp * 1000;
                    tmp = 0;
                }
            }else if (!strcmp(str, "million") || !strcmp(str, "millions")){
                n += tmp * 1000000;
                tmp = 0;
            }else if (!strcmp(str, "milliards") || !strcmp(str, "milliards")){
                n += tmp * 1000000000;
                tmp = 0;
            }else{
                int result = match_num(str);
                if (result != -1){
                    if (i == len){
                        if (result == 20 && tmp == 4){
                            n += 80;
                        }else{
                            n += tmp+result;
                        }
                        tmp = 0;
                    }else{
                        if (result == 20 && tmp == 4){
                            tmp = 80;
                        }else{
                            tmp += result;
                        }
                    }
                }
            }
            if (i == len){
                n += tmp;
            }
            str_len = 2;
            str = realloc(str, str_len*sizeof(char));
            index = 0;
        }else if (str_num[i] == '-'){
            int result = match_num(str);
            if (result != -1){
                if (result == 100){
                    tmp *= 100;
                }else if (result == 20 && tmp%100 == 4){
                    tmp = tmp - tmp%100 + 80;
                }else{
                    tmp += result;
                }
            }
            str_len = 2;
            str = realloc(str, str_len*sizeof(char));
            index = 0;
        }else{
            if (i<len){
                if (index+1 == str_len){
                    str_len *= 2;
                    str = realloc(str, str_len*sizeof(char));
                }
                str[index] = str_num[i];
                str[index+1] = '\0';
                index ++;
            }
        }
    }
    int* l = malloc(2*sizeof(int));
    l[0] = 1;
    l[1] = n;
    return l;
}
