#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "head.h"

// to display the database from all files
int display_database(H *hash_table)
{
    printf("\n--------DISPLAY DB------------\n");
    for (int i = 0; i < 27; i++)
    {
        MN *mcur = hash_table[i].mainnode;
        if (!mcur)
            continue;

        while (mcur)
        {
            printf("\n-------------------------\n");
            printf("WORD  : %s\n", mcur->word);
            printf("FILES : %d\n", mcur->file_count);

            SN *scur = mcur->sublink;
            while (scur)
            {
                printf("%s → %d\n", scur->filename, scur->word_count);
                scur = scur->sublink;
            }

            printf("-------------------------\n");
            mcur = mcur->mainnodelink;
        }
    }

    return SUCCESS;
}
