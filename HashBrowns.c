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
struct hash_brown * look_up(char const *key);

struct hash_brown hash_table[91];
const int table_size = 91;
double possibles;

int main()
{
    char fname[] = "Jacques";
    char lname[] = "woodcock";
    char key[] = "jwoodcock";

    printf( "Hash 1: %zu\n", hash(fname) );
    printf( "Hash 2: %zu\n", hash2(fname) );
    printf( "Hash 3: %u\n", hash3(fname) );

    possibles = pow(2, table_size);
    printf( "Possibilities: %f\n", possibles );

    int entry = add_entry(fname, lname, key);
    //int entry2 = add_entry(fname, lname, key);
    //int entry3 = add_entry(fname, lname, key);

    struct hash_brown * match = look_up(key);

    printf( "First Entry Hash: %i\n", entry );
    printf( "First Entry FName: %s\n", match->fname );
    printf( "First Entry In Use: %i\n", match->in_use );
    /*printf( "First Entry Hash: %i\n", entry );
    printf( "First Entry FName: %s\n", hash_table[entry].key );
    printf( "First Entry In Use: %i\n", hash_table[entry].in_use );
    printf( "Second Entry Hash: %i\n", entry2 );
    printf( "Second Entry FName: %s\n", hash_table[entry2].key );
    printf( "Second Entry In Use: %i\n", hash_table[entry2].in_use );
    printf( "Third Entry Hash: %i\n", entry3 );
    printf( "Third Entry FName: %s\n", hash_table[entry3].key );
    printf( "Third Entry In Use: %i\n", hash_table[entry3].in_use );*/
    /*strcpy( hashTable[0].fname, "Jacques" );
    strcpy( hashTable[0].lname, "Woodcock" );

    printf( "First Name: %s %s\n", hashTable[0].fname, hashTable[0].lname );*/

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

unsigned int add_entry(char const *fname, char const *lname, char const *key)
{
    unsigned int hash_value = hash3(key) % table_size;
    
    printf( "add hash: %i\n", hash_value);
 
    if (hash_table[hash_value].in_use == 1) {
        unsigned int hash_value2 = hash3(lname);
        hash_value = hash_value2 & table_size;
        if (hash_value > possibles || hash_table[hash_value].in_use == 1) {
            return 0;
        }
    }

    hash_table[hash_value].in_use = 1;
    strcpy(hash_table[hash_value].fname, fname);
    strcpy(hash_table[hash_value].lname, lname);
    strcpy(hash_table[hash_value].key, key);

    return hash_value;
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
    //printf( "\n" );
    for (size_t i = 0; i < strlen(value); i++) {
        h += value[i];
        //int temp = value[i] - '0'; // just testing something out for future hash
        //printf( ":%i\n", temp );
    }
    //printf( "\n" );
    return h;

    //int i = c[0] - '0';
}
