/**
 * Mini Memcheck
 * CS 241 - Fall 2019
 */
#include "mini_memcheck.h"
#include <stdio.h>
#include <string.h>

void *mini_malloc(size_t request_size, const char *filename,
                  void *instruction) {

    void *block = malloc(sizeof(meta_data) + request_size);
    if (block == NULL) {
        return NULL;
    }
    meta_data *p = (meta_data *)block;
    p->request_size = request_size;
    p->filename = filename;
    p->instruction = instruction;
    if (head == NULL) {
        head = p;
        head->next = NULL;
    } else {
        p->next = head->next;
        head->next = p;
    }
    total_memory_requested += p->request_size;
    return (char *)block + sizeof(meta_data);
}

void *mini_calloc(size_t num_elements, size_t element_size,
                  const char *filename, void *instruction) {
    void *data = mini_malloc((num_elements * element_size), filename, instruction);
    if (data == NULL) {
        return NULL;
    }
    memset(data, 0x0, (num_elements * element_size));
    return data;
}

void *mini_realloc(void *payload, size_t request_size, const char *filename,
                   void *instruction) {
    void *block = realloc(payload, request_size);
    if (block == NULL) {
        return NULL;
    }
    meta_data *p = (meta_data *)block;
    p->request_size = request_size;
    p->filename = filename;
    p->instruction = instruction;

    meta_data *tmp = head;
    meta_data *prev = NULL;
    while (tmp != NULL) {
        if (tmp + 1 == payload) {
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        invalid_addresses++;
    } else {
        prev->next = block;
        total_memory_requested += (p->request_size - request_size);
    }
    return (char *)block + sizeof(meta_data);
}

void mini_free(void *payload) {
    free(payload);
    meta_data *tmp = head;
    meta_data *prev = NULL;
    while (tmp != NULL) {
        if (tmp + 1 == payload) {
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        if (payload != NULL) {
            invalid_addresses++;
        }
    } else {
        prev->next = tmp->next;
        total_memory_freed += tmp->request_size;
    }
}
