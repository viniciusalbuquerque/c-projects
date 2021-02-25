typedef struct entry_t {
    char* key;
    char* value;
    struct entry_t* next;
} entry_t;

typedef struct hash_table {
    entry_t** entries;
    unsigned int table_size;
} hash_table;
