#include "shell.h"
/**
 * execute - execute the commands with its variables.
 * @data: a pointer to the program's data
 * Return: zero, otherwise, return -1.
 */
int execute(data_of_program *data)
{
	int retval = 0, status;
	pid_t pidd;

	/* check for the program in built ins */
	retval = builtins_list(data);
	if (retval != -1)/* if program was found in built ins */
		return (retval);

	/* check for the program file systems */
	retval = find_program(data);
	if (retval)
	{/* when not found */
		return (retval);
	}
	else
	{/* when the program is found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* the child process, executes program*/
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* the father, wait and checks exit status */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
