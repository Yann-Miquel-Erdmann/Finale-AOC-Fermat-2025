#include "../../structures/val.h"
#include "../expressions.h"
#include "../../timeout.h"

void get_input(val_t* dest){
    pause_timeout();
    char* chaine = malloc(2 * sizeof(char));
    int len = 2;
    int index = 0;
    char c;
    scanf("%c", &c);
    while (c != '\n'){
        chaine[index] = c;
        index++;
        if (index+1 == len){
            len *= 2;
            chaine = realloc(chaine, len);
        }
        scanf("%c", &c);
    }
    chaine[index] = '\0';
    set_char(dest, new_chaine_t(chaine));
    free(chaine);
    unpause_timeout();
}
