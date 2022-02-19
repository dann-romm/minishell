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

typedef enum e_token_type
{
	/* GRAMMAR SYMBOLS */
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,
	
	// The following are the operators containing more than one character
	AND_IF, // &&
	OR_IF, // ||
	DSEMI, // ;;
	DLESS, // <<
	DGREAT, // >>
	LESSAND, // <&
	GREATAND, // >&
	LESSGREAT, // <>
	DLESSDASH, // <<-

	CLOBBER, // >|

	// The following are the reserved words
	IF, // if
	THEN, // then
	ELSE, // else
	ELIF, // elif
	FI, // fi
	DO, // do
	DONE, // done

	CASE, // case
	ESAC, // esac
	WHILE, // while
	UNTIL, // until
	FOR, // for

	// These are reserved words, not operator tokens, and are
	// recognized when reserved words are recognized
	LBRACE, // {
	RBRACE, // }
	BANG, // !

	IN, // in

	/* GRAMMAR */

	// linebreak complete_commands linebreak
	// linebreak
	program,

	// complete_commands newline_list complete_command
	// complete_command
	complete_commands,

	// list separator_op
	// list
	complete_command,

	// list separator_op and_or
	// and_or
	list,

	// pipeline
	// and_or AND_IF linebreak pipeline
	// and_or OR_IF  linebreak pipeline
	and_or,

	// BANG pipe_sequence
	// pipe_sequence
	pipeline,

	// command
	// pipe_sequence '|' linebreak command
	pipe_sequence,

	// simple_command
	// compound_command
	// compound_command redirect_list
	// function_definition
	command,

	// brace_group
	// subshell
	// for_clause
	// case_clause
	// if_clause
	// while_clause
	// until_clause
	compound_command,

	// '(' compound_list ')'
	subshell,

	// linebreak term
	// linebreak term separator
	compound_list,

	// term separator and_or
	// and_or
	term,

	// FOR name do_group
	// FOR name sequential_sep do_group
	// FOR name linebreak in sequential_sep do_group
	// FOR name linebreak in wordlist sequential_sep do_group
	for_clause,

	// NAME
	name,

	// IN
	in,

	// wordlist WORD
	// WORD
	wordlist,
	
	// CASE WORD linebreak in linebreak case_list ESAC
	// CASE WORD linebreak in linebreak case_list_ns ESAC
	// CASE WORD linebreak in linebreak ESAC
	case_clause,

	// case_list case_item_ns
	// case_item_ns
	case_list_ns,

	// case_list case_item
	// case_item
	case_list,

	// pattern ')' linebreak
	// pattern ')' compound_list
	// '(' pattern ')' linebreak
	// '(' pattern ')' compound_list
	case_item_ns,

	// pattern ')' linebreak DSEMI linebreak
	// pattern ')' compound_list DSEMI linebreak
	// '(' pattern ')' linebreak DSEMI linebreak
	// '(' pattern ')' compound_list DSEMI linebreak
	case_item,

	// WORD
	// pattern '|' WORD
	pattern,

	// IF compound_list THEN compound_list else_part FI
	// IF compound_list THEN compound_list FI
	if_clause,

	// ELIF compound_list Then compound_list
	// ELIF compound_list Then compound_list else_part
	// ELSE compound_list
	else_part,

	// THILE compound_list do_group
	while_clause,

	// UNTIL compound_list do_group
	until_clause,

	// fname '(' ')' linebreak function_body
	function_definition,

	// compound_command
	// compound_command redirect_list
	function_body,
	fname,
	brace_group,
	do_group,
	simple_command,
	cmd_name,
	cmd_word,
	cmd_prefix,
	cmd_suffix,
	redirect_list,
	io_redirect,
	io_file,
	filename,
	io_here,
	here_end,
	newline_list,
	linebreak,
	separator_op,
	separator,
	sequential_sep
}	t_token_type;

typedef struct s_token
{
	t_source	*t_source;
	int32_t		str_len;
	char		*str;
}	t_token;



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

// source.c
char	peek(t_source *src);
char	peek2(t_source *src);
char	next_char(t_source *src);
void	unget_char(t_source *src);
void	skip_whitespaces(t_source *src);

#endif
