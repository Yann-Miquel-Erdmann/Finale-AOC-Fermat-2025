#ifndef PARSER_H
#define PARSER_H

#include "stdio.h"
#include "phrase.h"
// crée et renvoie l'AST à partir d'un fichier f  
phrase_t* parse_file(FILE* f);

#endif