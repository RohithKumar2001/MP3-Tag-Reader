#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

View viewInfo;
Edit editInfo;

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
	error_usage();
	return FAILURE;
    }

    if(argc == 2 && (strcmp(argv[1],"--help") == 0))
	help_menu();
    else if(argc == 2)
	error_usage();

    if(argc == 3)
    {
	if(check_operation(argv) == view)
	{
	    if(check_file_extension(argv, &viewInfo) == SUCCESS)
	    {
		if(open_file(&viewInfo) == SUCCESS)
		{
		    if(check_id3_version(&viewInfo) == SUCCESS)
		    {
			display_details(&viewInfo);
		    }
		    else
		    {
			printf("ERROR : mp3 file version is not matching\n");
		    }
		}
		else
		{
		    printf("ERROR : Please pass valid file\nLike : ./a.out -v mp3filename\n");
		    return FAILURE;
		}
	    }
	    else
	    {
		printf("ERROR : Please pass valid file\nLike : ./a.out -v mp3filename\n");
		return FAILURE;
	    }
	}
	else
	{
	    error_usage();
	    return FAILURE;
	}
    }

    if(argc == 5)
    {
	if(check_operation(argv) == edit)
	{
	    if(check_edit_file_extension(argv, &editInfo) == SUCCESS)
	    {
		if(open_edit_file(&editInfo) == SUCCESS)
		{
		    if(check_edit_id3_version(&editInfo) == SUCCESS)
		    {
			if(check_edit_option(argv,&editInfo) == SUCCESS)
			{
			    if(edit_details(&editInfo) == SUCCESS)
			    {
				printf("Details edited successfully\n");
			    }
			}
		    }

		}
	    }
	}
    }
}

OperationType check_operation(char *argv[])
{
    if (strcmp(argv[1], "-v") == 0)
	return view;
    else if (strcmp(argv[1], "-e") == 0)
	return edit; 
    return unsupported;
}

void error_usage()
{
    printf("ERROR: ./a.out : Invalid arguments\nUSAGE:\n");
    printf("To view please pass like: ./a.out -v mp3filename\n");
    printf("To edit please pass like: ./a.out -e -t/-a/-A/-y/-c/-C changing_text mp3filename\n");
    printf("To get help pass like: ./a.out --help\n");
}

void help_menu()
{
    printf("HELP MENU\n");
    printf("1) -v -> to view mp3 file contents.\n");
    printf("2) -e -> to edit mp3 file contents.\n");
    printf("\t2.1) -t -> to edit song title.\n");
    printf("\t2.2) -a -> to edit artist name.\n");
    printf("\t2.3) -A -> to edit album name.\n");
    printf("\t2.4) -y -> to edit year.\n");
    printf("\t2.5) -c -> to edit content type.\n");
    printf("\t2.6) -C -> to edit comment.\n");
}
