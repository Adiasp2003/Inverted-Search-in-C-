#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "head.h"

int save_database(H *hash_table)
{
    // read filename from user
    char filename[100];
    printf("Enter the backup filename: ");
    scanf("%s", filename);

    // open the file in write mode
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Unable to open file\n");
        return FAILURE;
    }

    // fprintf(fp, "#");   // start of DB

    // run a loop for hash index number of times
    for (int i = 0; i < 27; i++)
    {
        MN *mcur = hash_table[i].mainnode;
        // if null,continue
        if (mcur == NULL)
            continue;

        // else
        while (mcur != NULL)
        {
            fprintf(fp, "#");
            // MAINNODE PORTION → index ; word ; file_count ;
            fprintf(fp, "%d;%s;%d;", i, mcur->word, mcur->file_count);

            // SUBNODE PORTION → filename ; word_count ;
            SN *scur = mcur->sublink;
            while (scur != NULL)
            {
                fprintf(fp, "%s;%d;", scur->filename, scur->word_count);
                scur = scur->sublink;
            }

            mcur = mcur->mainnodelink;
            fprintf(fp, "#\n");
        }
    }

    // fprintf(fp, "#");   // end of DB

    fclose(fp);
    printf("\nSaved data to %s file\n", filename);
    return SUCCESS;
}
