#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int main(int argc, char *argv[])
{
    if (argc < 2) // for less arguments
    {
        printf("Enter the correct arguments\n");
        printf("Use: ./a.out file1.txt file2.txt file3.txt ....\n");
        return FAILURE;
    }

    // validate arguments
    if (check_arguments(argv) == FAILURE)
        return FAILURE;

    // t0 check file names
    FL *file_head = NULL;

    // to check for valid files based on argument count
    for (int i = 1; i < argc; i++)
    {
        if (validate_file(argv[i]) == FAILURE)
        {
            printf("Fatal error. Exiting program.\n");
            return FAILURE;
        }

        if (check_duplicate_file(file_head, argv[i]) == DUPLICATE)
        {
            printf("Duplicate filename not accepted: %s\n", argv[i]);
            printf("Exiting program\n");
            return FAILURE;
        }

        file_linked_list(&file_head, argv[i]);
    }

    if (file_head == NULL)
    {
        printf("NO valid files to process\n");
        return FAILURE;
    }

    // create hash table of 27 characters

    H hash_table[27];

    for (int i = 0; i < 27; i++)
        hash_table[i].mainnode = NULL;

    // menu to select
    int choice;
    while (1)
    {
        printf("\n----- MENU -----\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Word\n");
        printf("4. Save Database to File\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            // CREATE DATABASE
            if (create_database(file_head, hash_table) == SUCCESS)
                printf("Database created successfully.\n");
            else
                printf("Database creation failed.\n");

            break;
        }

        case 2:
        {
            // DISPLAY DATABASE
            display_database(hash_table);
            break;
        }

        case 3:
        {
            // SEARCH WORD
            char key[50];
            printf("Enter word to search: "); // read a word
            scanf("%s", key);

            search_word(hash_table, key);
            break;
        }

        case 4:
        {
            // SAVE DATABASE
            save_database(hash_table);
            break;
        }

        case 5:
        {
            // UPDATE DATABASE
            for (int i = 0; i < 27; i++)
                hash_table[i].mainnode = NULL;

            if (update_db(hash_table) == SUCCESS)
                printf("Database updated successfully.\n");
            else
                printf("Database updation failed.\n");

            break;
        }

        case 6:
        {
            // EXIT
            printf("Exiting...\n");
            return SUCCESS;
        }

        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}