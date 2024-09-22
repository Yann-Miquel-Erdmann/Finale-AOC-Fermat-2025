#include "../../structures/val.h"
#include "../expressions.h"
#include "../../timeout.h"
#include "../../safe_alloc.h"

void get_input(val_t* dest){
    pause_timeout();
    char* chaine = safe_alloc(NULL, 2 * sizeof(char));
    int len = 2;
    int index = 0;
    char c;
    scanf("%c", &c);
    while (c != '\n'){
        chaine[index] = c;
        index++;
        if (index+1 == len){
            len *= 2;
            chaine = safe_alloc(chaine, len);
        }
        scanf("%c", &c);
    }
    chaine[index] = '\0';
    val_t* val = new_chaine_val_t(chaine);
    copy_val(dest, val, true, true);
    free(chaine);
    free_val_t(val, true, true);
    unpause_timeout();
}
