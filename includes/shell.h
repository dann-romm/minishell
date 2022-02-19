#ifndef SHELL_H
# define SHELL_H

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

# define EOFCHAR -1
# define ERRCHAR 0

typedef struct s_source
{
	char	*buffer;
	int32_t	bufsize;
	int32_t	pos;
}	t_source;



typedef struct s_simple_command
{

	char	*cmd;
	int32_t	args_num;
	char	**cmd_args;
	
}	t_simple_command;

typedef struct s_command_table
{
	int32_t				commands_num;
	t_simple_command	**commands;
	char				*_stdin;
	char				*_stdout;
	char				*_stderr;



}	t_command_table;


#endif
