#include "hash_table.h"

void* search_linked_list(struct hash_table_item* head, uint64_t key)
{
    do
    {
        if (head->key == key)
            return head->value;
    } while ((head = head->next));

    return NULL;
}

uint64_t hash_string_djb2(char* str)
{
    uint64_t hash = 0x1337133713371337;
    char c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

struct hash_table_item* create_hash_table_item(uint64_t key, void* value)
{
    struct hash_table_item* item = malloc(sizeof(*item));

    item->key = key;
    item->value = value;
    item->next = NULL;

    return item;
}

void free_hash_table_item(struct hash_table_item* item)
{
    free(item);
}

struct hash_table* create_hash_table(size_t size)
{
    struct hash_table* table = malloc(sizeof(*table));

    table->size = size;

    table->items = calloc(table->size, sizeof(*table->items));

    return table;
}

void free_hash_table(struct hash_table* table)
{
    struct hash_table_item* item = NULL;
    struct hash_table_item* popped = NULL;

    for (int i = 0; i < table->size; i++)
    {
        item = table->items[i];
        if (item != NULL)
        {
            /*
                Free every item in the chain

                TODO: maybe popping every value from the end isn't
                good for performance, maybe we free from the head?
            */
            do
            {
                popped = (struct hash_table_item*)pop_linked_list((struct Node*)item);

                if (popped == item)
                {
                    free_hash_table_item(item);
                    table->items[i] = NULL;
                    break;
                }

                free_hash_table_item(popped);
            } while (popped != NULL);
        }
    }

    print_hash_table(table);

    free(table);
}

void hash_table_insert(struct hash_table* table, struct hash_table_item* item)
{
    struct hash_table_item* indexed_item = NULL;

    /*
        Get hash table index
    */
    uint64_t index = item->key % table->size;

    indexed_item = table->items[index];

    if (indexed_item == NULL)
    {
        /*
            Insert item into hash index
        */
        table->items[index] = item;
    }
    else
    {
        /*
            Hash collision, prepend new item to the
            head of the chain.
            TODO: Find a way to modify existing entries without
            costing insert time complexity to become O(n)
        */
        table->items[index] = (struct hash_table_item*)prepend_linked_list(
            (struct Node*)indexed_item,
            (struct Node*)item);
    }
}

void* hash_table_search(struct hash_table* table, uint64_t key)
{
    /*
        Get hash table index
    */
    uint64_t index = key % table->size;

    if (table->items[index] == NULL)
        return NULL;

    /*
        If the key at the index is different from search key,
        we have to walk the chain to find the value. We do this
        anyways as there is no need to branch here.
    */
    return search_linked_list(table->items[index], key);
}

void print_hash_table(struct hash_table* table)
{
    struct hash_table_item* item = NULL;

    /*
        Print every valid item index.
    */
    for (int i = 0; i < table->size; i++)
    {
        item = table->items[i];

        if (item)
        {
            /*
                Walk item chain to print all items
            */
            do
            {
                printf("%d:\taddr:%p\tnext:%p\n", i, item->value, item->next);
            } while ((item = item->next));
        }
    }
}