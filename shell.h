#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

/* STRUCTURES */

/**
 * struct info- the structure  for the program's data
 * @program_name: the name of the executable
 * @input_line:  the pointer to input read for _getline
 * @command_name: the pointer to the first command typed by the user
 * @exec_counter: the number of excecuted comands
 * @file_descriptor: the file descriptor to the input of commands
 * @tokens: the pointer to array of tokenized input
 * @env: the copy of the environ
 * @alias_list: the array of pointers with aliases.
 */
typedef struct info
{
	char *input_line;
	char *program_name;
	char *command_name;
	int file_descriptor;
	int exec_counter;
	char **tokens;
	char **alias_list;
	char **env;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;

/* string.c */
char *str_duplicate(char *string);
int str_compare(char *string1, char *string2, int number);
void str_reverse(char *string);
int str_length(char *string);

/* strings_1.c */
char *str_concat(char *string1, char *string2);
void long_to_string(long number, char *string, int base);
int _atoi(char *s);
int count_characters(char *string, char *character);

/* print.c */
int _printe(char *string);
int _print_error(int errorcode, data_of_program *data);

/* memset.c */
void free_recurrent_data(data_of_program *data);
void free_all_data(data_of_program *data);
void free_array_of_pointers(char **array);

/* _alias.c */
int print_alias(data_of_program *data, char *alias);
char *get_alias(data_of_program *data, char *name);
int set_alias(char *alias_string, data_of_program *data);

/* _builtin.c */
int builtin_env(data_of_program *data);
int builtin_set_env(data_of_program *data);
int builtin_unset_env(data_of_program *data); 

/* _builtin_exit.c */
int builtin_exit(data_of_program *data);
int builtin_cd(data_of_program *data);
int set_work_directory(data_of_program *data, char *new_dir);
int builtin_help(data_of_program *data);

/*  get_line.c */
int _getline(data_of_program *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

/* _exec.c */
int execute(data_of_program *data);

/* main.c */

void handle_ctrl_c(int opr UNUSED);
void sisifo(char *prompt, data_of_program *data);
void initialize_data(data_of_program *data, int argc, char *argv[], char **env);
int main(int argc, char *argv[], char *env[]);


/* path.c */
int check_file(char *full_path);
char **tokenize_path(data_of_program *data);
int find_program(data_of_program *data);

/* _variables.c */
int buffer_add(char *buffer, char *str_to_add);
void expand_alias(data_of_program *data);
void expand_variables(data_of_program *data);

/* _builtinlist.c */
int builtins_list(data_of_program *data);
int builtin_alias(data_of_program *data);

/*_env.c */
char *env_get_key(char *key, data_of_program *data);
int env_set_key(char *key, char *value, data_of_program *data);
int env_remove_key(char *key, data_of_program *data);
void print_environ(data_of_program *data);


/* _tokstr.c */
char *_strtok(char *line, char *delim);
void tokenize(data_of_program *data);


#endif
