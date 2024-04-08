#include "../instructions.h"

char** split_args(char* args, int* len) {  // TODO à optimiser (remplacer realloc de taille 1 par taille *2)
    char** result = malloc(sizeof(char*) * DEFAULT_RES_SIZE);
    int result_size = DEFAULT_RES_SIZE;
    int result_len = 0;

    char* curr_arg = malloc(sizeof(char) * DEFAULT_CURR_SIZE);
    int curr_arg_size = DEFAULT_CURR_SIZE;
    int curr_arg_len = 0;

    int arg_len = 0;
    arg_len = (int)strlen(args);
    printf("%d\n", arg_len);
    for (int i = 0; i < arg_len; i++) {
        if (args[i] == ',') {
            if (curr_arg_len == curr_arg_size) {
                curr_arg_size *= 2;
                curr_arg = realloc(curr_arg, curr_arg_size * sizeof(char));
            }
            curr_arg[curr_arg_len] = '\0';
            curr_arg_len++;

            if (result_len == result_size) {
                result_size *= 2;
                result = realloc(result, result_size * sizeof(char*));
            }

            result[result_len] = curr_arg;
            result_len++;

            curr_arg = malloc(sizeof(char) * DEFAULT_CURR_SIZE);
            curr_arg_size = DEFAULT_CURR_SIZE;
            curr_arg_len = 0;
        } else {
            if (curr_arg_len == curr_arg_size) {
                curr_arg_size *= 2;
                curr_arg = realloc(curr_arg, curr_arg_size * sizeof(char));
            }
            curr_arg[curr_arg_len] = args[i];
            curr_arg_len++;
        }
    }

    if (curr_arg_len == curr_arg_size) {
        curr_arg_size *= 2;
        curr_arg = realloc(curr_arg, curr_arg_size * sizeof(char));
    }
    curr_arg[curr_arg_len] = '\0';
    curr_arg_len++;

    if (result_len == result_size) {
        result_size *= 2;
        result = realloc(result, result_size * sizeof(char*));
    }
    result[result_len] = curr_arg;
    result_len++;

    *len = result_len;
    return result;
}

bool test_inst_def_func_args(phrase_t* phrase, function_list_t* function_list) {
    if (phrase->phraseId != -1 || strlen(phrase->text) <= 16) {
        return false;
    }

    char** result_str = cut_a_b(phrase->text, 5, 11);
    char** result_str_2 = split_word(result_str[1], "une fonction qui lorsqu'elle est appelée avec");

    if (!strcmp(result_str_2[1], "")) {
        free(result_str[1]);
        free_pointers(result_str);
        free(result_str_2[0]);
        free(result_str_2[1]);
        free(result_str_2);
        return false;
    }
    strcat(result_str[0], " une fonction qui lorsqu'elle est appelée avec *");
    strcat(result_str[0], result_str[2]);

    if (!strcmp(result_str[0], DEFINITION_FONCTION_ARGUMENT_S)) {
        int len = 0;
        char** result_str_3 = split_args(result_str_2[1], &len);
        // printf("result_str_2 %s\n",result_str_2[1]);
        // printf("definition de la fonction %s avec arguments\n", result_str_2[0]);
        phrase->phraseId = DEFINITION_FONCTION_ARGUMENT;

        function_t* new_func = new_function(result_str_2[0], phrase);

        for (int i = 0; i < len; i++) {
            addToVariableList(new_func->env, new_variable(result_str_3[i], new_val_t(UNDEFINED)));

        }

        phrase->function = new_func;
        printf("new_func nom %s\n", new_func->nom);
        addToFunctionList(function_list, new_func);
        free(result_str_3);
    }
    free(result_str[1]);
    free_pointers(result_str);
    free(result_str_2[1]);
    free(result_str_2);

    // renvoie true si l'expression est une def func args
    return phrase->phraseId != -1;
}
