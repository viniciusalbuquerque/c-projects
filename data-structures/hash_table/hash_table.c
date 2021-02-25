#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#define TABLE_SIZE 5

hash_table* create_hash_table(unsigned int table_size) {
    hash_table* h_table = malloc(sizeof(hash_table));
    h_table->table_size = table_size;
    h_table->entries = malloc(sizeof(entry_t*) * table_size);
    for (int i = 0; i < table_size; i++) {
        h_table->entries[i] = NULL;
    }
    return h_table;
}

unsigned int hash(char* key, unsigned int table_size) {
    unsigned int index = 0;

    for (int i = 0; i < strlen(key); i++) {
        index += key[i] * 39;
    }

    index *= 113;
    return index % table_size;
}

entry_t* hash_table_create_entry(char* key, char* word) {
    entry_t* entry = malloc(sizeof(entry_t));
    entry->key = key;
    entry->value = malloc(sizeof(char) * strlen(word) + 1);
    strcpy(entry->value, word);
    entry->next = NULL;
    return entry;
}

void hash_table_clear_entry(entry_t* entry, unsigned int should_clear_next_entries) {
/*   
    free(entry->key);
    free(entry->value);
*/
    if (should_clear_next_entries) {
        entry_t* next = entry->next;
        while (next) {
            entry_t* aux = next->next;
            free(next);
            next = aux;
        }
    }
    free(entry);
}
void hash_table_put(hash_table* h_table, char* key, char* word) {
    unsigned int index = hash(key, h_table->table_size);
    printf("put key: %s, value: %s, index: %d\n", key, word, index);
    if (!h_table->entries[index]) {
        h_table->entries[index] = hash_table_create_entry(key, word);
        return;
    }

    entry_t* entry = h_table->entries[index];
    entry_t* prev = NULL;
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry_t* new_entry = hash_table_create_entry(key, word);
            new_entry->next = entry->next;
            if (prev) {
                prev->next = new_entry;
            } else {
                h_table->entries[index] = new_entry;
            }
            hash_table_clear_entry(entry, 0);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
    prev->next = hash_table_create_entry(key, word);
}

char* hash_table_get(hash_table* h_table, char* key) {
    unsigned int index = hash(key, h_table->table_size);
    if (h_table->entries[index] == NULL) return NULL;

    entry_t* entry = h_table->entries[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void hash_table_dump(hash_table* h_table) {
    if (h_table->entries == NULL) return;
    unsigned int table_size = h_table->table_size;
    for (int i = 0; i < table_size; i++) {
        printf("\t%d: ", i);
        entry_t* entry = h_table->entries[i];
        while (entry) {
            printf("%s ", entry->value);
            entry = entry->next;
        }
        printf("\n");
    }
}

int main() {
    hash_table* h_table = create_hash_table(TABLE_SIZE);
    hash_table_put(h_table, "seila", "seila");
    hash_table_put(h_table, "seila2", "abcd");
    hash_table_put(h_table, "test", "madajkls");
    hash_table_put(h_table, "testX", "1892h");
    hash_table_put(h_table, "qshe", "asdasa");
    hash_table_put(h_table, "test", "test");
    hash_table_dump(h_table);
    printf("value: %s\n", hash_table_get(h_table, "seila2"));
    printf("value: %s\n", hash_table_get(h_table, "test"));
}
