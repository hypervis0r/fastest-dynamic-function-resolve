#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "linked_list.h"

struct hash_table_item
{
    struct hash_table_item* next;
    uint64_t key;
    void* value;
};

struct hash_table
{
    struct hash_table_item** items;
    size_t size;
};

void print_hash_table(struct hash_table* table);
void* search_linked_list(struct hash_table_item* head, uint64_t key);
uint64_t hash_string_djb2(char* str);
struct hash_table_item* create_hash_table_item(uint64_t key, void* value);
void free_hash_table_item(struct hash_table_item* item);
struct hash_table* create_hash_table(size_t size);
void free_hash_table(struct hash_table* table);
void hash_table_insert(struct hash_table* table, struct hash_table_item* item);
void* hash_table_search(struct hash_table* table, uint64_t key);