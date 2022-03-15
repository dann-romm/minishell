#ifndef SHELL_H
# define SHELL_H

# define PATH_MAX 4096
# define ERRCHAR 0
# define ESCCHAR '\\'

# include <errno.h>

# include <errno.h>

// readline rl_clear_history rl_on_new_line rl_replace_line rl_redisplay add_history
# include <readline/readline.h>

// printf
# include <stdio.h>

// malloc, free, exit, getenv
# include <stdlib.h>

// write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot, 
# include <unistd.h>

// open
# include <fcntl.h>

// wait, waitpid, wait3, wait4
# include <sys/wait.h>

// signal, sigaction, kill
# include <signal.h>

// stat, lstat, fstat
# include <sys/stat.h>

// opendir, readdir, closedir
# include <dirent.h>

// strerror
# include <string.h>

// ioctl
# include <sys/ioctl.h>

// tcsetattr, tcgetattr,
# include <termios.h>

// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>

# include "hashtable.h"

typedef enum e_cmd_type
{
	CMD_NONE = -1,
	CMD_CD,
	CMD_PWD,
	CMD_ECHO,
	CMD_EXPORT,
	CMD_EXIT,
	CMD_UNSET,
	CMD_ENV
} 	t_cmd_type;

typedef struct s_simple_cmd
{
	char		*cmd;
	int32_t		args_num;
	char		**cmd_args;
	t_cmd_type	type;
}	t_simple_cmd;

typedef struct s_redirect
{
	char	*_stdin;
	char	*_stdout;
	int		is_stdin_append;
	int		is_stdout_append;
}	t_redirect;

typedef struct s_command_table
{
	int32_t			commands_num;
	t_simple_cmd	**commands;
	t_redirect		redirect;
}	t_command_table;

typedef struct s_shell
{
	t_hashtable	*env_global;
	t_hashtable	*env_local;
}	t_shell;

t_shell	*g_shell;

// prompt.c
char		*read_input(char *prompt);

// execute.c
int	execute(t_command_table *table);

// init_g_shell.c
void	init_shell();

#endif
