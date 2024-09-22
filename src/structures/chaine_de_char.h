#ifndef CHAINE_DE_CHAR_H
#define CHAINE_DE_CHAR_H

struct val;

typedef struct chaine {
    char* chars;
    int chars_len;
    int chars_size;
} chaine_t;

void free_chaine_t(chaine_t* c);
chaine_t* new_chaine_t(char* c);
struct val * new_chaine_val_t(char* c);
chaine_t* copy_chaine(chaine_t* src);

void ajouter_char(chaine_t* c, char e);
void concat_chaines(chaine_t* c1, chaine_t* c2);

#endif
