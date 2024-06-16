#include "eval_numbers.h"

#include "custom_error.h"

char* add_str(char* str, int* taille, char* added) {
    if (str == NULL) {
        custom_error("str est NULL", NULL, NULL);
    }

    int len = (int)strlen(added);
    int len_str = (int)strlen(str);
    while (*(taille) <= len_str + len) {
        *(taille) *= 2;
        str = realloc(str, (*(taille)) * sizeof(char));
        if (str == NULL) {
            custom_error("", NULL);
            exit(0);
        }
    }
    strcat(str, added);
    strcat(str, "");
    return str;
}

int match_num(char* num, bool with_s) {
    if (!strcmp(num, "un")) {
        return 1;
    } else if (!strcmp(num, "deux")) {
        return 2;
    } else if (!strcmp(num, "trois")) {
        return 3;
    } else if (!strcmp(num, "quatre")) {
        return 4;
    } else if (!strcmp(num, "cinq")) {
        return 5;
    } else if (!strcmp(num, "six")) {
        return 6;
    } else if (!strcmp(num, "sept")) {
        return 7;
    } else if (!strcmp(num, "huit")) {
        return 8;
    } else if (!strcmp(num, "neuf")) {
        return 9;
    } else if (!strcmp(num, "zéro")) {
        return 0;
    } else if (!strcmp(num, "dix")) {
        return 10;
    } else if (!strcmp(num, "onze")) {
        return 11;
    } else if (!strcmp(num, "douze")) {
        return 12;
    } else if (!strcmp(num, "treize")) {
        return 13;
    } else if (!strcmp(num, "quatorze")) {
        return 14;
    } else if (!strcmp(num, "quinze")) {
        return 15;
    } else if (!strcmp(num, "seize")) {
        return 16;
    } else if ((!strcmp(num, "vingt") && !(with_s)) || (!strcmp(num, "vingts") && (with_s))) {
        return 20;
    } else if (!strcmp(num, "trente")) {
        return 30;
    } else if (!strcmp(num, "quarante")) {
        return 40;
    } else if (!strcmp(num, "cinquante")) {
        return 50;
    } else if (!strcmp(num, "soixante")) {
        return 60;
    } else if ((!strcmp(num, "cent") && !(with_s)) || (!strcmp(num, "cents") && (with_s))) {
        return 100;
    } else {
        return -1;
    }
}

int* eval_float(char* str_num, int len) {
    char* str = malloc((len + 1) * sizeof(char));
    int index = 0;
    int start = 0;
    int exp = 1;
    for (int i = 0; i < len; i++) {
        if (str_num[i] == ' ' || i == len) {
            str[index] = '\0';
            index = 0;
            if (!strcmp(str, "zéro")) {
                exp *= 10;
                start = i + 1;
            } else {
                break;
            }
        } else {
            str[index] = str_num[i];
            index++;
        }
    }
    index = 0;
    for (int i = start; i < len; i++) {
        str[index] = str_num[i];
        index++;
    }
    str[index] = '\0';
    int* result = eval_number(str, len - start);
    result = realloc(result, 3 * sizeof(int));
    result[2] = exp;
    free(str);
    return result;
}

