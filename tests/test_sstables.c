/*
 * Copyright 2022 Adam Bishop Comer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../includes/sstable.h"

void TestSSTable_new_from_memtable()
{
    char *path = "./123456789-1.sstable";

    struct MemTable *m = MemTable_new();

    struct MultiType
    {
        char *key;
        size_t key_len;
        int64_t value_loc;
    };

#define SIZE 6

    struct MultiType array[SIZE];

    // Assign values to the elements of the array
    array[0].key = "adex";
    array[0].key_len = strlen("adex");
    array[0].value_loc = 15;

    array[1].key = "suku";
    array[1].key_len = strlen("suku");
    array[1].value_loc = 14;

    array[2].key = "bell";
    array[2].key_len = strlen("bell");
    array[2].value_loc = 17;

    array[5].key = "swah";
    array[5].key_len = strlen("swah");
    array[5].value_loc = 17;

    array[3].key = "zuks";
    array[3].key_len = strlen("zuks");
    array[3].value_loc = 43;

    array[4].key = "jenj";
    array[4].key_len = strlen("jenj");
    array[4].value_loc = 43;

    struct RBTNode *root = NULL;
    for (int i = 0; i < SIZE; i++)
    {
        MemTable_set(m, array[i].key, array[i].key_len, array[i].value_loc);
    }

    struct SSTable *table = SSTable_new_from_memtable(path, m);
    struct RBTNode *nodes_arr = (struct RBTNode *)malloc(sizeof(struct RBTNode) * m->size);
    nodes_arr = MemTable_to_list(m);
    for (int i = 0; i < m->size; ++i)
    {
        assert(memcmp(nodes_arr[i].key, array[i].key, nodes_arr[i].key_len) == 0);
    }

    assert(table != NULL);
    assert(table->size == SIZE);
    assert(table->capacity == MEMTABLE_SIZE);

    assert(table->low_key_len == 4);
    assert(memcmp(table->low_key, array[0].key, table->low_key_len) == 0);

    assert(table->high_key_len == 4);
    assert(memcmp(table->high_key, array[3].key, table->high_key_len) == 0);

    MemTable_free(m);
    SSTable_free(table);
    remove(path);
}

void TestSSTable_new()
{
    char *path = "./123456790-1.sstable";

    struct MemTable *memtable = MemTable_new();

    struct MultiType
    {
        char *key;
        size_t key_len;
        int64_t value_loc;
    };

    #define SIZE 6

    struct MultiType array[SIZE];

    // Assign values to the elements of the array
    array[0].key = "adex";
    array[0].key_len = strlen("adex");
    array[0].value_loc = 15;

    array[1].key = "suku";
    array[1].key_len = strlen("suku");
    array[1].value_loc = 14;

    array[2].key = "bell";
    array[2].key_len = strlen("bell");
    array[2].value_loc = 17;

    array[5].key = "swah";
    array[5].key_len = strlen("swah");
    array[5].value_loc = 17;

    array[3].key = "zuks";
    array[3].key_len = strlen("zuks");
    array[3].value_loc = 43;

    array[4].key = "jenj";
    array[4].key_len = strlen("jenj");
    array[4].value_loc = 43;

    for (int i = 0; i < SIZE; i++)
    {
        MemTable_set(memtable, array[i].key, array[i].key_len, array[i].value_loc);
    }

    struct SSTable *table = SSTable_new_from_memtable(path, memtable);
    assert(table != NULL);
    SSTable_free(table);
    MemTable_free(memtable);

    struct SSTable *new_table = SSTable_new(path);

    assert(new_table != NULL);
    assert(new_table->timestamp == 123456790);
    assert(new_table->level == 1);
    assert(new_table->size == SIZE);
    assert(new_table->capacity == MEMTABLE_SIZE);
    // for (int i = 0; i < new_table->size; i++)
    // {
    //     assert(new_table->records[i] == i * 20);
    // }

    assert(new_table->low_key_len == 4);
    assert(memcmp(new_table->low_key, array[0].key, new_table->low_key_len) == 0);

    assert(new_table->high_key_len == 4);
    assert(memcmp(new_table->high_key, array[3].key, new_table->high_key_len) == 0);

    SSTable_free(new_table);
    //remove(path);
}

void TestSSTable_get_value_loc()
{
    char *path = "./123456789-1.sstable";

    struct MemTable *memtable = MemTable_new();

    struct MultiType
    {
        char *key;
        size_t key_len;
        int64_t value_loc;
    };

    #define SIZE 6

    struct MultiType array[SIZE];

    // Assign values to the elements of the array
    array[0].key = "adex";
    array[0].key_len = strlen("adex");
    array[0].value_loc = 45;

    array[1].key = "suku";
    array[1].key_len = strlen("suku");
    array[1].value_loc = 25;

    array[2].key = "bell";
    array[2].key_len = strlen("bell");
    array[2].value_loc = 16;

    array[5].key = "swah";
    array[5].key_len = strlen("swah");
    array[5].value_loc = 58;

    array[3].key = "zuks";
    array[3].key_len = strlen("zuks");
    array[3].value_loc = 83;

    array[4].key = "jenj";
    array[4].key_len = strlen("jenj");
    array[4].value_loc = 67;

    for (int i = 0; i < SIZE; i++)
    {
        MemTable_set(memtable, array[i].key, array[i].key_len, array[i].value_loc);
    }

    struct SSTable *table = SSTable_new_from_memtable(path, memtable);
    assert(table != NULL);
    MemTable_free(memtable);


    struct RBTNode *nodes_arr = (struct RBTNode *)malloc(sizeof(struct RBTNode) * table->size);
    nodes_arr = MemTable_to_list(memtable);
    for (int i = 0; i <  table->size; i++)
    {   int64_t value_loc = SSTable_get_value_loc(table, array[i].key, 4);
        assert(value_loc == array[i].value_loc);
    }
 
    char *key = "unkn";
    int64_t value_loc = SSTable_get_value_loc(table, key, 4);
    assert(value_loc == SSTABLE_KEY_NOT_FOUND);

    SSTable_free(table);
    remove(path);
}

void TestSSTable_in_key_range()
{
    char *path = "./123456789-1.sstable";

    struct MemTable *memtable = MemTable_new();

    struct MultiType
    {
        char *key;
        size_t key_len;
        int64_t value_loc;
    };

    #define SIZE 6

    struct MultiType array[SIZE];

    // Assign values to the elements of the array
    array[0].key = "adex";
    array[0].key_len = strlen("adex");
    array[0].value_loc = 45;

    array[1].key = "suku";
    array[1].key_len = strlen("suku");
    array[1].value_loc = 25;

    array[2].key = "bell";
    array[2].key_len = strlen("bell");
    array[2].value_loc = 16;

    array[5].key = "swah";
    array[5].key_len = strlen("swah");
    array[5].value_loc = 58;

    array[3].key = "zuks";
    array[3].key_len = strlen("fuks");
    array[3].value_loc = 83;

    array[4].key = "jenj";
    array[4].key_len = strlen("jenj");
    array[4].value_loc = 67;

    for (int i = 0; i < SIZE; i++)
    {
        MemTable_set(memtable, array[i].key, array[i].key_len, array[i].value_loc);
    }

    struct SSTable *table = SSTable_new_from_memtable(path, memtable);
    assert(table != NULL);
  


    struct RBTNode *nodes_arr = (struct RBTNode *)malloc(sizeof(struct RBTNode) * table->size);
    nodes_arr = MemTable_to_list(memtable);
    for (int i = 0; i <  table->size; i++)
    {   int64_t in_key_range = SSTable_in_key_range(table, array[i].key, 4);
        assert(in_key_range == 1);
    }

   char *key = "zulu";
    int in_key_range = SSTable_in_key_range(table, key, 4);
    assert(in_key_range == 0);
    MemTable_free(memtable);
    SSTable_free(table);
    remove(path);
}

int main()
{
    // New
     TestSSTable_new_from_memtable();
     TestSSTable_new();

    // // // Get Value Loc
    //TestSSTable_get_value_loc();

    // //In Key Range
    // TestSSTable_in_key_range();

    return 0;
}
