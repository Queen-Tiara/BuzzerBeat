#include <stdio.h>

#define NUM_OF_ELEMENTS 10

void printArray(int array[], int size);
int calculateSum(int array[], int size);
float calculateAverage(int array[], int size);
void reverseValues(int array[], int size);

int main() {
    int array[NUM_OF_ELEMENTS];

    printf("Enter %d integers: ", NUM_OF_ELEMENTS);
    for (int i = 0; i < NUM_OF_ELEMENTS; i++) {
        scanf("%d", &array[i]);
    }

    printf("The array contains: ");
    printArray(array, NUM_OF_ELEMENTS);

    int sum = calculateSum(array, NUM_OF_ELEMENTS);
    printf("The sum of the array elements is %d\n", sum);

    float average = calculateAverage(array, NUM_OF_ELEMENTS);
    printf("The average of the array elements is %.2f\n", average);

    printf("Reversing the values.\n");
    reverseValues(array, NUM_OF_ELEMENTS);

    printf("The array now contains: ");
    printArray(array, NUM_OF_ELEMENTS);

    return 0;
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int calculateSum(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

float calculateAverage(int array[], int size) {
    int sum = calculateSum(array, size);
    return (float)sum / size; 1 
}

void reverseValues(int array[], int size) {
    for (int i = 0; i < size; i++) {
        int reversed = 0;
        int temp = array[i];
        while (temp != 0) {
            int digit = temp % 10;
            reversed = reversed * 10 + digit;
            temp /= 10;
        }
        array[i] = reversed;
    }
}