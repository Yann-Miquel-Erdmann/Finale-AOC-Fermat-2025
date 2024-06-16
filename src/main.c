#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "eval_numbers.h"
#include "interpreter.h"
#include "parser.h"
#include "structures/function.h"
#include "structures/phrase.h"
#include "structures/val.h"
#include "syntax_convert.h"

int main(int argc, char const* argv[]) {
    if (argc == 2) {
        // help
        if (strcmp(argv[1], "-h") == 0) {
            // printf("Usage: %s <file>\n", argv[0]);
            return 0;
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

        char* nom = malloc(sizeof(char));
        nom[0] = '\0';
        function_t* function = new_function(nom, p);

        function_list_t* function_list = new_function_list();
        function_list_t* function_call_list = new_function_list();
        addToFunctionList(function_list, function);
        
        int i = 0;
        tokenise(p, function, function_list, function_call_list, &i, NULL,false, NULL);
        // exit(1);
        interpreter(function, function_list, NULL, 0);

        free_phrase(p);
        free_function_list(function_list);
        fclose(f);
        return 0;
    } else {
        custom_error("Usage: ./interpreter <file>", NULL, NULL);
        return 1;
    }
}
