#include "../../safe_alloc.h"
#include "../../structures/val.h"
#include "../../timeout.h"
#include "../expressions.h"

void get_input(val_t* dest) {
    pause_timeout();
    char* chaine = safe_alloc(NULL, 2 * sizeof(char));
    int len = 2;
    int index = 0;
    char c;
    scanf("%c", &c);
    while (c != '\n') {
        chaine[index] = c;
        index++;
        if (index + 1 == len) {
            len *= 2;
            chaine = safe_alloc(chaine, len);
        }
        scanf("%c", &c);
    }
    chaine[index] = '\0';

    chaine_t* ch = new_chaine_t(chaine);
    set_char(dest, ch);
    free(chaine);
    // copy_val(dest, val, true, true);
    // free(chaine);
    // free_val_t(val, true, true);
    unpause_timeout();
}
