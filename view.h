#ifndef VIEW
#define VIEW

typedef struct View_mp3
{
    FILE *fptr_file;
    char *file_name;

    char *tag;
    long tag_size;
}View;

/*Check file name*/
int check_file_extension(char *argv[], View *viewInfo);

/*Open mp3 file*/
int open_file(View *viewInfo);

/*Check for ID3 and version*/
int check_id3_version(View *viewInfo);

/*Display details*/
int display_details(View *viewInfo);

/*get size*/
int get_size(FILE *fptr);

/*get tag*/
char* get_tag(View *viewInfo, char *tag);

#endif
