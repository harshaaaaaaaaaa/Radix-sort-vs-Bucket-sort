#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMax(int *array, int n) {
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

void swap(int *array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void insertionSort(int *array, int n) {
    for (int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void radixSort(int *array, int n) {
    int max = getMax(array, n);
    int buckets[10];
    for (int i = 0; i < 10; i++) {
        buckets[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int digit = array[i] % 10;
        buckets[digit]++;
    }
    for (int i = 0; i < 10; i++) {
        if (buckets[i] > 0) {
            insertionSort(array + i, buckets[i]);
        }
    }
    int index = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < buckets[i]; j++) {
            array[index++] = array[i + j];
        }
    }
}

void bucketSort(int *array, int n, int numBuckets) {
    int buckets[numBuckets];
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int bucketIndex = (array[i] * numBuckets) / n;
        buckets[bucketIndex]++;
    }
    for (int i = 0; i < numBuckets; i++) {
        if (buckets[i] > 0) {
            insertionSort(array + i, buckets[i]);
        }
    }
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 0; j < buckets[i]; j++) {
            array[index++] = array[i + j];
        }
    }
}

void compareRadixAndBucketSort(int *array, int n, int numBuckets) {
    clock_t radixStartTime = clock();
    radixSort(array, n);
    clock_t radixEndTime = clock();
    float radixSortTime = (float)(radixEndTime - radixStartTime) / CLOCKS_PER_SEC;
    clock_t bucketStartTime = clock();
    bucketSort(array, n, numBuckets);
    clock_t bucketEndTime = clock();
    float bucketSortTime = (float)(bucketEndTime - bucketStartTime) / CLOCKS_PER_SEC;
    printf("Radix Sort time: %f seconds\n", radixSortTime);
    printf("Bucket Sort time: %f seconds\n", bucketSortTime);
}

int main() {
    int n = 1000000;
    int *array = (int *)malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 1000000;
    }
    compareRadixAndBucketSort(array, n, 10);
    free(array);
    return 0;
}