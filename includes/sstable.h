
#ifndef WISCKEY_SSTABLE_H
#define WISCKEY_SSTABLE_H


#include <stdlib.h>
#include <stdio.h>

#include "memtable.h"


#define SSTABLE_MIN_SIZE 1024
#define SSTABLE_KEY_NOT_FOUND (-2)

struct SSTableRecord {
    char *key;
    size_t key_len;
    int64_t value_loc;
};



struct SSTable {
    char *path;
    unsigned long timestamp;
    unsigned long level;
    FILE *file;
    uint64_t *records;
    size_t capacity;
    size_t size;

    char *low_key;
    size_t low_key_len;
    char *high_key;
    size_t high_key_len;
};


unsigned long SSTable_parse_timestamp(char *filename);


unsigned long SSTable_parse_level(char *filename);

struct SSTable *SSTable_new(char *path);

struct SSTable *SSTable_new_from_memtable(char *path, struct MemTable *memtable);

int64_t SSTable_get_value_loc(struct SSTable *table, char *key, size_t key_len);

int SSTable_in_key_range(struct SSTable *table, char *key, size_t key_len);

void SSTable_free(struct SSTable *table);

#endif