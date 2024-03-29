#include "../instructions.h"

char** split_args(char* args) { // TODO à optimiser (remplacer realloc de taille 1 par taille *2)
    char** result = malloc(sizeof(char*));
    int result_size = 1;
    int result_index = 0;
    
    char* curr_arg = malloc(sizeof(char));
    int curr_arg_size = 1;
    int curr_arg_index = 0;
    
    int arg_len = (int)strlen(args);
    
    for (int i = 0; i<arg_len; i++){
        if (args[i] == ',') {
            result[result_index] = curr_arg;
            result_index++;
            result_size++;
            result = realloc(result, result_size * sizeof(char*));
            
            curr_arg = malloc(sizeof(char));
            curr_arg_size = 1;
            curr_arg_index = 0;
        } else {
            curr_arg[curr_arg_index] = args[i];
            curr_arg_index++;
            curr_arg_size++;
            curr_arg = realloc(curr_arg, curr_arg_size * sizeof(char));
        }
    }
    result[result_index] = curr_arg;
    return result;
}
bool test_inst_def_func_args(phrase_t* phrase, function_list_t* function_list) {
    if (phrase->phraseId != -1 || strlen(phrase->text) <= 16) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 5, 11);
    char** result_str_2 = split_word(result_str[1], "une fonction qui lorsqu'elle est appelée avec");


    if (!strcmp(result_str_2[1], "")) {
        free_pointers(result_str);
        free(result_str_2);
        return false;
    }
    strcat(result_str[0], " une fonction qui lorsqu'elle est appelée avec *");
    strcat(result_str[0], result_str[2]);
    
    if (!strcmp(result_str[0], DEFINITION_FONCTION_ARGUMENT_S)) {
        char** result_str_3 = split_args(result_str_2[1]);
        for (int i = 0; i < strlen(result_str_2[1]); i++) {
            if (result_str_3[i] == NULL) {
                break;
            }
            printf("arg %d: %s\n", i, result_str_3[i]);
        }
        printf("definition de la fonction %s avec arguments\n", result_str_2[0]);
        phrase->phraseId = DEFINITION_FONCTION_ARGUMENT;

        phrase->function = new_function(result_str_2[0], phrase);
        
        phrase_t* p2 = special_copy_phrase(phrase);
        p2->phraseId = MAIN_PHRASE;
        strcpy(p2->text, "*.");
        addToFunctionList(function_list, phrase->function);

    } else {
        free(result_str[1]);
    }

    free_pointers(result_str);
    free(result_str_2);

    // renvoie true si l'expression est une def func args
    return phrase->phraseId != -1;
}
