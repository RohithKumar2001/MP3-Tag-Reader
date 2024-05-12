#ifndef MAIN_H
#define MAIN_H

#include "types.h"
#include "view.h"
#include "edit.h"

#define SUCCESS 0
#define FAILURE 1

/*Function to display Error Message*/
void error_usage(void);

/*Function to display Help Menu*/
void help_menu(void);

/*Check Operation Type*/
OperationType check_operation(char *argv[]);


#endif