int* eval_number(char* str_num, int len) {
    int n = 0;
    int tmp = 0;
    int str_len = 2;
    char* str = malloc(str_len * sizeof(char));
    int index = 0;
    int sign = 1;
    bool valid = true;
    char last_separator = ' ';
    int ten_power = 99;  // dernière puissance de dix placée pour savoir si les nombres donnés sont bien dans un bon ordre
    for (int i = 0; i <= len; i++) {
        if (str_num[i] == ' ' || i == len) {  // espace ou fin du nombre
            if (!strcmp(str, "zéro")) {
                if (i != len || tmp != 0) {
                    valid = false;
                    break;
                }
            }
            if ((!strcmp(str, "mille") && last_separator == '-' && ten_power > 3 && i == len) || (!strcmp(str, "mille") && last_separator == ' ' && tmp == 0)) {
                if (tmp == 0) {
                    n += 1000;
                } else {
                    n += tmp * 1000;
                    tmp = 0;
                }
                ten_power = 3;
            } else if (!strcmp(str, "million") && last_separator == ' ' && tmp == 1 && ten_power > 6) {
                n += 1000000;
                tmp = 0;
                ten_power = 6;
            } else if (!strcmp(str, "millions") && last_separator == ' ' && tmp > 1 && ten_power > 6) {
                n += tmp * 1000000;
                tmp = 0;
                ten_power = 6;
            } else if (!strcmp(str, "milliard") && last_separator == ' ' && tmp == 1 && ten_power > 9) {
                n += 1000000000;
                tmp = 0;
                ten_power = 9;
            } else if (!strcmp(str, "milliards") && last_separator == ' ' && tmp > 1 && ten_power > 9) {
                n += tmp * 1000000000;
                tmp = 0;
                ten_power = 9;
            } else if (!strcmp(str, "moins") && n == 0 && tmp == 0) {
                sign = -1;
            } else if (!strcmp(str, "vingt") && ((last_separator == ' ' && tmp == 0) || (last_separator == '-' && tmp % 100 == 0))) {
                tmp += 20;
            } else if (!strcmp(str, "cent") && last_separator == ' ' && tmp == 0) {
                tmp = 100;
            } else if (!strcmp(str, "cents") && last_separator == '-' && tmp > 1 && tmp < 10) {
                tmp *= 100;
            } else if (!strcmp(str, "un") && last_separator == '*' && tmp % 10 == 0 && tmp / 10 % 10 > 1 && tmp / 10 % 10 < 7) {
                tmp++;
                last_separator = ' ';
            } else if (!strcmp(str, "onze") && last_separator == '*' && tmp % 100 == 60) {
                tmp += 11;
                last_separator = ' ';
            } else {
                int result = match_num(str, true);
                if (result == -1 || last_separator == '*') {
                    valid = false;
                    // printf("error %d, '%s', %d\n", tmp, str, ten_power)
                    break;
                } else {
                    if (result == 1 && tmp == 0) {
                        tmp++;
                    } else if (result == 20 && tmp % 100 == 4 && last_separator == '-') {
                        tmp = tmp - tmp % 100 + 80;
                    } else if ((result < 10 && tmp % 10 == 0) || (result < 100 && tmp % 100 == 0 && result != 20) || (tmp % 1000 == 0 && result != 100 && result != 20)) {
                        tmp += result;
                    } else if (result > 9 && result < 20 && (tmp % 100 == 60 || tmp % 100 == 80)) {
                        tmp += result;
                    } else {
                        valid = false;
                        break;
                    }
                }
            }
            if (i == len) {
                n += tmp;
            }
            str_len = 2;
            str = realloc(str, str_len * sizeof(char));
            index = 0;
            if (last_separator != '*') {
                last_separator = ' ';
            }

        } else if (str_num[i] == '-') {
            int result = match_num(str, false);
            if (result != -1) {
                if (result == 0) {
                    if (i != len || tmp != 0) {
                        valid = false;
                        break;
                    }
                } else if (result == 100 && tmp < 100) {
                    if (tmp == 0) {
                        tmp = 1;
                    }
                    tmp *= 100;
                } else if (result == 20 && tmp % 100 == 4 && last_separator == '-') {
                    tmp = tmp - tmp % 100 + 80;
                } else if ((result < 10 && tmp % 10 == 0) || (result < 100 && tmp % 100 == 0) || tmp == 0) {
                    tmp += result;
                } else if (result > 9 && result < 20 && (tmp % 100 == 60 || tmp % 100 == 80)) {
                    tmp += result;
                } else {
                    valid = false;
                    break;
                }
            } else {
                if (!strcmp(str, "et") && last_separator == '-' && tmp % 10 == 0 && tmp / 10 % 10 > 1 && tmp / 10 % 10 < 7) {
                    last_separator = '*';
                } else if (!strcmp(str, "mille") && ten_power > 3) {
                    if (tmp == 0) {
                        tmp = 1;
                    }
                    n += 1000 * tmp;
                    tmp = 0;
                } else {
                    valid = false;
                    // printf("error 0, %s\n", str);

                    break;
                }
            }
            str_len = 2;
            str = realloc(str, str_len * sizeof(char));
            index = 0;
            if (last_separator != '*') {
                last_separator = '-';
            }
        } else {
            if (i < len) {
                if (index + 1 == str_len) {
                    str_len *= 2;
                    str = realloc(str, str_len * sizeof(char));
                }
                str[index] = str_num[i];
                str[index + 1] = '\0';
                index++;
            }
        }
    }
    int* l = malloc(2 * sizeof(int));
    l[0] = (int)valid;
    l[1] = n * sign;
    free(str);
    return l;
}

