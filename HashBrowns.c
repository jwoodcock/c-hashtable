//
// Simple Hash Table
// Hash table library and usage for learning c and
// hash table concepts. 
//

#include <stdio.h>
#include <string.h>
#include <math.h>

// Structures 
struct hash_brown {
    char fname[10];
    char lname[10];
    char key[10];
    int in_use;
};

// DEFINITIONS
size_t hash(char const *value);
unsigned long hash2(char const *str);
unsigned int hash3(char const *value);
unsigned int add_entry(char const *fname, char const *lname, char const *value);
void remove_entry(char const *key);
void update_entry(char const *fname, char const *lname, char const *key);
struct hash_brown * look_up(char const *key);

struct hash_brown hash_table[91];
const int table_size = 91;
double possibles;

int main()
{
    char fname[] = "Jacques";
    char lname[] = "woodcock";
    char key[] = "jwoodcock";
    char lname2[] = "zaccaro";
    char update_fname[] = "Angela";
    char update_lname[] = "Bailey";

    //printf( "Hash 1: %zu\n", hash(fname) );
    //printf( "Hash 2: %zu\n", hash2(fname) );
    //printf( "Hash 3: %u\n", hash3(fname) );

    possibles = pow(2, table_size);
    //printf( "Possibilities: %f\n", possibles );

    int entry = add_entry(fname, lname, key);
    int entry2 = add_entry(fname, lname2, key);
    //int entry2 = add_entry(fname, lname, key);
    //int entry3 = add_entry(fname, lname, key);

    struct hash_brown * match = look_up(key);
    struct hash_brown * match2 = look_up(key);

    printf( "First Entry Hash: %i\n", entry );
    printf( "First Entry FName: %s\n", match->fname );
    printf( "First Entry FName: %s\n", match->lname );
    printf( "First Entry In Use: %i\n", match->in_use );
    printf( "Second Entry Hash: %i\n", entry2 );
    printf( "Second Entry FName: %s\n", match2->fname );
    printf( "Second Entry FName: %s\n", match2->lname );
    printf( "Second Entry In Use: %i\n", match2->in_use );

    update_entry(update_fname, update_lname, key);
    struct hash_brown * match3 = look_up(key);
    printf( "Updated Entry FName: %s\n", match3->fname );
    printf( "Updated Entry LName: %s\n", match3->lname );

    remove_entry(key);
    printf( "Removed Entry in use: %i\n", hash_table[entry].in_use );

    return 0;
}

struct hash_brown * look_up(char const *key)
{
    unsigned int hash_value = hash3(key) % table_size;
    unsigned int offset = hash_value % table_size;
    unsigned int step = ((hash_value / table_size) % table_size);

    step |= 1;

    for (int i = 0; i < table_size; i++) {
        struct hash_brown* entry = &hash_table[offset];
        if (!entry->in_use) {
            return entry;
        }
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }

        offset = (offset + step) % table_size;  // no match found yet. move on.
    }

    return NULL; // oh no, the hash table is full
}

void remove_entry(char const *key)
{
    struct hash_brown * entry = look_up(key);
    entry->in_use = 0;
    strcpy(entry->fname, "");
    strcpy(entry->lname, "");
    strcpy(entry->key, "");
}

void update_entry(char const *fname, char const *lname, char const *key)
{
    struct hash_brown * entry = look_up(key);
    strcpy(entry->fname, fname);
    strcpy(entry->lname, lname);
    strcpy(entry->key, key);
}

unsigned int add_entry(char const *fname, char const *lname, char const *key)
{
    unsigned int hash_value = hash3(key) % table_size;
    unsigned int offset = hash_value % table_size;
    unsigned int step = ((hash_value / table_size) % table_size);

    step |= 1;

    for (int i = 0; i < table_size; i++) {
        struct hash_brown* entry = &hash_table[offset];

        if ((entry->in_use && strcmp(entry->key, key) == 0) || !entry->in_use) {
            entry->in_use = 1;
            strcpy(entry->fname, fname);
            strcpy(entry->lname, lname);
            strcpy(entry->key, key);
            return offset;
        }

        offset = (offset + step) % table_size;  // no match found yet. move on.
    }

    return NULL; // no room left
}

size_t hash(char const *value)
{
    const int ret_size = 32;
    size_t ret = 0x555555;
    const int per_char = 7;

    while (*value) { 
        ret ^= *value++;
        ret = ((ret << per_char) | (ret >> (ret_size - per_char)));
    }
   return ret;
}

unsigned long hash2(char const *value)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *value++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

unsigned int hash3(char const *value)
{
    unsigned int h = 0;
    for (size_t i = 0; i < strlen(value); i++) {
        h += value[i];
    }
    return h;
}
