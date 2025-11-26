#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

int arr[] = {5, 2, 9, 1, 6, 3, 8, 4, 7, 10};

typedef struct {
    int start_index;
    int end_index;
    long registration_id;
    int result;
} ThreadData;

void* find_min(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int min_val = INT_MAX;

    for (int i = data->start_index; i < data->end_index; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    data->result = min_val;
    printf("Thread %ld found Min = %d\n", data->registration_id, min_val);
    
    pthread_exit(NULL);
}

void* find_max(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int max_val = INT_MIN;

    for (int i = data->start_index; i < data->end_index; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    data->result = max_val;
    printf("Thread %ld found Max = %d\n", data->registration_id, max_val);
    
    pthread_exit(NULL);
}

int main() {
    long reg_no = 2023043;
    pthread_t threads[2];
    ThreadData args[2];

    printf("Registration Number: %ld\n\n", reg_no);

    // Thread 1 setup
    args[0].start_index = 0;
    args[0].end_index = 5;
    args[0].registration_id = reg_no;

    // Thread 2 setup
    args[1].start_index = 5;
    args[1].end_index = 10;
    args[1].registration_id = reg_no + 1;

    if (pthread_create(&threads[0], NULL, find_min, (void*)&args[0]) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }

    if (pthread_create(&threads[1], NULL, find_max, (void*)&args[1]) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Min = %d, Max = %d\n", args[0].result, args[1].result);

    return 0;
}
