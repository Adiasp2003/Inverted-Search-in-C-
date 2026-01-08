#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "head.h"

int search_word(H *hash_table, char *word)
{
    // find the index
    int index;

    if (isalpha(word[0]))
        index = tolower(word[0] - 'a');
    else
        index = 26;

        //check the user given word is present in the mainnode list or not
    MN *mcur = hash_table[index].mainnode;

    //if present,print the data in the subnodes
    while (mcur != NULL)
    {
        if (strcmp(mcur->word, word) == 0)
        {
            printf("\nWord '%s' found in database:\n", word);

            SN *scur = mcur->sublink;

            while (scur != NULL)
            {
                printf("→ File: %s | Count: %d\n",
                       scur->filename,
                       scur->word_count);

                scur = scur->sublink;
            }
            return SUCCESS;
        }
        mcur = mcur->mainnodelink;
    }
    //else word not found
    printf("\nWord '%s' not found in database\n", word);
    return FAILURE;
}