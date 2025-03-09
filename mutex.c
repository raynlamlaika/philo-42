#include "philo.h"

void *print_message(void *arg) {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    printf("Main thread finished.\n");
    pthread_create(&thread, NULL, print_message, NULL);
    pthread_join(thread, NULL);  // Wait for the thread to finish
    return 0;
}
