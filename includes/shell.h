#ifndef SHELL_H
# define SHELL_H
# define PATH_MAX        4096

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

typedef struct s_source
{
	char	*buffer;
	int32_t	bufsize;
	int32_t	pos;

	char	*str;
	int32_t	strsize;
	int32_t	strlen;
}	t_source;

typedef enum e_token_type
{
	T_EOF = -1,
	T_ERROR = 0,

	T_NUMBER = 10,
	T_BUILTIN,
	T_ID,
	T_DOLLAR,
	T_STRING,

	T_EXITSTATUS, // $?

	T_IF = 20,
	T_THEN,
	T_ELSE,
	T_ELIF,
	T_FI,
	T_FOR,
	T_IN,
	T_BREAK,
	T_CONTINUE,
	T_WHILE,
	T_DO,
	T_DONE,

	T_AND = 40, // &
	T_ANDAND, // &&
	T_PIPE, // |
	T_OROR, // ||
	T_LESS, // <
	T_GREAT, // >
	T_EQUALS, // =
	T_DGREAT, // >>
	T_DLESS, // <<
	T_LESSAND, // <&
	T_GREATAND, // >&
	T_LESSGREAT, // <>
	T_DLESSDASH, // <<-
	T_CLOBBER, // >|

	T_SEMI, // ;
	T_DSEMI, // ;;
	T_TICK, // `
	T_NEWLINE // \n

}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

// typedef struct s_token_list
// {
// 	t_token				*token;
// 	struct s_token_list	*next;
// }	t_token_list;


typedef struct s_simple_cmd
{

	char	*cmd;
	int32_t	args_num;
	char	**cmd_args;
	
}	t_simple_cmd;

typedef struct s_command_table
{
	int32_t				commands_num;
	t_simple_cmd		**commands;
	char 				**env;
	// char				*_stdin;
	// char				*_stdout;
	// char				*_stderr;
 
}						t_command_table;

// source.c
t_source	*init_source(char *str);
char		peek(t_source *src);
char		peek2(t_source *src);
char		next_char(t_source *src);
void		unget_char(t_source *src);
void		skip_whitespaces(t_source *src);
void		save_char(t_source *src, char c);
void		clear_str(t_source *src);

// lexer.c
t_token		*get_next_token(t_source *src);
t_token		*init_token(t_token_type type, char *str);

// prompt.c
char		*read_input(char *prompt);

#endif
