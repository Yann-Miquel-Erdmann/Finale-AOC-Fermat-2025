#ifndef safe_alloc_h
#define safe_alloc_h

#include <stdio.h>
#include "custom_error.h"
#include <stdlib.h>

// malloc a new pointer of size size if ptr is NULL
// else reallocs ptr with a new size of size
__attribute__((malloc)) void* _Nonnull safe_alloc(void* _Nullable ptr, size_t size) __result_use_check __alloc_size(2);

#endif
