#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

// ./a.out f1.txt f2.txt f3.txt
int check_arguments(char *argv[])
{
    int i = 1;
    while (argv[i] != NULL)
    {
        if (strstr(argv[i], ".txt") == NULL)
        {
            printf("Error: %s must be a .txt file\n", argv[i]);
            return FAILURE;
        }
        i++;
    }
    return SUCCESS;
}

// validate file
int validate_file(const char *filename)
{
    // open file and to check file exists
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening %s file\n", filename);
        return FAILURE;
    }

    // file is empty or not
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        printf("%s is empty\n", filename);
        fclose(fp);
        return FAILURE;
    }
    rewind(fp);
    fclose(fp);
    return SUCCESS;
}

// to check duplicate files using linked list
int check_duplicate_file(FL *head, const char *filename)
{
    FL *temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            return DUPLICATE;
        }
        temp = temp->next;
    }
    return SUCCESS;
}

// to create arguments into a linked list and then is checked
int file_linked_list(FL **head, const char *filename)
{
    FL *new = malloc(sizeof(FL));
    strcpy(new->filename, filename);
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    FL *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new;

    return SUCCESS;
}
