#include "../src/parser.h"
#include "../src/phrase.h"
#include "../src/val.h"
#include "assert.h"
#include "stdio.h"

void test_parse() {
    FILE* f = fopen("testing/test.FC", "r");
    assert(f != NULL);

    phrase_t* p = parse_file(f);
    printPhrase(p);
    free_phrase(p);
    fclose(f);
}

void test_val() {
    val_t* v1 = new_val();
    val_t* v2 = new_val();
    val_t* v3 = new_val();
    set_int(v1, 45);
    set_float(v2, 50.320);
    set_bool(v3, true);

    printf("%d\n", get_int(v1));
    printf("%f\n", get_float(v2));
    printf("%d\n", get_bool(v3));

    set_int(v3, 450207);
    printf("%d\n", get_int(v3));

    set_bool(v3, false);
    printf("%d\n", get_bool(v3));

    free_val(v1);
    free_val(v2);
    free_val(v3);
}

int main(int argc, char const* argv[]) {
    test_val();
    return 0;
}
