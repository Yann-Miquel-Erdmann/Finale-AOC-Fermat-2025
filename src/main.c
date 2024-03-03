#include <stdio.h>

#include "eval_numbers.h"

int main(void) {
    char* instruction = "Soit x la variable initialisée à La somme de La somme de L'entier 0? et de L'entier 1?? et de La somme de L'entier 2? et de L'entier 3???.";
    // instruction = "L'entier 3.";
    expr_t* expr = new_expr();
    expr->len = (int)strlen(instruction) + 1;
    expr->text = realloc(expr->text, expr->len);
    strcpy(expr->text, instruction);
    split_expr(expr);
    print_expr(expr);
    free_expr(expr);

    char* s = "moins trois-cent-vingt-sept millions deux-cent-quatre-vingt-douze mille six-cent-trente-huit";
    s = "cinq cents";
    char* s_l[100] = {"trente-trois-mille-quatre-cents", "trente-trois-mille-quatre-cent-un", "trente-trois-mille-quatre-cent-deux", "trente-trois-mille-quatre-cent-trois", "trente-trois-mille-quatre-cent-quatre", "trente-trois-mille-quatre-cent-cinq", "trente-trois-mille-quatre-cent-six", "trente-trois-mille-quatre-cent-sept", "trente-trois-mille-quatre-cent-huit", "trente-trois-mille-quatre-cent-neuf", "trente-trois-mille-quatre-cent-dix", "trente-trois-mille-quatre-cent-onze", "trente-trois-mille-quatre-cent-douze", "trente-trois-mille-quatre-cent-treize", "trente-trois-mille-quatre-cent-quatorze", "trente-trois-mille-quatre-cent-quinze", "trente-trois-mille-quatre-cent-seize", "trente-trois-mille-quatre-cent-dix-sept", "trente-trois-mille-quatre-cent-dix-huit", "trente-trois-mille-quatre-cent-dix-neuf", "trente-trois-mille-quatre-cent-vingt", "trente-trois-mille-quatre-cent-vingt-et-un", "trente-trois-mille-quatre-cent-vingt-deux", "trente-trois-mille-quatre-cent-vingt-trois", "trente-trois-mille-quatre-cent-vingt-quatre", "trente-trois-mille-quatre-cent-vingt-cinq", "trente-trois-mille-quatre-cent-vingt-six", "trente-trois-mille-quatre-cent-vingt-sept", "trente-trois-mille-quatre-cent-vingt-huit", "trente-trois-mille-quatre-cent-vingt-neuf", "trente-trois-mille-quatre-cent-trente", "trente-trois-mille-quatre-cent-trente-et-un", "trente-trois-mille-quatre-cent-trente-deux", "trente-trois-mille-quatre-cent-trente-trois", "trente-trois-mille-quatre-cent-trente-quatre", "trente-trois-mille-quatre-cent-trente-cinq", "trente-trois-mille-quatre-cent-trente-six", "trente-trois-mille-quatre-cent-trente-sept", "trente-trois-mille-quatre-cent-trente-huit", "trente-trois-mille-quatre-cent-trente-neuf", "trente-trois-mille-quatre-cent-quarante", "trente-trois-mille-quatre-cent-quarante-et-un", "trente-trois-mille-quatre-cent-quarante-deux", "trente-trois-mille-quatre-cent-quarante-trois", "trente-trois-mille-quatre-cent-quarante-quatre", "trente-trois-mille-quatre-cent-quarante-cinq", "trente-trois-mille-quatre-cent-quarante-six", "trente-trois-mille-quatre-cent-quarante-sept", "trente-trois-mille-quatre-cent-quarante-huit", "trente-trois-mille-quatre-cent-quarante-neuf", "trente-trois-mille-quatre-cent-cinquante", "trente-trois-mille-quatre-cent-cinquante-et-un", "trente-trois-mille-quatre-cent-cinquante-deux", "trente-trois-mille-quatre-cent-cinquante-trois", "trente-trois-mille-quatre-cent-cinquante-quatre", "trente-trois-mille-quatre-cent-cinquante-cinq", "trente-trois-mille-quatre-cent-cinquante-six", "trente-trois-mille-quatre-cent-cinquante-sept", "trente-trois-mille-quatre-cent-cinquante-huit", "trente-trois-mille-quatre-cent-cinquante-neuf", "trente-trois-mille-quatre-cent-soixante", "trente-trois-mille-quatre-cent-soixante-et-un", "trente-trois-mille-quatre-cent-soixante-deux", "trente-trois-mille-quatre-cent-soixante-trois", "trente-trois-mille-quatre-cent-soixante-quatre", "trente-trois-mille-quatre-cent-soixante-cinq", "trente-trois-mille-quatre-cent-soixante-six", "trente-trois-mille-quatre-cent-soixante-sept", "trente-trois-mille-quatre-cent-soixante-huit", "trente-trois-mille-quatre-cent-soixante-neuf", "trente-trois-mille-quatre-cent-soixante-dix", "trente-trois-mille-quatre-cent-soixante-et-onze", "trente-trois-mille-quatre-cent-soixante-douze", "trente-trois-mille-quatre-cent-soixante-treize", "trente-trois-mille-quatre-cent-soixante-quatorze", "trente-trois-mille-quatre-cent-soixante-quinze", "trente-trois-mille-quatre-cent-soixante-seize", "trente-trois-mille-quatre-cent-soixante-dix-sept", "trente-trois-mille-quatre-cent-soixante-dix-huit", "trente-trois-mille-quatre-cent-soixante-dix-neuf", "trente-trois-mille-quatre-cent-quatre-vingts", "trente-trois-mille-quatre-cent-quatre-vingt-un", "trente-trois-mille-quatre-cent-quatre-vingt-deux", "trente-trois-mille-quatre-cent-quatre-vingt-trois", "trente-trois-mille-quatre-cent-quatre-vingt-quatre", "trente-trois-mille-quatre-cent-quatre-vingt-cinq", "trente-trois-mille-quatre-cent-quatre-vingt-six", "trente-trois-mille-quatre-cent-quatre-vingt-sept", "trente-trois-mille-quatre-cent-quatre-vingt-huit", "trente-trois-mille-quatre-cent-quatre-vingt-neuf", "trente-trois-mille-quatre-cent-quatre-vingt-dix", "trente-trois-mille-quatre-cent-quatre-vingt-onze", "trente-trois-mille-quatre-cent-quatre-vingt-douze", "trente-trois-mille-quatre-cent-quatre-vingt-treize", "trente-trois-mille-quatre-cent-quatre-vingt-quatorze", "trente-trois-mille-quatre-cent-quatre-vingt-quinze", "trente-trois-mille-quatre-cent-quatre-vingt-seize", "trente-trois-mille-quatre-cent-quatre-vingt-dix-sept", "trente-trois-mille-quatre-cent-quatre-vingt-dix-huit", "trente-trois-mille-quatre-cent-quatre-vingt-dix-neuf"};

    for (int i = 0; i < 100; i++) {
        s = s_l[i];

        int* result = eval_number(s, (int)strlen(s));

        if (result[0] == 1) {
            printf("%d\n", result[1]);
        } else {
            printf("\"%s\" is not a valid number\n", s);
            break;
        }
        free(result);
    }
    return 0;
}
