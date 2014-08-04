//
// Simple Hash Table
// Hash table library and usage for learning c and
// hash table concepts. 
//
// @jwoodcock on github.com/jwoodcock
//

#include <stdio.h>
#include <string.h>
#include <math.h>

// Structures or just the one struct which will be our hash_table
struct hash_brown {
    char fname[10];
    char lname[10];
    char key[10];
    int in_use;
};

// DEFINITIONS
size_t              hash(char const *value);
unsigned long       hash2(char const *str);
unsigned int        hash3(char const *value);
unsigned long       worst_hash(char const *value);
unsigned int        add_entry(char const *fname, char const *lname, char const *value);
void                remove_entry(char const *key);
void                update_entry(char const *fname, char const *lname, char const *key);
unsigned int        set_hash(unsigned int hash);
unsigned long       get_hash(char const *key);
struct hash_brown * look_up(char const *key);

// Set Globals
struct hash_brown hash_table[91]; // the hash table we are going to use
const int table_size = 91; // the max size the table will be
unsigned int HASH = 0; // which hash to use set at run time

/**
 * The main method just does some testing on the Hash table and methods.
 */
int main()
{
    char fname[] = "Jacques";
    char lname[] = "woodcock";
    char key[] = "jwoodcock";
    char lname2[] = "zaccaro";
    char update_fname[] = "Angela";
    char update_lname[] = "Bailey";

    // set Hash
    set_hash(0);

    int entry = add_entry(fname, lname, key);
    int entry2 = add_entry(fname, lname2, key);

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

/**
 * This method does a hash look up for a povided key and returns
 * a pointer to a match if one is found or NULL if one is not found.
 */
struct hash_brown * look_up(char const *key)
{
    unsigned int hash_value = get_hash(key);
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

/**
 * This method removes an entry from the hash table based on the
 * provided key if there is a match.
 */
void remove_entry(char const *key)
{
    struct hash_brown * entry = look_up(key);
    if (entry->in_use && strcmp(entry->key, key) == 0) {
        entry->in_use = 0;
        strcpy(entry->fname, "");
        strcpy(entry->lname, "");
        strcpy(entry->key, "");
    }
}

/**
 * This method updates an entry in the hash table with the newly
 * provided data if at match is found.
 */
void update_entry(char const *fname, char const *lname, char const *key)
{
    struct hash_brown * entry = look_up(key);
    if (entry->in_use && strcmp(entry->key, key) == 0) {
        strcpy(entry->fname, fname);
        strcpy(entry->lname, lname);
        strcpy(entry->key, key);
    }
}

/**
 * This method add an entry in the first available empty table slot.
 */
unsigned int add_entry(char const *fname, char const *lname, char const *key)
{
    unsigned int hash_value = get_hash(key);
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

/**
 * This method gets a hash valued based on the provided key using the
 * configured hashing algorithm.
 */
unsigned long get_hash(char const *key)
{
    if (HASH == 0) {
        return hash(key) % table_size;
    }
    if (HASH == 1) {
        return hash2(key) % table_size;
    }
    if (HASH == 2) {
        return hash3(key) % table_size;
    }
    if (HASH == 3) {
        return worst_hash(key) % table_size;
    }
    return 0;
}

/**
 * Metho for configuring the table's hash method.
 */
unsigned int set_hash(unsigned int hash)
{
    if (hash > 3) {
        return 0;
    }
    HASH = hash;
    return 1;
}

/**
 * -------------------------------------------
 * Hashes - The different hashes you can use
 * -------------------------------------------
 */

/**
 * Hash 1 which uses bitshifting
 */
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

/**
 * Hash 2 which uses bitshifting
 */
unsigned long hash2(char const *value)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *value++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

/**
 * Hash 3 simple hashing based on the length of the provided key
 * Would not use in production.
 */
unsigned int hash3(char const *value)
{
    unsigned int h = 0;
    for (size_t i = 0; i < strlen(value); i++) {
        h += value[i];
    }
    return h;
}

/**
 * Hash 4 should never be used unless you are testing the collision handling
 * of the hash table.
 */
unsigned long worst_hash(char const *value)
{ 
    return 4; 
}
