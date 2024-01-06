
#ifndef WISKEY_VALUE_LOG_H
#define WISKEY_VALUE_LOG_H


#include <stdio.h>


struct ValueLog{
    FILE *file;
    size_t head;
    size_t tail;
};

struct ValueLog *ValueLog_new(const char *path, size_t head, size_t tail);


int ValueLog_append(struct ValueLog *log, size_t *pos, char *key, size_t key_len, const char *value, size_t value_len);


int ValueLog_get(const struct ValueLog *log, char **value, size_t *value_len, size_t value_loc);

int ValueLog_sync(const struct ValueLog *log);

void ValueLog_free(struct ValueLog *log);

#endif