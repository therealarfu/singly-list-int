#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intlist.h"

// Frees every node in a list, one by one.
void unload_list(node *list)
{
    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

// Loops through every node in a list
// Running a function(func) everytime it passes through one node.
void list_for_each(node *list, void (*func)(int number))
{
    while (list != NULL)
    {
        func(list->number);
        list = list->next;
    }
}

// Loops through every node in a list
// Returns an accumulated value based on a function(func) everytime it passes through one node.
// If list is NULL, it returns initial
int list_reduce(node *list, int (*func)(int acc, int number), int initial)
{
    int a = initial;
    while (list != NULL)
    {
        a = func(a, list->number);
        list = list->next;
    }
    return a;
}

// Order a linked list with an insertion sort algorithmn
// If list is NULL or has only one element, it does not change the list.
void list_sort(node **list)
{
    node *sorted = NULL;
    node *current = *list;
    if (list == NULL || *list == NULL || current->next == NULL)
    {
        return;
    }

    while (current != NULL)
    {
        node *next = current->next;

        if (sorted == NULL || current->number < sorted->number)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            node *temp = sorted;
            while (temp->next != NULL && temp->next->number < current->number)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *list = sorted;
}

// Loops through a list to create a string buffer
// Converts all items in a list to the string buffer
// All items are separated by a given separator
// Returns the converted string
// <User must free the string -> free(string)>
char *list_join(node *list, const char *separator)
{
    node *ptr = list;
    size_t str_len = 0;
    size_t list_len = 0;

    while (list != NULL)
    {
        str_len += snprintf(NULL, 0, "%d", list->number);
        list_len++;
        list = list->next;
    }

    if (list_len == 0)
    {
        return NULL;
    }

    size_t len_separator = strlen(separator);
    str_len += len_separator * (list_len - 1);

    char *buffer = malloc(str_len + 1);
    if (buffer == NULL)
    {
        return NULL;
    }

    size_t i = 0;
    while (ptr != NULL)
    {
        i += snprintf(&buffer[i], str_len - i + 1, "%d", ptr->number);
        ptr = ptr->next;
        if (ptr != NULL)
        {
            i += snprintf(&buffer[i], str_len - i + 1, "%s", separator);
        }
    }

    buffer[str_len] = '\0';
    return buffer;
}

// Searches through one function from left to right
// If the value satisfy the function, stores the value in *out and returns true
// If it doesn't satisfy or invalid arguments, returns false
bool list_find(node *list, bool (*func)(int number), int *out)
{
    if (out == NULL)
    {
        return false;
    }
    while (list != NULL)
    {
        if (func(list->number))
        {
            *out = list->number;
            return true;
        }
        list = list->next;
    }
    return false;
}

// Searches the list by loop
// Returns a new list with the elements that satisfy the condition in the function(func)
// If no elements satisfy the condition, it returns NULL
// Needs to be unloaded with unload_list() to free the memory allocated for the list
node *list_filter(node *list, bool (*func)(int number))
{
    if (list == NULL)
    {
        return NULL;
    }

    node *result = NULL;
    node *tail = NULL;

    while (list != NULL)
    {
        while (list != NULL && !func(list->number))
        {
            list = list->next;
        }

        if (list == NULL)
        {
            break;
        }

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload_list(result);
            return NULL;
        }
        n->number = list->number;
        n->next = NULL;

        if (result == NULL)
        {
            result = n;
            tail = n;
        }
        else
        {
            tail->next = n;
            tail = n;
        }
        list = list->next;
    }
    return result;
}

// Swap two values by two indexes
bool list_swap(size_t index1, size_t index2, node **list)
{
    if (list == NULL || *list == NULL)
    {
        return false;
    }

    size_t start;
    size_t end;

    if (index1 < index2)
    {
        start = index1;
        end = index2;
    }
    else if (index1 > index2)
    {
        start = index2;
        end = index1;
    }
    else
    {
        return true;
    }

    size_t i = 0;
    node *ptr = *list;
    node *node1 = NULL;
    node *node2 = NULL;

    while (ptr != NULL)
    {
        if (i == start)
        {
            node1 = ptr;
        }
        else if (i == end)
        {
            node2 = ptr;
            break;
        }
        ptr = ptr->next;
        i++;
    }

    if (node1 == NULL || node2 == NULL)
    {
        return false;
    }

    int temp = node1->number;
    node1->number = node2->number;
    node2->number = temp;

    return true;
}

// Join every list in the lists array into a unique list
// Returns the joined list
// Needs to be unloaded with unload_list() to free the memory allocated for the list
node *list_concat(node *lists[], size_t listqnt)
{
    node *result = NULL;
    node *tail = NULL;

    for (size_t i = 0; i < listqnt; i++)
    {
        node *temp = lists[i];
        if (temp == NULL)
        {
            continue;
        }
        while (temp != NULL)
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                unload_list(result);
                return NULL;
            }
            n->number = temp->number;
            n->next = NULL;
            if (result == NULL)
            {
                result = n;
                tail = n;
            }
            else
            {
                tail->next = n;
                tail = n;
            }
            temp = temp->next;
        }
    }
    return result;
}

