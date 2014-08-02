/* benchmark.c - Code to exercise the hash table code in jwHash.c.
   To run this:
     $ make benchmark
     $ time ./benchmark < sam.txt
*/

#include <ctype.h>

#define main banana
#include "jwHash.c"
#undef main

int main()
{
    int unique_word_count = 0;
    char word[100];

    while (scanf("%99s", word) == 1) {
        size_t i, len;
        struct hash_brown * entry;

        /* Convert word to lowercase. Drop any punctuation at the end.
           Also truncate it to 9 characters since that's the longest key
           jwHash can handle. */
        len = 0;
        for (i = 0; i < 9 && word[i] != '\0'; i++) {
            if (isalnum(word[i])) {
                word[i] = tolower(word[i]);
                len = i + 1;
            }
        }
        word[len] = '\0';

        /* Ask the hash table if we've seen this word before. */
        entry = look_up(word);
        if (entry != NULL && !entry->in_use) {
            /* We haven't seen this word before. Add it. */
            unique_word_count++;
            printf("%s\n", word);
            add_entry("Jacques", "Woodcock", word);
        }
    }

    /* Tell the user if scanf() hit some kind of error. */
    if (ferror(stdin)) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    printf("\nFound %d different words.\n", unique_word_count);
    return 0;
}
