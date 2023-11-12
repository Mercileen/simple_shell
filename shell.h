shell.h

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

/***** MACROS *****/

#include "macros.h"

/***** STRUCTURES *****/

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


/*******MAIN FUNCTIONS ******/


/*========  shell.c  ========*/

/* Initialize the struct with the info of the program */
void initialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* Makes infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

/* Print prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Read one line of standard input*/
int _getline(data_of_program *data);

/* split each line for the logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

/* expand the variables */
void expand_variables(data_of_program *data);

/* expand the aliases */
void expand_alias(data_of_program *data);

/* append string to the end of buffer*/
int buffer_add(char *buffer, char *str_to_add);


/*======str_tok.c ======*/

/* Separate string in tokens using designed delimiter */
void tokenize(data_of_program *data);

/* Creates pointer to the part of a string */
char *_strtok(char *line, char *delim);


/*==== execute.c ======*/

/* Execute the command with its entire path */
int execute(data_of_program *data);


/*====== builtins_list.c ========*/

/* If matches the builtin, executes it */
int builtins_list(data_of_program *data);


/*===== find_in_path.c ======*/

/* Creates an array for the path directories */
char **tokenize_path(data_of_program *data);

/* Search for program in path */
int find_program(data_of_program *data);


/*********** HELPERS FOR THE MEMORY MANAGEMENT ***********/


/*====== helpers_free.c ======*/

/* Frees the memory for the directories */
void free_array_of_pointers(char **directories);

/* Free fields needed for each loop */
void free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void free_all_data(data_of_program *data);

/*********** BUILTINS ***********/

/*====== builtins_more.c =====*/

/* Closing the shell */
int builtin_exit(data_of_program *data);

/* Change the current directory */
int builtin_cd(data_of_program *data);

/* set work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* show the help information */
int builtin_help(data_of_program *data);

/* set, unset and show alias */
int builtin_alias(data_of_program *data);

/*===== builtins_env.c ========*/

/* Shows environment where the shell runs */
int builtin_env(data_of_program *data);

/* creating or override a variable of environment */
int builtin_set_env(data_of_program *data);

/* delete the variable of environment */
int builtin_unset_env(data_of_program *data);

/********* HELPERS FOR THE ENVIRONMENT VARIABLES MANAGEMENT **************/

/*====== env_management.c ========*/

/* Gets Value of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* Overwrite value of the environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* Remove the key from the environment */
int env_remove_key(char *key, data_of_program *data);

/* prints the current environment */
void print_environ(data_of_program *data);

/************ HELPERS FOR THE PRINTING ************/

/*======== helpers_print.c ========*/

/* Prints the string in the standard output */
int _print(char *string);

/* Prints the string in the standard error */
int _printe(char *string);

/* Prints the string in the standard error */
int _print_error(int errorcode, data_of_program *data);

/********** HELPERS FOR THE STRINGS MANAGEMENT **********/

/*======== helpers_string.c ========*/

/* Counts the numbers of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse the string */
void str_reverse(char *string);

/*======== helpers_numbers.c ========*/

/* Cast from the int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);

/*======== alias_management.c ========*/

/* print the list of alias */
int print_alias(data_of_program *data, char *alias);

/* get the alias name */
char *get_alias(data_of_program *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, data_of_program *data);


#endif
