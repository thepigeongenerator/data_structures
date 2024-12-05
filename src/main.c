#include <stdio.h>

#include "list.h"

DEFINE_LIST(int)

int main(int argc, char** argv) {
    int_list list = {0};

    for (int i = 0; i < 100; i++)
        int_list_add(&list, i);

    for (int i = 0; i < list.info.count; i++)
        printf("%d, ", list.data[i]);
    printf("\ncount: %ld, cap: %ld", list.info.count, list.info.cap);

    free(list.data);
    return 0;
}
