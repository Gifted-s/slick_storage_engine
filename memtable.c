#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/rbtree.h>
#include <stdio.h>
#include "includes/memtable.h"
#include "includes/memtable_rbt.h"

struct MemTable *MemTable_new()
{
    struct MemTable *memtable = malloc(sizeof(struct MemTable));
    memtable->size = 0;
    memtable->record = NULL;
    return memtable;
}
// Major interfaces
struct RBTNode *MemTable_get(const struct MemTable *memtable, char *key, size_t key_len)
{
    return getKey(memtable->record, key, key_len);
}

void MemTable_set(struct MemTable *memtable, char *key, size_t key_len, int64_t value_loc)
{
    insert(&(memtable->record), key, key_len, value_loc);
    memtable->size++;
}

void MemTable_delete(struct MemTable *memtable, char *key, size_t key_len)
{
    insert(&(memtable->record), key, key_len, TUMBSTONE);
    memtable->size++;
    return;
}

struct RBTNode *MemTable_to_list(struct MemTable *memtable)
{
    if (memtable->size == 0)
    {
        return NULL;
    }
    else
    {
        return get_nodes_sorted(memtable->record, memtable->size);
    }
}

void MemTable_free(struct MemTable *memtable)
{   
    free_tree(memtable->record);
    free(memtable);
}




// int main()
// {
//     struct MemTable *m = MemTable_new();
//     char *key1 = "iim";
//     char *value1 = "{}";
//     char *key2 = "cat";
//     char *value2 = "Key Lime Pie";
//     char *key3 = "dog";
//     char *value3 = "Key Lime Pie";
//     char *key4 = "aom";
//     char *value4 = "Key Lime Pie";
//     char *key5 = "jim";
//     char *value5 = "Key Lime Pie";
//     char *key6 = "gim";
//     char *value6 = "Key Lime Pie";
//     long long value1_offset = 0;
//     MemTable_set(m, key1, strlen(key1) + 1, 38);
//     MemTable_set(m, key2, strlen(key2) + 1, 57);
//     MemTable_set(m, key3, strlen(key3) + 1, 39);
//     MemTable_set(m, key4, strlen(key4) + 1, 20);
//     MemTable_set(m, key5, strlen(key5) + 1, 56);
//     MemTable_set(m, key6, strlen(key6) + 1, 56);
//     // struct RBTNode *record = malloc(sizeof(struct RBTNode));
//     // MemTable_delete(m,key2, strlen(key1));
//     // record = MemTable_get(m, key2, strlen(key2));
//     printf("============================ DATABASE TEST ================================== \n");
//     // printf("Key: %s, Value: %lld \n", record->key, record->value_loc);
//      struct RBTNode* nodes_arr = (struct RBTNode *)malloc(sizeof(struct RBTNode) *  m->size);
//      nodes_arr = MemTable_to_list(m);
//     printf("SIZE %zu", m->size);
//     for (int i = 0; i < m->size; ++i)
//     {
//         printf("Key: %s Value_Offset: %llu \n", nodes_arr[i].key, nodes_arr[i].value_loc);
//     }
//     /* code */
//     printf("============================== PROGRAM END ================================= \n");
//     return 0;
// }
