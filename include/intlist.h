#ifndef INTLIST_H
#define INTLIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

// Prototypes
void unload_list(node *list);
node *array_to_list(int *number, size_t len);
bool list_index_of(int number, node *list, size_t *out);
bool list_at(size_t index, node *list, int *out);
bool list_min(node *list, int *out);
bool list_max(node *list, int *out);
double list_average(node *list);
size_t list_count(int number, node *list);
void list_reverse(node **list);
node *list_map(node *list, int (*func)(int number));
node *list_concat(node *lists[], size_t listqnt);
bool list_swap(size_t index1, size_t index2, node **list);
bool list_find(node *list, bool (*func)(int number), int *out);
node *list_filter(node *list, bool (*func)(int number));
int list_reduce(node *list, int (*func)(int acc, int number), int initial);
void list_sort(node **list);
void list_for_each(node *list, void (*func)(int number));
char *list_join(node *list, const char *separator);
bool list_prepend(int number, node **list);
bool list_append(int number, node **list);
size_t list_length(node *list);
bool list_insert(int number, size_t index, node **list);
bool list_shift(node **list);
bool list_pop(node **list);
bool list_remove_at(size_t index, node **list);

#endif