#include <libc.h>
#include "../include/minishell.h"

typedef struct node {
    void *ptr;
    struct node *next;
} t_node;

typedef struct mem {
    t_node *head;
    t_node *tail;
} t_memory_list;

t_memory_list memory_list;

void init_memory_list(void) {
    memory_list.head = NULL;
    memory_list.tail = NULL;
}

void add_memory(void *ptr) {
    t_node *new_node;

    new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node) {
        ft_printf(2, "Failed to allocate memory for list node\n");
        exit(EXIT_FAILURE);
    }
    new_node->ptr = ptr;
    new_node->next = NULL;
    if (memory_list.tail)
        memory_list.tail->next = new_node;
    else
        memory_list.head = new_node;
    memory_list.tail = new_node;
}

void *gc_malloc(size_t size) {
    void *ptr;

    ptr = malloc(size);
    if (!ptr) {
        ft_printf(2, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    add_memory(ptr);
    return (ptr);
}

void gc_free_all(void) {
    t_node *current;
    t_node *next;

    if (!memory_list.head)
        return;
    current = memory_list.head;
    while (current) {
        next = current->next;
        if (current->ptr)
            free(current->ptr);
        free(current);
        current = next;
    }
    memory_list.head = NULL;
    memory_list.tail = NULL;
}
