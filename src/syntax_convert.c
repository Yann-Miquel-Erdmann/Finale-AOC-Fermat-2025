#include "syntax_convert.h"
#include "assert.h"
#include "eval_numbers.h"
#include "custom_error.h"

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
        
        start = malloc(len*sizeof(char));
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

char** split_word(char* str, char* separator){
    int len = (int)strlen(str);
    char** l = malloc(2*sizeof(char*));
    
    int sep_len = (int)strlen(separator);
    
    char* str1 = malloc((len+1)*sizeof(char));
    char* str2 = malloc((len+1)*sizeof(char));
    int num = 1;
    int index = 0;
    
    for(int i = 0; i<len; i++){
        bool broken = false;
        if (i < len - sep_len && str[i] == ' ' && str[i+sep_len+1] == ' '){
            for (int j = 0; j < sep_len; j++){
                if (str[i+1+j] != separator[j]){
                    broken = true;
                    break;
                }
            }
            if (!broken){
                num = 2;
                i += sep_len+1;
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

int elem_liste(char* text){
    printf("%s\n", text);
    if (!strcmp(text, SOMME_S)){
        return SOMME;
    }
    if (!strcmp(text, DIFFERENCE_S)){
        return DIFFERENCE;
    }
    if (!strcmp(text, PRODUIT_S)){
        return PRODUIT;
    }
    if (!strcmp(text, QUOTIENT_S)){
        return QUOTIENT;
    }
    if (!strcmp(text, QUOTIENT_ENTIER_S)){
        return QUOTIENT_ENTIER;
    }
    if (!strcmp(text, RESTE_S)){
        return RESTE;
    }
    if (!strcmp(text, NEGATION_BOOLEENNE_S)){
        return NEGATION_BOOLEENNE;
    }
    return -1;
}

void reduce_var_and_num(phrase_t* phrase){
    if (phrase == NULL){
        return;
    }
    char** result_str;
    
    test_expr_entier(phrase);
    if (phrase->phraseId != -1){
        return;
    }
    
    test_expr_flottant(phrase);
    if (phrase->phraseId != -1){
        return;
    }
    
    test_expr_booleen(phrase);
    if (phrase->phraseId != -1){
        return;
    }
    
    char** result_str_2;
    
    result_str = cut_a_b(phrase->text, 26, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXPR_CHAINE_S)){
        if (result_str[1][0] == '"' && result_str[1][(int)strlen(result_str[1])-1] == '"'){
            printf("chaine: %s\n", result_str[1]);
            phrase->phraseId = EXPR_CHAINE;
            phrase->textLen = (int)strlen(result_str[1]);
            strcpy(phrase->text, result_str[1]);
            phrase->textSize = phrase->textLen;
            
            free(result_str[0]);
            free(result_str[1]);
            free(result_str[2]);
            free(result_str);
            
            return;
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
    
    result_str = cut_a_b(phrase->text, 5, 53);
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], DEFINITION_FONCTION_S)){
        printf("definition de la fonction %s\n", result_str[1]);
        phrase->phraseId = DEFINITION_FONCTION;
        phrase->function_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 20, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXECUTION_FONCTION_S)){
        printf("execution de la fonction %s\n", result_str[1]);
        phrase->phraseId = EXECUTION_FONCTION;
        phrase->function_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 36, 1);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], APPEL_VALEUR_FONCTION_S)){
        printf("appel de la fonction %s\n", result_str[1]);
        phrase->phraseId = APPEL_VALEUR_FONCTION;
        phrase->function_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 5, 11);
    result_str_2 = split_word(result_str[1], "une fonction qui lorsqu'elle est appelée avec");
    strcat(result_str[0], " une fonction qui lorsqu'elle est appelée avec *");
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], DEFINITION_FONCTION_ARGUMENT_S)){
        printf("definition de la fonction %s avec arguments\n", result_str[1]);
        phrase->phraseId = DEFINITION_FONCTION_ARGUMENT;
        phrase->function_call = result_str_2[0];
        phrase->variable_call = result_str_2[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    free(result_str_2);
    
    result_str = cut_a_b(phrase->text, 20, 22);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], EXECUTION_FONCTION_ARGUMENT_S)){
        printf("execution de la fonction %s avec arguments\n", result_str[1]);
        phrase->phraseId = EXECUTION_FONCTION_ARGUMENT;
        phrase->function_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
    
    result_str = cut_a_b(phrase->text, 36, 22);
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], APPEL_VALEUR_FONCTION_ARGUMENT_S)){
        printf("appel de la fonction %s avec arguments\n", result_str[1]);
        phrase->phraseId = APPEL_VALEUR_FONCTION_ARGUMENT;
        phrase->function_call = result_str[1];
        
    }else{
        free(result_str[1]);
    }
    
    free(result_str[0]);
    free(result_str[2]);
    free(result_str);
}

