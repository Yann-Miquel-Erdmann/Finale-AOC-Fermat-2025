#include <assert.h>
#include <stdio.h>

#include "../src/eval_numbers.h"
#include "../src/interpreter.h"
#include "../src/parser.h"
#include "../src/structures/function.h"
#include "../src/structures/phrase.h"
#include "../src/structures/val.h"
#include "../src/syntax_convert.h"

int test_number(void) {
    // char* s = "moins trois-cent-vingt-sept millions deux-cent-quatre-vingt-douze mille six-cent-trente-huit";
    // char* s = "cinq cents";
    char* s;
    char* s_l[100] = {"trente-trois-mille-quatre-cents", "trente-trois-mille-quatre-cent-un", "trente-trois-mille-quatre-cent-deux", "trente-trois-mille-quatre-cent-trois", "trente-trois-mille-quatre-cent-quatre", "trente-trois-mille-quatre-cent-cinq", "trente-trois-mille-quatre-cent-six", "trente-trois-mille-quatre-cent-sept", "trente-trois-mille-quatre-cent-huit", "trente-trois-mille-quatre-cent-neuf", "trente-trois-mille-quatre-cent-dix", "trente-trois-mille-quatre-cent-onze", "trente-trois-mille-quatre-cent-douze", "trente-trois-mille-quatre-cent-treize", "trente-trois-mille-quatre-cent-quatorze", "trente-trois-mille-quatre-cent-quinze", "trente-trois-mille-quatre-cent-seize", "trente-trois-mille-quatre-cent-dix-sept", "trente-trois-mille-quatre-cent-dix-huit", "trente-trois-mille-quatre-cent-dix-neuf", "trente-trois-mille-quatre-cent-vingt", "trente-trois-mille-quatre-cent-vingt-et-un", "trente-trois-mille-quatre-cent-vingt-deux", "trente-trois-mille-quatre-cent-vingt-trois", "trente-trois-mille-quatre-cent-vingt-quatre", "trente-trois-mille-quatre-cent-vingt-cinq", "trente-trois-mille-quatre-cent-vingt-six", "trente-trois-mille-quatre-cent-vingt-sept", "trente-trois-mille-quatre-cent-vingt-huit", "trente-trois-mille-quatre-cent-vingt-neuf", "trente-trois-mille-quatre-cent-trente", "trente-trois-mille-quatre-cent-trente-et-un", "trente-trois-mille-quatre-cent-trente-deux", "trente-trois-mille-quatre-cent-trente-trois", "trente-trois-mille-quatre-cent-trente-quatre", "trente-trois-mille-quatre-cent-trente-cinq", "trente-trois-mille-quatre-cent-trente-six", "trente-trois-mille-quatre-cent-trente-sept", "trente-trois-mille-quatre-cent-trente-huit", "trente-trois-mille-quatre-cent-trente-neuf", "trente-trois-mille-quatre-cent-quarante", "trente-trois-mille-quatre-cent-quarante-et-un", "trente-trois-mille-quatre-cent-quarante-deux", "trente-trois-mille-quatre-cent-quarante-trois", "trente-trois-mille-quatre-cent-quarante-quatre", "trente-trois-mille-quatre-cent-quarante-cinq", "trente-trois-mille-quatre-cent-quarante-six", "trente-trois-mille-quatre-cent-quarante-sept", "trente-trois-mille-quatre-cent-quarante-huit", "trente-trois-mille-quatre-cent-quarante-neuf", "trente-trois-mille-quatre-cent-cinquante", "trente-trois-mille-quatre-cent-cinquante-et-un", "trente-trois-mille-quatre-cent-cinquante-deux", "trente-trois-mille-quatre-cent-cinquante-trois", "trente-trois-mille-quatre-cent-cinquante-quatre", "trente-trois-mille-quatre-cent-cinquante-cinq", "trente-trois-mille-quatre-cent-cinquante-six", "trente-trois-mille-quatre-cent-cinquante-sept", "trente-trois-mille-quatre-cent-cinquante-huit", "trente-trois-mille-quatre-cent-cinquante-neuf", "trente-trois-mille-quatre-cent-soixante", "trente-trois-mille-quatre-cent-soixante-et-un", "trente-trois-mille-quatre-cent-soixante-deux", "trente-trois-mille-quatre-cent-soixante-trois", "trente-trois-mille-quatre-cent-soixante-quatre", "trente-trois-mille-quatre-cent-soixante-cinq", "trente-trois-mille-quatre-cent-soixante-six", "trente-trois-mille-quatre-cent-soixante-sept", "trente-trois-mille-quatre-cent-soixante-huit", "trente-trois-mille-quatre-cent-soixante-neuf", "trente-trois-mille-quatre-cent-soixante-dix", "trente-trois-mille-quatre-cent-soixante-et-onze", "trente-trois-mille-quatre-cent-soixante-douze", "trente-trois-mille-quatre-cent-soixante-treize", "trente-trois-mille-quatre-cent-soixante-quatorze", "trente-trois-mille-quatre-cent-soixante-quinze", "trente-trois-mille-quatre-cent-soixante-seize", "trente-trois-mille-quatre-cent-soixante-dix-sept", "trente-trois-mille-quatre-cent-soixante-dix-huit", "trente-trois-mille-quatre-cent-soixante-dix-neuf", "trente-trois-mille-quatre-cent-quatre-vingts", "trente-trois-mille-quatre-cent-quatre-vingt-un", "trente-trois-mille-quatre-cent-quatre-vingt-deux", "trente-trois-mille-quatre-cent-quatre-vingt-trois", "trente-trois-mille-quatre-cent-quatre-vingt-quatre", "trente-trois-mille-quatre-cent-quatre-vingt-cinq", "trente-trois-mille-quatre-cent-quatre-vingt-six", "trente-trois-mille-quatre-cent-quatre-vingt-sept", "trente-trois-mille-quatre-cent-quatre-vingt-huit", "trente-trois-mille-quatre-cent-quatre-vingt-neuf", "trente-trois-mille-quatre-cent-quatre-vingt-dix", "trente-trois-mille-quatre-cent-quatre-vingt-onze", "trente-trois-mille-quatre-cent-quatre-vingt-douze", "trente-trois-mille-quatre-cent-quatre-vingt-treize", "trente-trois-mille-quatre-cent-quatre-vingt-quatorze", "trente-trois-mille-quatre-cent-quatre-vingt-quinze", "trente-trois-mille-quatre-cent-quatre-vingt-seize", "trente-trois-mille-quatre-cent-quatre-vingt-dix-sept", "trente-trois-mille-quatre-cent-quatre-vingt-dix-huit", "trente-trois-mille-quatre-cent-quatre-vingt-dix-neuf"};

    for (int i = 0; i < 100; i++) {
        s = s_l[i];

        int* result = eval_number(s, (int)strlen(s));

        if (result[0] == 1) {
            // printf("%d\n", result[1]);
        } else {
            // printf("\"%s\" is not a valid number\n", s);
            break;
        }
        free(result);
    }
    return 0;
}

