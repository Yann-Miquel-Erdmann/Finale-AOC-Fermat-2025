#include "custom_error.h"

#include <stdio.h>

void custom_error(char* err_message) {
    fprintf(stderr, "Une erreur est survenue avec le message suivant:\n%s\n", err_message);
    exit(1);
}