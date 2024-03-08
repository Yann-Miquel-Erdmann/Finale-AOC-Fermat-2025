#include "syntax_convert.h"
#include "assert.h"
#include "eval_numbers.h"

char* get_first_n(char* s, int n){
    char* s2 = malloc((n+1)*sizeof(char));
    for (int i = 0; i<n; i++){
        s2[i] = s[i];
    }
    s2[n] = '\0';
    return s2;
}

float log_10_entier(int a){
    float i = 1;
    while (a > 0){
        a /= 10;
        i *= 10;
    }
    return i;
}

char** cut_a_b (char*s, int a, int b){
    int len = (int)strlen(s);
    char** l = malloc(3*sizeof(char*));
    char* start;
    char* middle;
    char* end;
    if (a+b > len){
        start = malloc(sizeof(char));
        middle = malloc(sizeof(char));
        end = malloc(sizeof(char));
        strcpy(start, "");
        strcpy(middle, "");
        strcpy(end, "");
        
    }else{
        
        start = malloc((a+b+2)*sizeof(char));
        middle = malloc((len-(a+b)+1)*sizeof(char));
        end = malloc((b+1)*sizeof(char));
        int index = 0;
        
        for (int i = 0; index<a; i++){
            start[i] = s[index];
            index ++;
        }
        start[a] = '*';
        start[a+1] = '\0';
        
        for(int i = 0; index < len-b; i++){
            middle[i] = s[index];
            index ++;
        }
        middle[len-(a+b)] = '\0';
        
        for(int i = 0; index < len; i++){
            end[i] = s[index];
            index ++;
        }
        end[b] = '\0';
    }
    
    l[0] = start;
    l[1] = middle;
    l[2] = end;
    
    return l;
}

char** split_virgule(char* str){
    int len = (int)strlen(str);
    char** l = malloc(2*sizeof(char*));
    
    char* str1 = malloc(len*sizeof(char));
    char* str2 = malloc(len*sizeof(char));
    int num = 1;
    int index = 0;
    
    for(int i = 0; i<len; i++){
        if (i < len - 8 && str[i] == ' ' && str[i+8] == ' '){
            if (str[i+1] == 'v' && str[i+2] == 'i' && str[i+3] == 'r' && str[i+4] == 'g' && str[i+5] == 'u' && str[i+6] == 'l' && str[i+7] == 'e'){
                str1[index] = '\0';
                num = 2;
                i += 8;
                index = 0;
            }else{
                if (num == 1){
                    str1[index] = str[i];
                    index ++;
                }else{
                    str2[index] = str[i];
                    index ++;
                }
            }
        }else{
            if (num == 1){
                str1[index] = str[i];
                index ++;
            }else{
                str2[index] = str[i];
                index ++;
            }
        }
    }
    str2[index] = '\0';
    if (num == 1){
        str2[0] = '\0';
    }
    l[0] = str1;
    l[1] = str2;
    return l;
}

//useless rn
int elem_liste(char* text){
    if (!strcmp(text, EXPR_ENTIER_S)){
        return 0;
    }
    if (!strcmp(text, EXPR_ENTIER_S)){
        return 1;
    }
    if (!strcmp(text, EXPR_ENTIER_S)){
        return 2;
    }
    if (!strcmp(text, EXPR_ENTIER_S)){
        return 3;
    }
    if (!strcmp(text, EXPR_ENTIER_S)){
        return 4;
    }
    if (!strcmp(text, EXPR_ENTIER_S)){
        return 5;
    }
    if (!strcmp(text, EXPR_ENTIER_S)){
        return 6;
    }
    if (!strcmp(text, EXPR_ENTIER_S)){
        return 7;
    }
    if (!strcmp(text, EXPR_ENTIER_S)){
        return 8;
    }
    return -1;
}

