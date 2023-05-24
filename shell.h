#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1




#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0


#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field for linked list
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} next_n;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@error_e: the error code for exit()
 *@countline_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@read_fd: the fd from which to read line inputs
 *@histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_e;
	int countline_flag;
	char *fname;
	next_n *env;
	next_n *history;
	next_n *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int read_fd;
	int histcount;
} shell_arg;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: pointer to a function
 */
typedef struct builtin
{
	char *type;
	int (*func)(shell_arg *);
} cmd_builtin;

int interactive(shell_arg *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _myhistory(shell_arg *info);
int _myalias(shell_arg *info);
int _myhelp(shell_arg *info);
int _mycd(shell_arg *info);
int _myexit(shell_arg *info);

int hsh(shell_arg *info, char **av);
int find_builtin(shell_arg *info);
void find_cmd(shell_arg *info);
void fork_cmd(shell_arg *info);

int is_cmd(shell_arg *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(shell_arg *info, char *pathstr, char *cmd);

void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

char **strtow(char *str, char *d);
char **strtow2(char *str, char d);


char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int bfree(void **ptr);

int _erratoi(char *s);
void print_error(shell_arg *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

ssize_t get_input(shell_arg *);
int _getline(shell_arg *, char **, size_t *);
void sigintHandler(int);

void clear_info(shell_arg *);
void set_info(shell_arg *, char **);
void free_info(shell_arg *, int);

char *_getenv(shell_arg *, const char *);
int _myenv(shell_arg *);
int _mysetenv(shell_arg *);
int _myunsetenv(shell_arg *);
int populate_env_list(shell_arg *);

char **get_environ(shell_arg *);
int _unsetenv(shell_arg *, char *);
int _setenv(shell_arg *, char *, char *);

char *get_history_file(shell_arg *info);
int write_history(shell_arg *info);
int read_history(shell_arg *info);
int build_history_list(shell_arg *info, char *buf, int linecount);
int renumber_history(shell_arg *info);

next_n *add_node(next_n **, const char *, int);
next_n *add_node_end(next_n **, const char *, int);
size_t print_list_str(const next_n *);
int delete_node_at_index(next_n **, unsigned int);
void free_list(next_n **);

size_t list_len(const next_n *);
char **next_no_strings(next_n *);
size_t print_list(const next_n *);
next_n *node_starts_with(next_n *, char *, char);
ssize_t get_node_index(next_n *, next_n *);

int is_chain(shell_arg *, char *, size_t *);
void check_chain(shell_arg *, char *, size_t *, size_t, size_t);
int replace_alias(shell_arg *);
int replace_vars(shell_arg *);
int replace_string(char **, char *);

#endif
