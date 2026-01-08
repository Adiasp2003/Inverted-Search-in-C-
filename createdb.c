#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "head.h"

int create_database(FL *file_head, H *hash_table)
{
    FL *temp = file_head;

    while (temp != NULL)
    {
        FILE *fp = fopen(temp->filename, "r"); // open file in read mode
        if (fp == NULL)
        {
            printf("Error opening %s file\n", temp->filename);
            return FAILURE;
        }

        // read a word from file
        char word[60];

        while (fscanf(fp, "%s", word) != EOF)
        {
            // find index
            int index;

            // now find index based on characters to store in hash table
            if ((word[0] >= 'A' && word[0] <= 'Z'))
                index = word[0] - 'A';
            else if ((word[0] >= 'a' && word[0] <= 'z'))
                index = word[0] - 'a';
            else
                index = 26; // for special characters

            // check if hash table index is NULL or not

            // if yes
            if (hash_table[index].mainnode == NULL)
            {
                // create mainnode &update data
                MN *new_main = malloc(sizeof(MN));
                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->sublink = NULL;
                new_main->mainnodelink = NULL;

                // create subnode and update data
                SN *new_sub = malloc(sizeof(SN));
                strcpy(new_sub->filename, temp->filename);
                new_sub->word_count = 1;
                new_sub->sublink = NULL;

                // update subnode address to main node
                new_main->sublink = new_sub;

                // update main node address to hash table
                hash_table[index].mainnode = new_main;
            }

            // if hash table index link not null
            else
            {
                MN *cursor = hash_table[index].mainnode;
                MN *prev = NULL;

                int found_main = 0;

                // search for the main node
                while (cursor != NULL)
                {
                    if (strcmp(cursor->word, word) == 0)
                    {
                        found_main = 1;
                        break;
                    }
                    prev = cursor;
                    cursor = cursor->mainnodelink;
                }

                if (found_main) // if main node already exists
                {
                    SN *subcursor = cursor->sublink;
                    int found_sub = 0;

                    // search subnode(filename)
                    while (subcursor != NULL)
                    {
                        if (strcmp(subcursor->filename, temp->filename) == 0)
                        {
                            subcursor->word_count++;
                            found_sub = 1;
                            break;
                        }
                        subcursor = subcursor->sublink;
                    }

                    if (!found_sub)
                    {
                        // create new subnode
                        SN *new_sub = malloc(sizeof(SN));
                        strcpy(new_sub->filename, temp->filename);
                        new_sub->word_count = 1;

                        // insert subnode at head of subnode list
                        new_sub->sublink = cursor->sublink;
                        cursor->sublink = new_sub;

                        cursor->file_count++;
                    }
                }
                else
                { // main node not found , create new main node
                    MN *new_main = malloc(sizeof(MN));
                    strcpy(new_main->word, word);
                    new_main->file_count = 1;
                    new_main->sublink = NULL;

                    SN *new_sub = malloc(sizeof(SN));
                    strcpy(new_sub->filename, temp->filename);
                    new_sub->word_count = 1;
                    new_sub->sublink = NULL;

                    // attach subnode to main node
                    new_main->sublink = new_sub;

                    // attach mainnode to hash bucket
                    new_main->mainnodelink = hash_table[index].mainnode;
                    hash_table[index].mainnode = new_main;
                }
            }
        }
        fclose(fp);
        temp = temp->next;
    }
    return SUCCESS;
}