void reduce_var_and_num(phrase_t* phrase){
    
    char** result_str = cut_a_b(phrase->text, 9, 1);
    strcat(result_str[0], result_str[2]);
    if (!strcmp(result_str[0], EXPR_ENTIER_S)){
        int* result_num = eval_number(result_str[1], (int)strlen(result_str[1]));
        if (result_num[0]){
            printf("integer: %d\n", result_num[1]);
            phrase->valeur = new_val();
            phrase->phraseId = EXPR_ENTIER;
            set_int(phrase->valeur, result_num[1]);
        }
        free(result_num);
    }
    
    free(result_str[0]);
    free(result_str[1]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 12, (int)strlen(phrase->text)-12);
    char** result_str_2 = cut_a_b(result_str[2], 0, 1);
    char** result_virgule = split_virgule(result_str_2[1]);
    
    
    strcat(result_str_2[0], result_str_2[2]);
    strcat(result_str[0], " virgule ");
    strcat(result_str[0], result_str_2[0]);
    
    if (!strcmp(result_str[0], EXPR_FLOTTANT_S)){
        int* result_num = eval_number(result_virgule[0], (int)strlen(result_virgule[0]));
        int* result_num_2 = eval_number(result_virgule[1], (int)strlen(result_virgule[1]));
        if (result_num[0] && result_num_2[0]){
            float num = (float)result_num[1] + ((float)result_num_2[1])/(log_10_entier(result_num_2[1]));
            printf("float: %f\n", num);
            phrase->phraseId = EXPR_FLOTTANT;
            phrase->valeur = new_val();
            set_float(phrase->valeur, num);
        }
        free(result_num);
        free(result_num_2);
    }
    free(result_str[0]);
    free(result_str[1]);
    free(result_str[2]);
    free(result_str);
    free(result_str_2[0]);
    free(result_str_2[1]);
    free(result_str_2[2]);
    free(result_str_2);
    free(result_virgule[0]);
    free(result_virgule[1]);
    free(result_virgule);
    
    
    result_str = cut_a_b(phrase->text, 12, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXPR_BOOLEEN_S)){
        if (!strcmp(result_str[1], "vrai")){
            printf("booléen: vrai\n");
            phrase->phraseId = EXPR_CHAINE;
            phrase->valeur = new_val();
            set_bool(phrase->valeur, true);
        }else if(!strcmp(result_str[1], "faux")){
            printf("booléen: faux\n");
            phrase->phraseId = EXPR_CHAINE;
            phrase->valeur = new_val();
            set_bool(phrase->valeur, false);
        }
    }
    
    free(result_str[0]);
    free(result_str[1]);
    free(result_str[2]);
    free(result_str);
    
    //
    result_str = cut_a_b(phrase->text, 26, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXPR_CHAINE_S)){
        if (result_str[1][0] == '"' && result_str[1][(int)strlen(result_str[1])-1] == '"'){
            printf("chaine: %s\n", result_str[1]);
            phrase->phraseId = EXPR_CHAINE;
            free(phrase->text);
            phrase->textLen = (int)strlen(result_str[1]);
            strcpy(phrase->text, result_str[1]);
            phrase->textSize = phrase->textLen;
        }
    }
    
    free(result_str[0]);
    free(result_str[1]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 5, 31);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], DEFINITION_VARIABLE_AVEC_INIT_S)){
        printf("variable init: %s\n", result_str[1]);
        phrase->phraseId = DEFINITION_VARIABLE_AVEC_INIT;
        phrase->variable_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 5, 14);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], CREATION_VARIABLE_SANS_INIT_S)){
        printf("variable sans init: %s\n", result_str[1]);
        phrase->phraseId = CREATION_VARIABLE_SANS_INIT;
        phrase->variable_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 12, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], ACCESSION_VARIABLE_S)){
        printf("valeur de la variable %s\n", result_str[1]);
        phrase->phraseId = ACCESSION_VARIABLE;
        phrase->variable_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 16, 12);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], MODIFICATION_VARIABLE_S)){
        printf("modification de la variable %s\n", result_str[1]);
        phrase->phraseId = MODIFICATION_VARIABLE;
        phrase->variable_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 5, 16);
    strcat(result_str[0], result_str[2]);
    
    
    if (!strcmp(result_str[0], CREATION_LISTE_S)){
        printf("création de la liste %s\n", result_str[1]);
        phrase->phraseId = CREATION_LISTE;
        phrase->liste_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 37, 15);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0],ACCESSION_LISTE_S)){
        printf("accession de la liste %s\n", result_str[1]);
        phrase->phraseId = ACCESSION_LISTE;
        phrase->liste_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 34, 21);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0],MODIFICATION_LISTE_S)){
        printf("modification de la liste %s\n", result_str[1]);
        phrase->phraseId = MODIFICATION_LISTE;
        phrase->liste_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 20, 3);
    strcat(result_str[0], result_str[2]);
    if (!strcmp(result_str[0],AJOUT_LISTE_S)){
        printf("ajout à la liste %s\n", result_str[1]);
        phrase->phraseId = AJOUT_LISTE;
        phrase->liste_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 20, 24);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0],SUPPRESSION_LISTE_S)){
        printf("suppression élément de la liste %s\n", result_str[1]);
        phrase->phraseId = SUPPRESSION_LISTE;
        phrase->liste_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 22, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0],TAILLE_LISTE_S)){
        printf("la taille de la liste %s\n", result_str[1]);
        phrase->phraseId = TAILLE_LISTE;
        phrase->liste_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
}

phrase_t* tokenise(phrase_t* phrase){
    
    
    return phrase;
}

phrase_t* calculate_args(phrase_t* phrase){
    
    
    return phrase;
}
