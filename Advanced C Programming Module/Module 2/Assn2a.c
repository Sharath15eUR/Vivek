#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

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
    int N = *(int*)arg;
    int count = 0;
    int num = 2;
    int sum = 0;
    
    while (count < N) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }
    
    printf("Thread A: Sum of first %d primes is %d\n", N, sum);
    pthread_exit(NULL);
}

void* thread_b_func(void* arg) {
    time_t start_time = time(NULL);
    
    while (time(NULL) - start_time < 100) {
        printf("Thread 1 running (Every 2 Seconds) \n");
        sleep(2);
    }
    
    pthread_exit(NULL);
}

void* thread_c_func(void* arg) {
    time_t start_time = time(NULL);
    
    while (time(NULL) - start_time < 100) {
        printf("Thread 2 running (Every 3 seconds) \n");
        sleep(3);
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_a, thread_b, thread_c;
    int N;
    
    printf("Enter the value of N: ");
    scanf("%d", &N);
    

    pthread_create(&thread_a, NULL, thread_a_func, &N);
    pthread_create(&thread_b, NULL, thread_b_func, NULL);
    pthread_create(&thread_c, NULL, thread_c_func, NULL);
    

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);
    
    printf("All threads have completed execution.\n");
    return 0;
}
