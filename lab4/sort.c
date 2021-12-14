#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void combSort(int* a, int n) {
    int gap = n;
    int swapped = 1;

    while (gap != 1 || swapped) {
        gap *= 10 / 13;
        if (gap < 1) {
            gap = 1;
        }
        swapped = 0;
        for (int i = 0; i < n - gap; i++) {
            if (a[i] > a[i + gap]) {
                swap(&a[i], &a[i + gap]);
                swapped = 1;
            }
        }
    }

}

void insertion_sort(int* mass, int n) {
    int newElement, location;

    for (int i = 1; i < n; i++)
    {
        newElement = mass[i];
        location = i - 1;
        while (location >= 0 && mass[location] > newElement)
        {
            mass[location + 1] = mass[location];
            location = location - 1;
        } 
        mass[location + 1] = newElement;
    }
}

void double_selection_sort(int* mas, int n) {
    int max, min, max_index, min_index, i, j, k;

    k = n - 1;
    for (i = 0; i <= k; i++)
    {
        max = min = mas[i];
        max_index = min_index = i;
        for (j = i + 1; j <= k; j++)
        {
            if (mas[j] > max)
            {
                max = mas[j];
                max_index = j;
            }
            if (mas[j] < min)
            {
                min = mas[j];
                min_index = j;
            }
        }
        if (max_index == i && min_index != k) 
        {
            swap(&mas[k], &mas[max_index]);
            swap(&mas[i], &mas[min_index]);
        }
        if (min_index == k && max_index != i)
        {
            swap(&mas[i], &mas[min_index]);
            swap(&mas[k], &mas[max_index]);
        }
        if (min_index == k && max_index == i)
            swap(&mas[k], &mas[i]);
        if (min_index != k && max_index != i)
        { 
            swap(&mas[k], &mas[max_index]);
            swap(&mas[i], &mas[min_index]);
        }
        k--; 
    }
}

void print_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}
