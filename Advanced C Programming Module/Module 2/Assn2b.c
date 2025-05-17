#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <windows.h>
#include <signal.h>
#include <time.h>

volatile sig_atomic_t keep_running = 1;

void handle_sigint(int sig) {
    printf("\nReceived SIGINT (Ctrl+C). Finishing current work...\n");
    keep_running = 0;
}

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    int i;
    for (i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return false;
    }
    return true;
}

void* thread_a_func(void* arg) {
    clock_t start = clock();

    int N = *(int*)arg;
    int count = 0, num = 2, sum = 0;

    while (count < N && keep_running) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Thread A: Sum of first %d primes is %d (Time taken: %.2f seconds)\n", N, sum, time_taken);
    pthread_exit(NULL);
}

void* thread_b_func(void* arg) {
    time_t start_time = time(NULL);
    int iteration = 0;

    while (time(NULL) - start_time < 100 && keep_running) {
        iteration++;
        printf("Thread B: Running (Iteration %d)\n", iteration);
        Sleep(2000); // 2 seconds
    }

    printf("Thread B: Completed\n");
    pthread_exit(NULL);
}

void* thread_c_func(void* arg) {
    time_t start_time = time(NULL);
    int iteration = 0;

    while (time(NULL) - start_time < 100 && keep_running) {
        iteration++;
        printf("Thread C: Running (Iteration %d)\n", iteration);
        Sleep(3000); // 3 seconds
    }

    printf("Thread C: Completed\n");
    pthread_exit(NULL);
}

int main() {
    signal(SIGINT, handle_sigint);

    pthread_t thread_a, thread_b, thread_c;
    int N;

    printf("Enter the value of N: ");
    scanf("%d", &N);

    printf("Main thread started at %ld\n", time(NULL));

    pthread_create(&thread_a, NULL, thread_a_func, &N);
    pthread_create(&thread_b, NULL, thread_b_func, NULL);
    pthread_create(&thread_c, NULL, thread_c_func, NULL);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);

    printf("All threads completed at %ld\n", time(NULL));
    return 0;
}

