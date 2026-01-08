#ifndef Head_H
#define Head_H

#define SUCCESS 0
#define FAILURE -1
#define DUPLICATE 1

typedef struct file_list // for single linked list to track duplicate file
{
    char filename[30];
    struct file_list *next;
} FL;

typedef struct subnode // for subnode
{
    char filename[30];
    int word_count;
    struct subnode *sublink;
} SN;

typedef struct mainnode // for main node
{
    char word[60];
    int file_count;
    SN *sublink;                   // must point to subnode list
    struct mainnode *mainnodelink; // if collision occurs in the hash table then we need to store it as linked list
} MN;

typedef struct hash // for hash table to store 27 elements
{
    MN *mainnode; // just points to the hash table with specific position
} H;

int check_arguments(char *argv[]);
int validate_file(const char *filename);
int check_duplicate_file(FL *head, const char *filename);
int file_linked_list(FL **head, const char *filename);

int create_database(FL *file_head, H *hash_table);
int display_database(H *hash_table);
int search_word(H *hash_table, char *word);
int save_database(H *hash_table);
int update_db(H *hash_table);
#endif