int value_type(phrase_t* p1, phrase_t* p2){
    if (p1->valeur->type == FLOAT || p2->valeur->type == FLOAT){
        return FLOAT;
    }
    return INT;
}

float return_value(phrase_t* p){
    switch (p->valeur->type) {
        case INT:
            return (float)get_int(p->valeur);
            
        case FLOAT:
            return get_float(p->valeur);
        
        case BOOL:
            return (float)get_bool(p->valeur);
            
        default:
            return -1;
    }
}

void tokenise(phrase_t* phrase){
    bool valid = true;
    switch (elem_liste(phrase->text)) {
        case SOMME:
            phrase->phraseId = SOMME;
            for (int i = 0; i< 2 && valid; i++){
                tokenise(phrase->args[i]);
                if (phrase->args[i]->phraseId == -1){
                    valid = false;
                }
            }
            if (valid){
                phrase->valeur = new_val();
                set_float(phrase->valeur, return_value(phrase->args[0]) + return_value(phrase->args[1]));
                if (!(phrase->args[0]->valeur->type == FLOAT && phrase->args[1]->valeur->type == FLOAT)){
                    set_int(phrase->valeur, get_float(phrase->valeur));
                }
            }
            break;

        case DIFFERENCE:
            phrase->phraseId = DIFFERENCE;
            for (int i = 0; i< 2 && valid; i++){
                tokenise(phrase->args[i]);
                if (phrase->args[i]->phraseId == -1){
                    valid = false;
                }
            }
            if (valid){
                phrase->valeur = new_val();
                set_float(phrase->valeur, return_value(phrase->args[0]) - return_value(phrase->args[1]));
                if (!(phrase->args[0]->valeur->type == FLOAT && phrase->args[1]->valeur->type == FLOAT)){
                    set_int(phrase->valeur, get_float(phrase->valeur));
                }
            }
            break;
        case PRODUIT:
            phrase->phraseId = PRODUIT;
            for (int i = 0; i< 2 && valid; i++){
                tokenise(phrase->args[i]);
                if (phrase->args[i]->phraseId == -1){
                    valid = false;
                }
            }
            if (valid){
                phrase->valeur = new_val();
                set_float(phrase->valeur, return_value(phrase->args[0]) * return_value(phrase->args[1]));
                if (!(phrase->args[0]->valeur->type == FLOAT && phrase->args[1]->valeur->type == FLOAT)){
                    set_int(phrase->valeur, get_float(phrase->valeur));
                }
            }
            break;
        case QUOTIENT:
            phrase->phraseId = PRODUIT;
            for (int i = 0; i< 2 && valid; i++){
                tokenise(phrase->args[i]);
                if (phrase->args[i]->phraseId == -1){
                    valid = false;
                }
            }
            if (valid){
                if (return_value(phrase->args[0]) * return_value(phrase->args[1]) == 0){
                    phrase->error = true;
                    custom_error("Division par 0", phrase);
                }
                phrase->valeur = new_val();
                set_float(phrase->valeur, return_value(phrase->args[0]) * return_value(phrase->args[1]));
                if (!(phrase->args[0]->valeur->type == FLOAT && phrase->args[1]->valeur->type == FLOAT)){
                    set_int(phrase->valeur, get_float(phrase->valeur));
                }
            }
            break;
        default:
            reduce_var_and_num(phrase);
    }
    
}

phrase_t* calculate_args(phrase_t* phrase){
    
    
    return phrase;
}
