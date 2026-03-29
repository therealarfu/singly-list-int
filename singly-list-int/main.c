#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "intlist.h"

// Funções auxiliares
int square(int x)
{
    return x * x;
}

bool is_even(int x)
{
    return x % 2 == 0;
}

int sum(int acc, int x)
{
    return acc + x;
}

void print_number(int x)
{
    printf("%d ", x);
}

int main()
{
    int arr[] = {5, 2, 8, 3, 10, 7, 2, 6};

    // Create list from array
    node *list = array_to_list(arr, 8);

    printf("Original list: ");
    list_for_each(list, print_number);
    printf("\n");

    // Sort list
    list_sort(&list);
    printf("Ordenada: ");
    list_for_each(list, print_number);
    printf("\n");

    // Map (squared)
    node *squared = list_map(list, square);
    printf("Squared: ");
    list_for_each(squared, print_number);
    printf("\n");

    // Filter (even numbers)
    node *evens = list_filter(list, is_even);
    printf("Even numbers: ");
    list_for_each(evens, print_number);
    printf("\n");

    // Reduce (sum)
    int total = list_reduce(list, sum, 0);
    printf("Sum total: %d\n", total);

    // Estatísticas
    int min, max;
    list_min(list, &min);
    list_max(list, &max);
    printf("Min: %d | Max: %d\n", min, max);
    printf("Average: %.2f\n", list_average(list));

    // Join (string)
    char *joined = list_join(list, " -> ");
    printf("Join: %s\n", joined);

    // Search for a number
    size_t index;
    if (list_index_of(7, list, &index))
    {
        printf("Number 7 found at index %zu\n", index);
    }

    // Swap
    list_swap(0, 3, &list);
    printf("After swap(0,3): ");
    list_for_each(list, print_number);
    printf("\n");

    // Reverse
    list_reverse(&list);
    printf("Reverse: ");
    list_for_each(list, print_number);
    printf("\n");

    // Unload lists and free memory
    free(joined);
    unload_list(list);
    unload_list(squared);
    unload_list(evens);

    return 0;
}