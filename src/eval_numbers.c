#include "eval_numbers.h"

int match_num(char* num, bool with_s){
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
    }else if (!strcmp(num, "zéro")){
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
    }else if ((!strcmp(num, "vingt") && !(with_s)) || (!strcmp(num, "vingts") && (with_s))){
        return 20;
    }else if (!strcmp(num, "trente")){
        return 30;
    }else if (!strcmp(num, "quarante")){
        return 40;
    }else if (!strcmp(num, "cinquante")){
        return 50;
    }else if (!strcmp(num, "soixante")){
        return 60;
    }else if ((!strcmp(num, "cent") && !(with_s)) || (!strcmp(num, "cents") && (with_s))){
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
    int sign = 1;
    bool valid = true;
    char last_separator = ' ';
    int ten_power = 99; // dernière puissance de dix placée pour savoir si les nombres donnés sont bien dans un bon ordre
    for (int i = 0; i<=len; i++){
        if (str_num[i] == ' ' || i == len){ // espace ou fin du nombre
            if (!strcmp(str, "zéro")){
                if (i!= len || tmp != 0){
                    valid = false;
                    break;
                }
            }
            if (!strcmp(str, "mille") && last_separator == '-' && ten_power > 3 && i == len){
                if (tmp == 0){
                    n += 1000;
                }else{
                    n += tmp * 1000;
                    tmp = 0;
                }
                ten_power = 3;
            }else if (!strcmp(str, "million") && last_separator == ' ' && tmp == 1 && ten_power > 6){
                n += 1000000;
                tmp = 0;
                ten_power = 6;
            }else if (!strcmp(str, "millions") && last_separator == ' ' && tmp > 1 && ten_power > 6){
                n += tmp * 1000000;
                tmp = 0;
                ten_power = 6;
            }else if (!strcmp(str, "milliard") && last_separator == ' ' && tmp == 1 && ten_power > 9){
                n += 1000000000;
                tmp = 0;
                ten_power = 9;
            }else if (!strcmp(str, "milliards") && last_separator == ' ' && tmp > 1 && ten_power > 9){
                n += tmp * 1000000000;
                tmp = 0;
                ten_power = 9;
            }else if (!strcmp(str, "moins") && n == 0 && tmp == 0){
                sign = -1;
            }else if (!strcmp(str, "vingt") && ((last_separator == ' ' && tmp == 0) || (last_separator == '-' && tmp%100 == 0))){
                tmp += 20;
            }else if (!strcmp(str, "cent") && last_separator == ' ' && tmp == 0){
                tmp = 100;
            }else if (!strcmp(str, "cents") && last_separator == '-' && tmp > 1 && tmp < 10){
                tmp *= 100;
            }else if (!strcmp(str, "un") && last_separator == '*' && tmp%10 == 0 && tmp/10%10 > 1 && tmp/10%10 < 7){
                tmp ++;
                last_separator = ' ';
            }else if (!strcmp(str, "onze") && last_separator == '*' && tmp%100 == 60){
                tmp += 11;
                last_separator = ' ';
            }else{
                int result = match_num(str, true);
                if (result == -1 || last_separator == '*'){
                    valid = false;
                    printf("error %d, '%s', %d\n", tmp, str, ten_power);
                    break;
                }else{
                    if (result == 1 && tmp == 0){
                        tmp ++;
                    }else if (result == 20 && tmp%100 == 4 && last_separator == '-'){
                        tmp = tmp - tmp%100 + 80;
                    }else if ((result < 10 && tmp%10 == 0) || (result < 100 && tmp%100 == 0 && result != 20) || (tmp%1000 == 0 && result != 100 && result != 20)){
                        tmp += result;
                    }else if (result > 9 && result < 20 && (tmp%100 == 60 || tmp%100 == 80)){
                        tmp += result;
                    }else{
                        valid = false;
                        break;
                    }
                }
            }
            if (i == len){
                n += tmp;
            }
            str_len = 2;
            str = realloc(str, str_len*sizeof(char));
            index = 0;
            if (last_separator != '*'){
                last_separator = ' ';
            }
            
        }else if (str_num[i] == '-'){
            int result = match_num(str, false);
            if (result != -1){
                if (result == 0){
                    if (i!= len || tmp != 0){
                        valid = false;
                        break;
                    }
                }else if (result == 100 && tmp < 100){
                    if (tmp == 0){
                        tmp = 1;
                    }
                    tmp *= 100;
                }else if (result == 20 && tmp%100 == 4 && last_separator == '-'){
                    tmp = tmp - tmp%100 + 80;
                }else if ((result < 10 && tmp%10 == 0) || (result < 100 && tmp%100 == 0) || tmp == 0){
                    tmp += result;
                }else if (result > 9 && result < 20 && (tmp%100 == 60 || tmp%100 == 80)){
                    tmp += result;
                }else{
                    valid = false;
                    break;
                }
            }else{
                if (!strcmp(str, "et") && last_separator == '-' && tmp%10 == 0 && tmp/10%10 > 1 && tmp/10%10 < 7){
                    last_separator = '*';
                }else if (!strcmp(str, "mille") && ten_power > 3){
                    if (tmp == 0){
                        tmp = 1;
                    }
                    n += 1000*tmp;
                    tmp = 0;
                }else{
                    valid = false;
                    printf("error 0, %s\n", str);

                    break;
                }
            }
            str_len = 2;
            str = realloc(str, str_len*sizeof(char));
            index = 0;
            if (last_separator != '*'){
                last_separator = '-';
            }
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
    l[0] = (int)valid;
    l[1] = n*sign;
    free(str);
    return l;
}