char* str_from_chuck(int n) {
    int text_size = 1;
    char* text = malloc(text_size * sizeof(char));
    text[0] = '\0';

    int units = n % 10;
    n /= 10;
    int tens = n % 10;
    n /= 10;
    int hundreds = n % 10;

    switch (hundreds) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            text = add_str(text, &text_size, "deux");
            break;
        case 3:
            text = add_str(text, &text_size, "trois");
            break;
        case 4:
            text = add_str(text, &text_size, "quatre");
            break;
        case 5:
            text = add_str(text, &text_size, "cinq");
            break;
        case 6:
            text = add_str(text, &text_size, "six");
            break;
        case 7:
            text = add_str(text, &text_size, "sept");
            break;
        case 8:
            text = add_str(text, &text_size, "huit");
            break;
        case 9:
            text = add_str(text, &text_size, "neuf");
            break;
        default:
            break;
    }
    if (hundreds != 0) {
        if (tens == 0 && units == 0 && hundreds != 1) {
            text = add_str(text, &text_size, "-cents");
        } else {
            if (strcmp(text, "")) {
                text = add_str(text, &text_size, "-");
            }
            text = add_str(text, &text_size, "cent");
        }
    }
    if (hundreds != 0 && tens != 0) {
        text = add_str(text, &text_size, "-");
    }
    switch (tens) {
        case 0:
            break;
        case 1:
            if (!(0 < units && units < 7)) {
                text = add_str(text, &text_size, "dix");
            }
            break;
        case 2:
            text = add_str(text, &text_size, "vingt");
            break;
        case 3:
            text = add_str(text, &text_size, "trente");
            break;
        case 4:
            text = add_str(text, &text_size, "quarante");
            break;
        case 5:
            text = add_str(text, &text_size, "cinquante");
            break;
        case 6:
            text = add_str(text, &text_size, "soixante");
            break;
        case 7:
            if (0 < units && units < 7) {
                text = add_str(text, &text_size, "soixante");
            } else {
                text = add_str(text, &text_size, "soixante-dix");
            }
            break;
        case 8:
            text = add_str(text, &text_size, "quatre-vingt");
            if (units == 0) {
                text = add_str(text, &text_size, "s");
            }
            break;
        case 9:
            if (0 < units && units < 7) {
                text = add_str(text, &text_size, "quatre-vingt");
            } else {
                text = add_str(text, &text_size, "quatre-vingt-dix");
            }
            break;
        default:
            break;
    }
    int text_len = (int)strlen(text);

    if (units != 0 && text_len != 0 && text[text_len - 1] != '-') {
        if (strcmp(text, "")) {
            text = add_str(text, &text_size, "-");
        }
    }
    switch (units) {
        case 0:
            break;
        case 1:
            if (tens == 1 || tens == 7 || tens == 9) {
                if (tens != 1) {
                    text = add_str(text, &text_size, "et-");
                }
                text = add_str(text, &text_size, "onze");
            } else {
                if (tens == 2 || tens == 3 || tens == 4 || tens == 5 || tens == 6) {
                    text = add_str(text, &text_size, "et-");
                }
                text = add_str(text, &text_size, "un");
            }
            break;
        case 2:
            if (tens == 1 || tens == 7 || tens == 9) {
                text = add_str(text, &text_size, "douze");
            } else {
                text = add_str(text, &text_size, "deux");
            }
            break;
        case 3:
            if (tens == 1 || tens == 7 || tens == 9) {
                text = add_str(text, &text_size, "treize");
            } else {
                text = add_str(text, &text_size, "trois");
            }
            break;
        case 4:
            if (tens == 1 || tens == 7 || tens == 9) {
                text = add_str(text, &text_size, "quatorze");
            } else {
                text = add_str(text, &text_size, "quatre");
            }
            break;
        case 5:
            if (tens == 1 || tens == 7 || tens == 9) {
                text = add_str(text, &text_size, "quinze");
            } else {
                text = add_str(text, &text_size, "cinq");
            }
            break;
        case 6:
            if (tens == 1 || tens == 7 || tens == 9) {
                text = add_str(text, &text_size, "seize");
            } else {
                text = add_str(text, &text_size, "six");
            }
            break;
        case 7:
            text = add_str(text, &text_size, "sept");
            break;
        case 8:
            text = add_str(text, &text_size, "huit");
            break;
        case 9:
            text = add_str(text, &text_size, "neuf");
            break;
        default:
            break;
    }
    return text;
}

