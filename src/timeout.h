#ifndef timeout_h
#define timeout_h

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "custom_error.h"

void setTimeout(int timeout);
void pause_timeout(void);
void unpause_timeout(void);

#endif
