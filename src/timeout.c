#include "timeout.h"
#include <stdatomic.h>
#include <unistd.h>
#include "safe_alloc.h"

atomic_bool timeout_stopped = false;

typedef struct timeout {
    int value;
} timeout_t;


void* thread_timeout(void* arg){
    int max_time = ((timeout_t*)arg)->value;
    int time_used = 0;
    while (time_used < max_time){
        if (!timeout_stopped){
            time_used += 10;
        }
        usleep(10000);
    }
    custom_error("Timeout atteint, boucle infinie / récursion infinie?", NULL, NULL);
}

void pause_timeout(void){
    timeout_stopped = true;
}

void unpause_timeout(void){
    timeout_stopped = false;
}

// timeout in miliseconds
void setTimeout(int time){
    pthread_t thread;
    timeout_t* t = safe_alloc(NULL, sizeof(timeout_t));
    t->value = time;
    pthread_create(&thread, NULL, thread_timeout, t);
}