char* str_from_int(int n) {
    int text_size = 1;
    char* text = malloc(text_size * sizeof(char));
    text[0] = '\0';
    if (n < 0) {
        text = add_str(text, &text_size, "moins ");
        n = -n;
    }

    if (n == 0) {
        text = add_str(text, &text_size, "zéro");
        return text;
    }
    int e_0 = n % 1000;
    n /= 1000;
    int e_3 = n % 1000;
    n /= 1000;
    int e_6 = n % 1000;
    n /= 1000;
    int e_9 = n % 1000;

    if (e_9 != 0) {
        char* billions = str_from_chuck(e_9);
        text = add_str(text, &text_size, billions);
        free(billions);
        text = add_str(text, &text_size, " milliard");
        if (e_9 > 1) {
            text = add_str(text, &text_size, "s");
        }
    }
    if (e_6 != 0) {
        if (e_9 != 0) {
            text = add_str(text, &text_size, " ");
        }
        char* millions = str_from_chuck(e_6);
        text = add_str(text, &text_size, millions);
        free(millions);
        text = add_str(text, &text_size, " million");
        if (e_6 > 1) {
            text = add_str(text, &text_size, "s");
        }
    }
    if (e_3 != 0) {
        if (e_9 != 0 || e_6 != 0) {
            text = add_str(text, &text_size, " ");
        }
        if (e_3 == 1) {
            text = add_str(text, &text_size, "mille");
        } else {
            char* thousands = str_from_chuck(e_3);
            text = add_str(text, &text_size, thousands);
            free(thousands);
            text = add_str(text, &text_size, " mille");
        }
    }
    if (e_9 != 0 || e_6 != 0 || e_3 != 0) {
        text = add_str(text, &text_size, " ");
    }
    char* hundreds = str_from_chuck(e_0);
    text = add_str(text, &text_size, hundreds);
    free(hundreds);

    return text;
}

char* str_from_float(float n) {
    int text_size = 1;
    // printf("%f, %d\n", n, (int)n);
    char* text = malloc(text_size*sizeof(char));
    text[0] = '\0';
    if (n < 0){
        text = add_str(text, &text_size, "moins ");
        n = -n;
    }
    char* text_int = str_from_int((int)n);
    text = add_str(text, &text_size, text_int);
    if ((float)(int)n == n) {
        return text;
    }
    n = n - (int)n;
    text_size = (int)strlen(text);
    text = add_str(text, &text_size, " virgule ");
    while (n != (int)n) {
        n *= 10;
        if ((int)n == 0) {
            text = add_str(text, &text_size, "zéro ");
        }
    }
    char* text_dec = str_from_int((int)n);
    text = add_str(text, &text_size, text_dec);
    free(text_dec);
    free(text_int);
    return text;
}
