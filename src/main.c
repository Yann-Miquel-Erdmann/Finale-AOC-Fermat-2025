#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "eval_numbers.h"
#include "interpreter.h"
#include "parser.h"
#include "structures/function.h"
#include "structures/phrase.h"
#include "structures/val.h"
#include "syntax_convert.h"
#include "timeout.h"
#include "custom_error.h"
#include "safe_alloc.h"

int main(int argc, char const* argv[]) {
    if (argc == 2) {
        // help
        if (strcmp(argv[1], "-h") == 0) {
            printf("Utilisation: %s <file> [--timeout timeout] [--input input_file] [--ignore_errors]\n", argv[0]);
            return 0;
        }
    }
    if (argc == 1){
        custom_error("Utilisation: ./interpreter <file> [--timeout timeout] [--input input_file] [--ignore_errors]1", NULL, NULL);
    }else{
        if (access(argv[1], F_OK) != 0) {
            custom_error("Le fichier source n'existe pas", NULL, NULL);
        }
    }
    
    int require_argument = 0;
    for (int i = 2; i< argc; i++){
        if (argv[i][0] == '-' && argv[i][1] == '-'){
            if (require_argument){
                char error[64]; // argument de taille au plus 15, par de buffer overflow possible
                sprintf(error, "Le paramètre \"%s\" requiert un argument", argv[i-1]);
                custom_error(error, NULL, NULL);
            }
            if (!strcmp(argv[i], "--ignore_errors")){
                set_ignore();
            }else if (!strcmp(argv[i], "--input")){
                require_argument = 1;
            }else if (!strcmp(argv[i], "--timeout")){
                require_argument = 2;
            }else{
                char* error = safe_alloc(NULL, (40+sizeof(argv[i]))*sizeof(char)); // besoin du safe_alloc car taille de l'entrée utilisateur n'est pas définie
                sprintf(error, "Le paramètre \"%s\" n'est pas reconnu.", argv[i]);
                custom_error(error, NULL, NULL);
            }
        }else{
            switch (require_argument) {
                case 0:{
                    char error[64]; // argument de taille au plus 15, pas de buffer overflow possible
                    sprintf(error, "Le paramètre \"%s\" ne prend par d'argument", argv[i-1]);
                    custom_error(error, NULL, NULL);
                    break;
                }
                case 1:
                    if (access(argv[i], F_OK) != 0) {
                        custom_error("Le fichier d'input n'existe pas.", NULL, NULL);
                    }
                    fclose(stdin);
                    stdin = fopen(argv[i], "r");
                    require_argument = false;
                    break;
                case 2:
                    setTimeout(atoi(argv[i]));
                    require_argument = false;
                    break;
            }
            
        }
    }
    if (require_argument){
        char error[64]; // argument de taille au plus 15, pas de buffer overflow possible
        sprintf(error, "Le paramètre \"%s\" requiert un argument", argv[argc-1]);
        custom_error(error, NULL, NULL);
    }
    
    // check if file exists
    if (access(argv[1], F_OK) != 0) {
        custom_error("Le fichier n'existe pas", NULL, NULL);
    }
    
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        custom_error("Impossible d'ouvrir le fichier", NULL, NULL);
    }
    
    phrase_t* p = parse_file(f);
    char* nom = safe_alloc(NULL, sizeof(char));
    nom[0] = '\0';
    function_t* function = new_function(nom, p);

    function_list_t* function_list = new_function_list();
    function_list_t* function_call_list = new_function_list();
    addToFunctionList(function_list, function);
    
    int i = 0;
            
    tokenise(p, function, function_list, function_call_list, &i, NULL,false, NULL);

    interpreter(function, function_list, NULL, 0);

    free_phrase(p);
    free_function_list(function_list);
    fclose(f);
    return 0;

}
