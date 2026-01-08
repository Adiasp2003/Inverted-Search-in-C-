#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

int update_db(H *hash_table)
{
    // read filename from user to update
    char filename[50];
    printf("Enter the filename to be updated\n");
    scanf("%s", filename);

    // open the file in read mode
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("%s file not opened for update\n", filename);
        return FAILURE;
    }

    // check the 1st character is # or not
    char ch = fgetc(fp); //reads 1st '#'
    if (ch != '#')
        return FAILURE;

    // if #
    while (ch == '#')
    {
        char index_str[5];
        char word[50];
        char filecount_str[10];

        // read index,word,filecount from backup.txt file
        if (fscanf(fp, "%[^;];%[^;];%[^;];", index_str, word, filecount_str) != 3)
            break;

        // convert them to integer using atoi function
        int index = atoi(index_str);
        int file_count = atoi(filecount_str);

        // create a mainnode and update the word an file count
        MN *new_main = malloc(sizeof(MN));
        strcpy(new_main->word, word);
        new_main->file_count = file_count;
        new_main->sublink = NULL;
        new_main->mainnodelink = NULL;

        // check index NULL or not
        if (hash_table[index].mainnode == NULL)
        {
            hash_table[index].mainnode = new_main; // yes then update new main node to hast_table index
        }
        // if no then update last node address in HASH table
        else
        {
            MN *temp = hash_table[index].mainnode;

            while (temp->mainnodelink)
            {
                temp = temp->mainnodelink;
            }
            temp->mainnodelink = new_main;
        }

        // run a loop filecount times
        for (int i = 0; i < file_count; i++)
        {
            char f_name[40];
            char w_count[5];

            //read filename and wordcount from backupfile
            fscanf(fp, "%[^;];%[^;];", f_name, w_count);

            int word_count = atoi(w_count);// convert wordcount to integer using atoi

            // create subnode and update the filename and word_count 
            SN *new_sub = malloc(sizeof(SN));
            strcpy(new_sub->filename, f_name);
            new_sub->word_count = word_count;
            new_sub->sublink = NULL;

            // check mainnode->sublink is NULL or NOT
            if (new_main->sublink == NULL)
            {
                new_main->sublink = new_sub; // if yes, update subnode address to mainnode->sublink part
            }

            // if no , update the subnode address in the last subnode link part
            else
            {
                SN *temp = new_main->sublink;
                while (temp->sublink)
                {
                    temp = temp->sublink;
                }
                temp->sublink = new_sub;
            }
        }
        ch = fgetc(fp);// reads next '#
    }
    fclose(fp); // close file after open
    return SUCCESS;
}