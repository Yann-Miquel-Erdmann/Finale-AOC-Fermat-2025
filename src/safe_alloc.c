#include "safe_alloc.h"

void* safe_alloc(void* ptr, size_t size){
    if (ptr == NULL){
        ptr = malloc(size);
    }else{
        ptr = realloc(ptr, size);
    }
    if (ptr == NULL){
        custom_error("Plus d'espace mémoire disponible", NULL, NULL);
    }
    return ptr;
}
