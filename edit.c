#include<stdio.h>
#include<string.h>
#include"main.h"

int check_edit_file_extension(char *argv[], Edit *editInfo)
{
    if (strstr(argv[4], ".mp3"))
	editInfo->file_name = argv[4];
    else
	return FAILURE;

    editInfo->change_text = argv[3];
    editInfo->size_change_text = strlen(editInfo->change_text);

    return SUCCESS;
}

int open_edit_file(Edit *editInfo)
{
    editInfo->fptr_file = fopen(editInfo->file_name, "r+");

    if (editInfo->fptr_file == NULL)
    {
	perror("fopen");
	fprintf(stderr, "ERROR: unable to open file %s\n", editInfo->file_name);
	return FAILURE;
    }
    return SUCCESS;
}


int check_edit_id3_version(Edit *editInfo)
{
    char buff_id3[3], buff_ver[2];

    fread(buff_id3, 1, 3,editInfo->fptr_file);

    if (strcmp(buff_id3, "ID3"))
	return FAILURE;

    fread(buff_ver, 1, 2, editInfo->fptr_file);

    if (buff_ver[0] != 3)
	return FAILURE;

    return SUCCESS;
}

int check_edit_option(char *argv[], Edit *editInfo)
{
    char *option[] = {"-t", "-a", "-A", "-y", "-c", "-C"};

    for (int i = 0; i < 6; i++)
	if (strcmp(argv[2], option[i]) == 0)
	{
	    strcpy(editInfo->op, option[i]);
	    return SUCCESS;
	}

    return SUCCESS;
}


int edit_details(Edit *editInfo)
{
    rewind(editInfo->fptr_file); 
    fseek(editInfo -> fptr_file, 6, SEEK_SET);
    editInfo -> tag_size = get_size(editInfo -> fptr_file); 
 
    if (strcmp(editInfo -> op, "-t") == 0)
    {
	if (edit_tag(editInfo, "TIT2") == FAILURE)
	    printf("Input Size exceed!!\n");
	else
	    printf("Title modified\n");
    }

    if (strcmp(editInfo->op,"-a") == 0)
    {
	if (edit_tag(editInfo,"TPE1") == FAILURE)
	    printf("Input Size exceed!!\n");
	else
	    printf("Artist name modified\n");
    }

    if (strcmp(editInfo->op,"-A") == 0)
    {
	if (edit_tag(editInfo,"TALB") == FAILURE)
	    printf("Input Size exceed!!\n");
	else 
	    printf("Album name modified\n");
    }

    if (strcmp(editInfo->op,"-y") == 0)
    {
	if (edit_tag(editInfo, "TYER") == FAILURE)
	    printf("Input size exceed!!\n");
	else 
	    printf("Year modified\n");
    }

    if (strcmp(editInfo -> op, "-c") == 0)
    {
	if (edit_tag(editInfo, "TCON") == FAILURE)
	    printf("Input Size exceed!!\n");
	else 
	    printf("Content modified\n");
    }

    if (strcmp(editInfo -> op, "-C") == 0)
    {
	if (edit_tag(editInfo, "COMM") == FAILURE)
	    printf("Input Size exceed!!\n");
	else 
	    printf("Comment modified\n");
    }

    return SUCCESS;
}

int edit_tag(Edit *editInfo, char *tag)
{
    char bufftag[4], cl = 0;
    int size, flag = 1, i;

    rewind(editInfo -> fptr_file); 
    fseek(editInfo -> fptr_file, 10, SEEK_SET);
    fread(bufftag, 1, 4, editInfo -> fptr_file);
    size = get_size(editInfo -> fptr_file);
    fseek(editInfo -> fptr_file, 2, SEEK_CUR);

    while(flag)
    {
	if (strcmp(bufftag, tag) == 0)
	{
	    if (size > editInfo -> size_change_text)
	    {
		fseek(editInfo -> fptr_file, 1, SEEK_CUR);		
		for (i = 0; i < size - 1; i++)
		    fwrite(&cl, 1, 1, editInfo -> fptr_file);
		fseek(editInfo -> fptr_file, -(size - 1), SEEK_CUR);
		fwrite(editInfo -> change_text, editInfo -> size_change_text, 1, editInfo -> fptr_file);
		flag = 0;		
	    }
	    else
		return FAILURE; 
	}
	else
	{
	    fseek(editInfo -> fptr_file, size, SEEK_CUR);
	    fread(bufftag, 1, 4, editInfo -> fptr_file);
	    size = get_size(editInfo -> fptr_file);
	    fseek(editInfo -> fptr_file, 2, SEEK_CUR);
	}

	if (ftell(editInfo -> fptr_file) >= editInfo -> tag_size)
	{
	    editInfo -> tag = NULL;
	    break;
	}
    }
    return SUCCESS;
}
