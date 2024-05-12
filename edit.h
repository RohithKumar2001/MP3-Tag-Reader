#ifndef EDIT
#define EDIT

#include "types.h"

typedef struct Edit_mp3
{
    FILE *fptr_file;
    char *file_name;
    char op[2];

    char *change_text;
    int size_change_text;

    long tag_size;   //entire meta container size.

    char *tag;

}Edit;

/* Function Definition */
int check_edit_file_extension(char *argv[], Edit *editInfo);

/* Open Required files*/
int open_edit_file(Edit *editInfo);

/* Do required checks*/
int do_checks_edit(Edit *editInfo);

/* Check for ID3 and version*/
int check_edit_id3_version(Edit *editInfo);

/* Check option*/
int check_edit_option(char *argv[], Edit *editInfo);

/*Edit the detail*/
int edit_details(Edit *editInfo);

/* to edit the tag data */
int edit_tag(Edit *editInfo, char *tag);

#endif
