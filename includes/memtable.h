#ifndef WISCKEY_MEMTABLE_H
#define WISCKEY_MEMTABLE_H

#include <stdlib.h>
#include <stdint.h>
#include "./memtable_rbt.h"

#define MEMTABLE_SIZE 1024
#define TUMBSTONE -1
struct MemTable
{
    struct RBTNode *record;
    size_t size;
};

struct MemTable *MemTable_new();

struct RBTNode *MemTable_get(const struct MemTable *memtable, char *key, size_t key_len);

struct RBTNode* MemTable_to_list(struct MemTable *memtable);

void MemTable_set(struct MemTable *memtable, char *key, size_t key_len, int64_t value_loc);

void MemTable_delete(struct MemTable *memtable, char *key, size_t key_len);

void MemTable_free(struct MemTable *memtable);

void free_tree(struct RBTNode *root);
#endif