void test_parse(void) {
    FILE* f = fopen("testing/test.FC", "r");
    assert(f != NULL);

    phrase_t* p = parse_file(f);
    printPhrase(p);
    free_phrase(p);
    fclose(f);
}

/*void test_val(void) {
    val_t* v1 = new_val_t(UNDEFINED);
    val_t* v2 = new_val_t(UNDEFINED);
    val_t* v3 = new_val_t(UNDEFINED);
    set_int(v1, 45);
    set_float(v2, 50.320);
    set_bool(v3, true);

    // printf("%d\n", get_int(v1));
    // printf("%f\n", get_float(v2));
    // printf("%d\n", get_bool(v3));

    set_int(v3, 450207);
    // printf("%d\n", get_int(v3));

    set_bool(v3, false);
    // printf("%d\n", get_bool(v3));

    free_val_t(v1);
    free_val_t(v2);
    free_val_t(v3);
}*/

int main(int argc, char const* argv[]) {
    // str_from_int(-2000289635);
    // printf("%s\n", str_from_float(12.7));

    // test_val();

    FILE* f = fopen("testing/test.FC", "r");
    assert(f != NULL);

    phrase_t* p = parse_file(f);

    char* nom = malloc(sizeof(char));
    nom[0] = '\0';
    function_t* function = new_function(nom, p);

    function_list_t* function_list = new_function_list();
    function_list_t* function_call_list = new_function_list();
    addToFunctionList(function_list, function);
    tokenise(p, function, function_list, function_call_list);

    // printPhrase(p);
    for (int i = 0; i < function_list->function_list_len; i++) {
        // printf("function: '%s'\n", function_list->function_list[i]->nom);
        printPhrase(function_list->function_list[i]->ast);
        // printf("======\n\n");
    }

    // printf("====== Début execution ======\n\n");
    interpreter(function, function_list, NULL, 0);

    free_function_list(function_list);
    fclose(f);
    return 0;
}
