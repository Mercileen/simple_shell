#include "shell.h"

/**
* builtins_list - searches for the match and execute the associate builtin
* @data: structure for the program's data
* Return: Returns the return of the function executed is there is a match,
* otherwise returns -1.
**/
int builtins_list(data_of_program *data)
{
int iterator;
builtins options[] = {
{"exit", builtin_exit},
{"help", builtin_help},
{"cd", builtin_cd},
{"alias", builtin_alias},
{"env", builtin_env},
{"setenv", builtin_set_env},
{"unsetenv", builtin_unset_env},
{NULL, NULL}
};

/*walk in through structure*/
for (iterator = 0; options[iterator].builtin != NULL; iterator++)
{
/*if there is  match between given command and builtin,*/
if (str_compare(options[iterator].builtin, data->command_name, 0))
{
/*execute the function, and return the return value of the function*/
return (options[iterator].function(data));
}
/*if there is no match return -1 */
}
return (-1);
}
