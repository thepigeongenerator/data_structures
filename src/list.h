#pragma once
#include <stdlib.h>

typedef struct {
    size_t cap;   // contains the capacity of the list
    size_t count; // contains the amount of elements within the list
} ListInfo;

// resizes a generic list
void list_resize(void** data, ListInfo* info, const size_t new_cap, const size_t elmt_size) {
    info->cap = new_cap;

    // just allocate an array if it hasn't been allocated yet
    if (*data == NULL) {
        *data = malloc(new_cap * elmt_size);
        return;
    }

    // reallocate the array with a new size
    *data = realloc(*data, new_cap * elmt_size);
}

// inserts all the code for a list of a specific type
#define DEFINE_LIST(_type)                                                                    \
    typedef struct {                                                                          \
        _type* data;                                                                          \
        ListInfo info;                                                                        \
    } _type##_list;                                                                           \
                                                                                              \
    /* initializes a _list list with a set capacity, use {0} for a capacity of 0 */           \
    _type##_list _type##_list_init(const size_t cap) {                                        \
        return (_type##_list){(_type*)malloc(cap * sizeof(_type))};                           \
    }                                                                                         \
                                                                                              \
    /* adds an item to the _type list, doubles the capacity if it is full */                  \
    void _type##_list_add(_type##_list* list, _type val) {                                    \
        if (list->data == NULL)                                                               \
            list_resize((void**)&list->data, &list->info, 1, sizeof(_type));                  \
        else if (list->info.cap == list->info.count)                                          \
            list_resize((void**)&list->data, &list->info, list->info.cap * 2, sizeof(_type)); \
                                                                                              \
        list->data[list->info.count] = val;                                                   \
        list->info.count++;                                                                   \
    }                                                                                         \
                                                                                              \
    /* removes an item from the list at a specific index */                                   \
    void _type##_list_remove(_type##_list* list, const size_t index) {                        \
        list->info.count--;                                                                   \
        for (size_t i = index; i < list->info.count; i++) {                                   \
            list->data[i] = list->data[i + 1];                                                \
        }                                                                                     \
    }
