// #include "stdio.h"
// int main(int argc, char const *argv[]) {
//     float a = 45.02367;

//     printf("%d", *((int *)&a));

//     return 0;
// }


#include "stdio.h"
#include "../src/parser.h"
#include "../src/phrase.h"
#include "assert.h"
int main(int argc, char const *argv[])
{
    FILE* f = fopen("testing/test.FC", "r");
    assert(f!=NULL);

    phrase_t* p = parse_file(f);
    printPhrase(p);

    return 0;
}