// Converts an array of integers into a singly linked list of integers
// Returns the linked list
// Needs to be unloaded with unload_list() to free the memory allocated for the list
node *array_to_list(int *number, size_t len)
{
    node *start = NULL;
    node *tail = NULL;
    for (size_t i = 0; i < len; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload_list(start);
            return NULL;
        }

        n->number = number[i];
        n->next = NULL;
        if (i == 0)
        {
            start = n;
            tail = n;
        }
        else if (i > 0)
        {
            tail->next = n;
            tail = n;
        }
    }
    return start;
}

// Searches the list by loop
// Replaces each element with the returning value of the function(func)
// Returns mapped list
// Needs to be unloaded with unload_list() to free the memory allocated for the list
node *list_map(node *list, int (*func)(int number))
{
    if (list == NULL)
    {
        return NULL;
    }

    node *result = NULL;
    node *tail = NULL;
    while (list != NULL)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload_list(result);
            return NULL;
        }
        n->number = func(list->number);
        n->next = NULL;

        if (result == NULL)
        {
            result = n;
            tail = n;
        }
        else
        {
            tail->next = n;
            tail = n;
        }
        list = list->next;
    }
    return result;
}

// Reverses a list like [1,2,3] -> [3,2,1]
void list_reverse(node **list)
{
    if (list == NULL || *list == NULL || (*list)->next == NULL)
    {
        return;
    }

    node *prev = *list;
    node *current = prev->next;
    prev->next = NULL;
    node *next = current->next;
    current->next = prev;

    while (next != NULL)
    {
        prev = current;
        current = next;
        next = next->next;
        current->next = prev;
    }
    *list = current;
}

// Returns the arithmetic mean of all values in the list
// Sums all values in the list then divide by the number of values
// If division by zero, then it returns 0
double list_average(node *list)
{
    size_t n = 0;
    int s = 0;
    while (list != NULL)
    {
        s += list->number;
        n++;
        list = list->next;
    }

    if (n == 0)
    {
        return 0;
    }
    return s / (double) n;
}

// Returns how many times a given number has appeared in a list
// If it has never appeared then returns 0
size_t list_count(int number, node *list)
{
    size_t n = 0;
    while (list != NULL)
    {
        if (list->number == number)
        {
            n++;
        }
        list = list->next;
    }
    return n;
}

// Seachers for a value in the list
// If found, stores the first index of that value in *out and returns true
// If not found or invalid arguments, returns false
bool list_index_of(int number, node *list, size_t *out)
{
    if (out == NULL)
    {
        return false;
    }

    size_t n = 0;
    while (list != NULL)
    {
        if (number == list->number)
        {
            *out = n;
            return true;
        }
        n++;
        list = list->next;
    }
    return false;
}

