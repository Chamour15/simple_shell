#ifndef _MAIN_H_
#define _MAIN_H_

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#define UNUSED(x) (void)(x)

extern char **environ;

typedef struct shell_s shell_t;
typedef struct builtins_s builtins_t;

/**
 * struct shell_s - shell_s struct.
 * @av: commad line arguments.
 * @user_input: command line of the user.
 * @args: command line arguments.
 * @shell_status: shell status.
 * @line_counter: lines counter.
 * @_environ: environment variables.
 * @pid: process id of the shell.
 */
struct shell_s
{
	char **av;
	char *user_input;
	char **args;
	char *pid;
	char **_environ;
	int shell_status;
	int line_counter;
};

/**
 * struct builtins_s - Builtin struct for command args.
 * @command_name: The name of the command builtin.
 * @function: data type pointer function.
 */
struct builtins_s
{
	char *command_name;
	int (*function)(shell_t *dcshell);
};

/* scanner.c */
char *line_reader(int *end_of_file);
ssize_t _getline(char **buffer, size_t *size, FILE *stream);
void _getline2(char **bufferdp, size_t *sizedp, char *strb, size_t inpsize);

/* string_functions.c*/
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
char *_strdup(const char *str);
int _strcmp(char *s1, char *s2);
char *_strtok(char *string, const char *delim);

/* string_functions2.c*/
int number_length(int num);
int _strlen(const char *str);
char *_itoa(int num);
int _atoi(char *s);
int _isdigit(const char *c);

/* memory_functions.c */
void _memcpy(void *destptr, const void *srcptr, unsigned int sizep);
void *_realloc(void *oldptr, unsigned int old_msize, unsigned int new_msize);
char **_reallocmdp(char **oldmp, unsigned int old_size, unsigned int new_size);

/* command_executer.c*/
int find_command(shell_t *dcshell);
int execute_cmd(shell_t *dcshell);
int isexe(shell_t *dcshell);
char *_cmd_location(char *cmd, char **_environ);
int isdir(char *path, int *i);

/* environment.c */
char *_envir(const char *envname, char **_environ);
int print_env(shell_t *dcshell);
int _setenv(shell_t *dcshell);
int _unsetenv(shell_t *dcshell);
char *create_env(char *envname, char *envval);

/* environment2.c */
void cd_env(char *envname, char *envvalue, shell_t *dcshell);
void cd(shell_t *dcshell);
int cmp_env(const char *envname, const char *pname);
char *get_cdenv(const char *envname, char **_environ);
void cd_env(char *envname, char *envvalue, shell_t *dcsh);

/* command_parser.c */
int parse_cmd(shell_t *dcshell, char *usrinput);
char **parse_cmdline(char *usrinput);

/* command_parser2.c*/
char *non_printed(char *usrinput);

/* errors_handler.c */
int chk_cmd_err(char *directory, shell_t *dcshell);
int errors(shell_t *dcshell, int error);
char *not_found404(shell_t *dcshell);
char *env_error(shell_t *dcshell);

/* builtins_functions.c*/
int (*builtins(char *command)) (shell_t *dcshell);
int shell_exit(shell_t *dcshel);

#endif

