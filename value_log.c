#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "includes/value_log.h"

struct ValueLog *ValueLog_new(const char *path, size_t head, size_t tail)
{
    char *mode = "w+";
    if (access(path, F_OK) == 0)
    {
        mode = "r+";
    }

    FILE *file = fopen(path, mode);
    if (file == NULL)
    {
        perror("fopen");
        return NULL;
    }

    struct ValueLog *log = malloc(sizeof(struct ValueLog));

    log->file = file;
    log->head = head;
    log->tail = tail;

    return log;
}

int ValueLog_append(struct ValueLog *log, size_t *pos, char *key, size_t key_len, const char *value,
                    size_t value_len)
{
    int res = fseek(log->file, (long)log->head, SEEK_SET);

    uint64_t key_len_64 = key_len;
    uint64_t value_len_64 = value_len;

    size_t b_written = fwrite(&key_len_64, sizeof(uint64_t), 1, log->file);
    if (b_written != 1)
    {
        perror("fwrite");
        return -1;
    }

    b_written = fwrite(&value_len_64, sizeof(uint64_t), 1, log->file);
    if (b_written != 1)
    {
        perror("fwrite");
        return -1;
    }

    b_written = fwrite(key, sizeof(char), key_len_64, log->file);
    if (b_written != key_len)
    {
        perror("fwrite");
        return -1;
    }

    b_written = fwrite(value, sizeof(char), value_len_64, log->file);
    if (b_written != value_len)
    {
        perror("fwrite");
        return -1;
    }

    *pos = log->head;
    log->head += sizeof(uint64_t) + sizeof(uint64_t) + key_len + value_len;

    return 0;
}

int ValueLog_get(const struct ValueLog *log, char **value, size_t *value_len, size_t loc)
{
    int res = fseek(log->file, (long)loc, SEEK_SET);
    if (res == -1)
    {
        return -1;
    }

    uint64_t key_len_64;
    uint64_t value_len_64;

    size_t bread = fread(&key_len_64, sizeof(uint64_t), 1, log->file);
    if (bread != 1)
    {
        perror("fread");
        return -1;
    }

    bread = fread(&value_len_64, sizeof(uint64_t), 1, log->file);
    if (bread != 1)
    {
        perror("fread");
        return -1;
    }

    res = fseek(log->file, (long) key_len_64, SEEK_CUR);
    if (res == -1)
    {
        perror("fread");
        return -1;
    }

    *value = malloc(value_len_64);
    *value_len = value_len_64;
    bread = fread(*value, sizeof(char), value_len_64, log->file);
    if(bread != value_len_64){
        perror("fread");
        return -1;
    }

   return 0;
}

int ValueLog_sync(const struct ValueLog *log){
    int res = fflush(log->file);
    if(res == EOF){
        perror("fflush");
        return -1;
    }

    return 0;
}


void ValueLog_free(struct ValueLog *log){
    int res = fclose(log->file);
    if(res==-1){
        perror("fclose");
    }

    free(log);
}