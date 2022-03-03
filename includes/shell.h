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

# define ERRCHAR 0
# define ESCCHAR '\\'

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


// typedef struct s_simple_command
// {

// 	char	*cmd;
// 	int32_t	args_num;
// 	char	**cmd_args;
	
// }	t_simple_command;

// typedef struct s_command_table
// {
// 	int32_t				commands_num;
// 	t_simple_command	**commands;
// 	char				*_stdin;
// 	char				*_stdout;
// 	char				*_stderr;
// }	t_command_table;

// source.c
t_source	*init_source(char *str);
char		peek(t_source *src);
char		peek2(t_source *src);
char		next_char(t_source *src);
void		unget_char(t_source *src);
void		skip_whitespaces(t_source *src);
void		save_char(t_source *src, char c);
void		clear_str(t_source *src);

// utils_ft.c
int			is_alnum(char c);
int			is_space(char c);
char		*ft_strcpy(char *dest, char *src);
int			ft_strlen(char *str);
char		*ft_strdup(const char *str);
char		*ft_strcat(char *dst, char *src);
char		*ft_strncat(char *s1, const char *s2, unsigned int n);
int			ft_strcmp(char *s1, char *s2);

// lexer.c
t_token		*get_next_token(t_source *src);
t_token		*init_token(t_token_type type, char *str);

// prompt.c
char		*read_input(char *prompt);

#endif