// Searches if the index exists in the list
// If found, stores the value at the index in *out and returns true
// If not found or invalid arguments, returns false
bool list_at(size_t index, node *list, int *out)
{
    if (out == NULL)
    {
        return false;
    }

    size_t n = 0;
    while (list != NULL && n <= index)
    {
        if (n == index)
        {
            *out = list->number;
            return true;
        }
        n++;
        list = list->next;
    }
    return false;
}

// Adds one new item at the start of the list
bool list_prepend(int number, node **list)
{
    if (list == NULL)
    {
        return false;
    }
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return false;
    }
    n->number = number;
    n->next = *list;
    *list = n;
    return true;
}

// Adds one new item at the end of the list
bool list_append(int number, node **list)
{
    if (list == NULL)
    {
        return false;
    }
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return false;
    }

    n->number = number;
    n->next = NULL;
    if (*list == NULL)
    {
        *list = n;
        return true;
    }
    node *ptr = *list;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = n;
    return true;
}

// Returns how many elements has on the list
size_t list_length(node *list)
{
    node *ptr = list;
    size_t i = 0;
    while (ptr != NULL)
    {
        i = i + 1;
        ptr = ptr->next;
    }
    return i;
}

// Inserts a new item at any index that exists on the list length
bool list_insert(int number, size_t index, node **list)
{
    if (list == NULL)
    {
        return false;
    }

    size_t len = list_length(*list);
    if (index > len)
    {
        return false;
    }

    if (*list == NULL || index == 0)
    {
        return list_prepend(number, list);
    }
    else if (index == len)
    {
        return list_append(number, list);
    }
    else
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        n->number = number;

        node *prev = *list;
        node *after = *list;
        for (size_t i = 0; i < index - 1; i++)
        {
            prev = prev->next;
        }
        after = prev->next;
        prev->next = n;
        n->next = after;
    }
    return true;
}

// Removes the first element on the list
bool list_shift(node **list)
{
    if (list == NULL || *list == NULL)
    {
        return false;
    }
    else if ((*list)->next == NULL)
    {
        free(*list);
        *list = NULL;
        return true;
    }
    node *temp = *list;
    temp = temp->next;
    free(*list);
    *list = temp;
    return true;
}

// Removes the last/top element on the list
bool list_pop(node **list)
{
    if (list == NULL || *list == NULL)
    {
        return false;
    }
    else if ((*list)->next == NULL)
    {
        free(*list);
        *list = NULL;
        return true;
    }
    node *before = *list;
    while (before->next->next != NULL)
    {
        before = before->next;
    }
    free(before->next);
    before->next = NULL;
    return true;
}

// Removes any element at a given position, but only if that index exists on the list.
bool list_remove_at(size_t index, node **list)
{
    if (list == NULL)
    {
        return false;
    }

    size_t len = list_length(*list);
    if (*list == NULL || index >= len)
    {
        return false;
    }
    if (index == 0 || len == 1)
    {
        return list_shift(list);
    }
    else if (index == len - 1)
    {
        return list_pop(list);
    }
    else
    {
        node *before = *list;
        node *after = *list;
        for (size_t i = 0; i < index - 1; i++)
        {
            before = before->next;
        }
        after = before->next->next;
        free(before->next);
        before->next = after;
    }
    return true;
}

// Searches for the maximum value inside of the list
// If found, stores the value in *out and returns true
// If not found or invalid arguments, returns false
bool list_max(node *list, int *out)
{
    if (list == NULL || out == NULL)
    {
        return false;
    }
    int temp;
    temp = list->number;
    while (list->next != NULL)
    {
        list = list->next;
        if (temp < list->number)
        {
            temp = list->number;
        }
    }
    *out = temp;
    return true;
}

// Searches for the minimum value inside of the list
// If found, stores the value in *out and returns true
// If not found or invalid arguments, returns false
bool list_min(node *list, int *out)
{
    if (list == NULL || out == NULL)
    {
        return false;
    }
    int temp;
    temp = list->number;
    while (list->next != NULL)
    {
        list = list->next;
        if (temp > list->number)
        {
            temp = list->number;
        }
    }
    *out = temp;
    return true;
}
