#include "shell.h"

/**
* print_alias - add, remove or show aliases
* @alias: alias name to be printed
* Return: zero if its a sucess, or other number if declared in arguments
*/
int print_alias(data_of_program *data, char *alias)
{
int i, j, alias_length;
char buffer[250] = {'\0'};

if (data->alias_list)
{
alias_length = str_length(alias);
for (i = 0; data->alias_list[i]; i++)
{
if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
&&	data->alias_list[i][alias_length] == '='))
{
for (j = 0; data->alias_list[i][j]; j++)
{
buffer[j] = data->alias_list[i][j];
if (data->alias_list[i][j] == '=')
break;
}
buffer[j + 1] = '\0';
buffer_add(buffer, "'");
buffer_add(buffer, data->alias_list[i] + j + 1);
buffer_add(buffer, "'\n");
_print(buffer);
}
}
}

return (0);
}

/**
* get_alias - It must add, remove or show aliases
* @data: structure for program's data
* Return: zero if its sucess, or other number if declared the arguments
*/
char *get_alias(data_of_program *data, char *name)
{
int i, alias_length;

/* arguments to validate */
if (name == NULL || data->alias_list == NULL)
return (NULL);

alias_length = str_length(name);

for (i = 0; data->alias_list[i]; i++)
{/* Iterates environment */
if (str_compare(name, data->alias_list[i], alias_length) &&
data->alias_list[i][alias_length] == '=')
{/* returns the value NAME */
return (data->alias_list[i] + alias_length + 1);
}
}
/* returns NULL */
return (NULL);

}

/**
* set_alias - it must add, or override alias
* @alias_string: set alias in the form (name='value')
* @data: structure for program's data
* Return: zero if its sucess, or other number if its declared in the arguments
*/

int set_alias(char *alias_string, data_of_program *data)
{
int i, j;
char buffer[250] = {'0'}, *temp = NULL;

/* arguments to validate */
if (alias_string == NULL ||  data->alias_list == NULL)
return (1);
/* alias to find = char */
for (i = 0; alias_string[i]; i++)
if (alias_string[i] != '=')
buffer[i] = alias_string[i];
else
{/* searches value alias in another alias */
temp = get_alias(data, alias_string + i + 1);
break;
}

/* alias list and check the varname */
for (j = 0; data->alias_list[j]; j++)
if (str_compare(buffer, data->alias_list[j], i) &&
data->alias_list[j][i] == '=')
{/* if the alias alredy exist */
free(data->alias_list[j]);
break;
}

/* add alias */
if (temp)
{/* if the alias already exist */
buffer_add(buffer, "=");
buffer_add(buffer, temp);
data->alias_list[j] = str_duplicate(buffer);
}
else /* if alias is not  */
data->alias_list[j] = str_duplicate(alias_string);
return (0);
}
